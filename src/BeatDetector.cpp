#include "BeatDetector.h"

#include "cinder/app/App.h"
#include "cinder/CinderMath.h"

using namespace ci;

const float VOLUME_MIN = 0.001;

BeatDetector::BeatDetector() {
	mTempo = 2.f;
	mLastBeat = 0;
	mEnergyIndex = 0;
	mDeterioration = 0;

	mAverageEnergy = {0};
	for (int i = 0; i < BUCKETS; ++i) {
		mEnergyHistory[i] = {0};
	}
}

float BeatDetector::getBeat(std::shared_ptr<AudioSource> as, float c) {
	std::array<float, BUCKETS> sum = { 0 };
	int j = 0;
	int startBucketIndex = 0;
	int bucketSize = 1;
	int i = 0;
	std::vector<float> spectrum = as->getMagSpectrum();
	while (j < BUCKETS) {
		if(spectrum[i] > VOLUME_MIN)
		{
			sum[j] += (spectrum[i] * spectrum[i]) / (float) bucketSize;
		}

		i++;

		if (i >= startBucketIndex + bucketSize) {
			j++;
			bucketSize = j + 1;
			startBucketIndex = i;
		}
	}

	float dBeat = app::getElapsedSeconds() - mLastBeat;
	float tempo = 1 / dBeat;
	float gaus = (float)((1 + cos(abs(tempo - mTempo))) / 2 * 3.1415);
	float weight = gaus * tempo * abs(tempo - mTempo);

	float beat = -1.0f;
	for (i = 0; i < BUCKETS; ++i) {
		float newBeat = (sum[i] * weight) - c * mAverageEnergy[i];
		if (beat < newBeat && newBeat > 0) {
			beat = newBeat;
			mTempo = glm::max<float>(tempo, 4);
			mLastBeat = app::getElapsedSeconds();
		}

		mAverageEnergy[i] -=
			mEnergyHistory[i][(int)mEnergyIndex] / HISTORY;
		mEnergyHistory[i][(int) mEnergyIndex] = sum[i];
		mAverageEnergy[i] += mEnergyHistory[i][(int)mEnergyIndex] / HISTORY;
		++mEnergyIndex;
		if (mEnergyIndex >= HISTORY) {
			mEnergyIndex = 0;
		}
	}

	if (beat > 0) {
		app::console() << "Beat " << app::getElapsedSeconds() << " tempo: " << mTempo << std::endl;
	}
	return beat > 0 ? 1.f : 0.f; 
	//std::array<float, BUCKETS> sum = {};
	//int j = 0;
	//int startBucketIndex = 0;
	//int bucketSize = 1;
	//int i = 0;
	//as->update();
	//std::vector<float> spectrum = as->getMagSpectrum();
	//while (j < BUCKETS) {
	//	sum[j] += spectrum[i + 20] / bucketSize;
	//	i++;

	//	if (i >= startBucketIndex + bucketSize) {
	//		j++;
	//		bucketSize = j + 1;
	//		startBucketIndex = i;
	//	}
	//}

	//float beat = -1.0;
	//for (int i = 0; i < BUCKETS; ++i) {
	//	if (beat < 0) {
	//		beat = sum[i] - c * mAverageEnergy[i];
	//		if (beat > 0) {
	//			beat = 1.0;
	//		}
	//	}
	//	mAverageEnergy[i] -=
	//		mEnergyHistory[i][mEnergyIndex] / HISTORY;
	//	mEnergyHistory[i][mEnergyIndex] = sum[i];
	//	mAverageEnergy[i] += mEnergyHistory[i][mEnergyIndex] / HISTORY;
	//	++mEnergyIndex;
	//	if (mEnergyIndex >= HISTORY) {
	//		mEnergyIndex = 0;
	//	}
	//}

	//if (beat > mBeat) {
	//	mBeat = beat;
	//	mDeterioration = 4 * beat / HISTORY;
	//}
	//else {
	//	mBeat -= mDeterioration;
	//	mBeat = math<float>::max(mBeat, 0.0);
	//}

	//return mBeat;
}