#include "AudioSource.h"

#include "cinder/app/App.h"
#include "cinder/audio/audio.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"

using namespace ci;

/*
 * Note: All outputs are scaled to decibel then divided by 100.
 */

void AudioSource::setup() {
    mLastUpdateFrame = -1;
	mLastUpdateTexFrame = -1;
	mAccumulatedSound = 0.0;

	auto ctx = audio::Context::master();
    ctx->deviceManager()->setSampleRate(ctx->deviceManager()->getDefaultInput(), 48000);

    mInputNode = ctx->createInputDeviceNode();

	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	mMonitor = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

	mInputNode >> mMonitor;

	mInputNode->enable();
	ctx->enable();

	app::getWindow()->setTitle(mInputNode->getDevice()->getName());

	mMult = 2.0;

	gl::Texture::Format fmt;
	fmt.setDataType(GL_FLOAT);
	fmt.setInternalFormat(GL_RGB32F);

	mSpectrumTex = gl::Texture::create(1024, 1, fmt);
}

void AudioSource::update() {
}

std::vector<float> AudioSource::getMagSpectrum() {
	// Cache spectrum to avoid recalculating it
	int frame = app::getElapsedFrames();
	if (frame <= mLastUpdateFrame) {
		return mSpectrum;
	}

	mLastUpdateFrame = frame;

	std::vector<float> scaledSpectrum = mMonitor->getMagSpectrum();

	for (int i = 0; i < scaledSpectrum.size(); ++i) {
		float val = audio::linearToDecibel(scaledSpectrum[i]) / 100.0f + 1.0f;
		scaledSpectrum[i] = log10(val * val);
	}
	mSpectrum = scaledSpectrum;

	mAccumulatedSound += getVolume();

	return mSpectrum;
}

gl::TextureRef AudioSource::getMagSpectrumTexture() {
	int frame = app::getElapsedFrames();
	if (frame <= mLastUpdateTexFrame) {
		return mSpectrumTex;
	}

	float spectrum[1024 * 3];
	std::vector<float> spectrumVec = getMagSpectrum();
	audio::Buffer buffer = mMonitor->getBuffer();
	float smoothBuffer[1024];

	for (int i = 0; i < 1024; ++i) {
		int j = -2;
		smoothBuffer[i] = 0;
		if (j + i > 0) smoothBuffer[i] += 0.061 * buffer.getData()[i + j];
		j++;
		if (j + i > 0) smoothBuffer[i] += 0.242 * buffer.getData()[i + j];
		j++;
		smoothBuffer[i] += 0.393 * buffer.getData()[i + j];
		j++;
		if(j + i < buffer.getSize() - 1) smoothBuffer[i] += 0.242 * buffer.getData()[i + j];
		j++;
		if(j + i < buffer.getSize() - 1) smoothBuffer[i] += 0.061 * buffer.getData()[i + j];
	}

	for (std::vector<float>::size_type i = 0; i < spectrumVec.size(); i++) {
		spectrum[i * 3] = spectrumVec[i] * mMult;
		spectrum[i * 3 + 1] = smoothBuffer[i] * mMult;
		spectrum[i * 3 + 2] = 0.0f;
	}

	mSpectrumTex->update(Surface32f(spectrum, 1024, 1, 3, SurfaceChannelOrder::RGB));

	return mSpectrumTex;
}

float AudioSource::getHighestVolumePos() {
	std::vector<float> spectrumVec = getMagSpectrum();

	float max = 0;
	float size = spectrumVec.size() / 3;

	for (std::vector<float>::size_type i = 0; i < size; i++) {
		float pos = i / size;
		if (math<float>::pow(spectrumVec[i], 1.5 * pos) > spectrumVec[max]) {
			max = i;
		}
	}

	return max / size;
}

float AudioSource::getVolume() 
{
	return mMonitor->getVolume() * mMult;
}

float AudioSource::getAccumulatedSound()
{
	return mAccumulatedSound;
}

std::vector<float> AudioSource::getEqs(int binCount)
{
	std::vector<float> buffer = getMagSpectrum();
	std::vector<float> bins(binCount);
	int binSize = buffer.size() * 0.5 / binCount;

	for (std::vector<float>::size_type i = 0; i < buffer.size() * 0.5; i++) {
		int bin = i / binSize;

		// Just discard the last one if it fits perfectly.
		if(bin < bins.size()) {
			bins[bin] += glm::pow(buffer[i], 2.0 - ((float) i / (float) buffer.size()));
		}
	}

	for (std::vector<float>::iterator it = bins.begin(); it != bins.end(); ++it) {
		// 100.0f to account for linear to decibal
		*it = *it / binSize;
	}

	return bins;
}

gl::TextureRef AudioSource::getEqTexture(int binCount) {
	auto texIter = mEqTexes.find(binCount);
	if (texIter == mEqTexes.end()) {
		gl::Texture::Format fmt;
		fmt.setDataType(GL_FLOAT);
		fmt.setInternalFormat(GL_RGB32F);
		auto result = mEqTexes.insert(std::pair<int, gl::TextureRef>(binCount, gl::Texture::create(512, 1, fmt)));
		texIter = result.first;
	}

	gl::TextureRef tex = texIter->second;

	binCount++;

	std::vector<float> buffer = getMagSpectrum();
	std::vector<float> bins(binCount);
	float eqs[512 * 3];

	int binSize = buffer.size() * 0.5f / binCount;
	for (std::vector<float>::size_type i = 0; i < buffer.size() * 0.5f; i++) {
		int bin = i / binSize;

		// Just discard the last one if it fits perfectly.
		if(bin < bins.size()) {
			bins[bin] += buffer[i];
		}
	}

	binCount--;
	float scale = (binCount * binSize) / 512.0f;
	for (std::vector<float>::size_type i = 0; i < 512; i++) {
		int bin = (int) (i * scale / binSize) + 1;

		eqs[i * 3] = bins[bin] / binSize;
		eqs[i * 3 + 1] = bins[bin] / binSize;
		eqs[i * 3 + 2] = 0;
	}

	tex->update(Surface32f(eqs, 512, 1, 3, SurfaceChannelOrder::RGB));

	return tex;
}
