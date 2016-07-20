#pragma once

#include "cinder/audio/audio.h"
#include "cinder/gl/gl.h"

class AudioSource {
public:
	void setup();
	void update();
	std::vector<float> getMagSpectrum();
	ci::gl::TextureRef getMagSpectrumTexture();
	float getVolume();
	float getAccumulatedSound();
	float getHighestVolumePos();
	std::vector<float> getEqs(int binCount);
	std::vector<float> getEqs(int binCount, float scale);

private:
	ci::audio::InputDeviceNodeRef mInputNode;
	ci::audio::MonitorSpectralNodeRef mMonitor;
	std::vector<float>  mSpectrum;

	int mLastUpdateFrame;
	float mAccumulatedSound;
	float mMult;
};
