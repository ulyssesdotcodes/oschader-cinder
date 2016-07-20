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
	mAccumulatedSound = 0.0;

	auto ctx = audio::Context::master();

	mInputNode = ctx->createInputDeviceNode();

	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	mMonitor = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

	mInputNode >> mMonitor;

	mInputNode->enable();
	ctx->enable();

	app::getWindow()->setTitle(mInputNode->getDevice()->getName());

	mMult = 2.0;
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
		scaledSpectrum[i] = audio::linearToDecibel(scaledSpectrum[i]) / 100.0f;
	}
	mSpectrum = scaledSpectrum;

	mAccumulatedSound += getVolume();

	return mSpectrum;
}

gl::TextureRef AudioSource::getMagSpectrumTexture() {
	float spectrum[1024 * 4];
	std::vector<float> spectrumVec = getMagSpectrum();
	audio::Buffer buffer = mMonitor->getBuffer();

	for (std::vector<float>::size_type i = 0; i < spectrumVec.size(); i++) {
		spectrum[i * 4] = spectrumVec[i] * mMult;
		spectrum[i * 4 + 1] = buffer.getData()[i] * mMult;
		spectrum[i * 4 + 2] = 0.0f;
		spectrum[i * 4 + 3] = 256.0f;
	}

	return gl::Texture::create(Surface32f(spectrum, 1024, 1, 4, SurfaceChannelOrder::RGBA));
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

std::vector<float> AudioSource::getEqs(int binCount) {
	return getEqs(binCount, 1.0);
}

std::vector<float> AudioSource::getEqs(int binCount, float scale)
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
		*it = *it * scale/ binSize;
	}

	return bins;
}
