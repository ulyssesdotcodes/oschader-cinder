#include "OschaderInputState.h"

void OschaderInputResolver::update(InputState is) {
	mState = is;
}

int OschaderInputResolver::parseInputType(std::string str) {
	if (str == "audio_texture") {
		return AUDIO_TEXTURE;
	}
	else if (str == "camera_texture") {
		return CAMERA_TEXTURE;
	}
	else if (str == "kick") {
		return KICK;
	}
	else if (str == "volume") {
		return VOLUME;
	}
	else if (str == "eq_texture") {
		return EQ_TEXTURE;
	}

	return -1;
}

bool OschaderInputResolver::isFloat(int t) {
	return t == VOLUME || t == KICK;
}

float OschaderInputResolver::getFloat(int t) {
	switch (t) {
	case VOLUME:
		return mState.volume;
	case KICK:
		return mState.kick;
	default:
		throw ci::Exception("That isn't a float input type.");
		return -1;
	}
}

bool OschaderInputResolver::isTexture(int t) {
	return t == AUDIO_TEXTURE || t == CAMERA_TEXTURE || t == EQ_TEXTURE;
}

ci::gl::TextureRef OschaderInputResolver::getTexture(int t, float mod) {
	switch (t) {
	case AUDIO_TEXTURE:
		return mState.audioTexture;
	case CAMERA_TEXTURE:
		return mState.cameraTexture;
	case EQ_TEXTURE:
		return mState.eqTexture(floor(mod));
	default:
		throw ci::Exception("That isn't a texture input type.");
		return nullptr;
	}
}
