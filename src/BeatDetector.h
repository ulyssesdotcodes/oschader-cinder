#pragma once

#include "AudioSource.h"

const int HISTORY = 43;
const int BUCKETS = 16;

class BeatDetector {
public:
	BeatDetector();
	float getBeat(std::shared_ptr<AudioSource> as, float c);

private:
	std::array<std::array<float, HISTORY>, BUCKETS> mEnergyHistory;
	int mEnergyIndex;
	std::array<float, BUCKETS> mAverageEnergy;
	float mLastBeat;
	float mTempo;
	int mHistory;
	float mDeterioration;
};