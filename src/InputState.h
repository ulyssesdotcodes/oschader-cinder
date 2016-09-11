#pragma once

#include "cinder/gl/gl.h"

#include "cinder/Exception.h"

namespace input {

	enum class InputType { AUDIO_TEXTURE, CAMERA_TEXTURE, KICK, EQ_TEXTURE, VOLUME, NULL_T };

	struct InputState {
		ci::gl::TextureRef audioTexture;
		ci::gl::TextureRef cameraTexture;
		float volume;
		float kick;
		std::function<ci::gl::TextureRef(int)> eqTexture;
	};

	static InputType parseInputType(std::string str) {
		if (str == "audio_texture") {
			return InputType::AUDIO_TEXTURE;
		}
		else if (str == "camera_texture") {
			return InputType::CAMERA_TEXTURE;
		}
		else if (str == "kick") {
			return InputType::KICK;
		}
		else if (str == "volume") {
			return InputType::VOLUME;
		}
		else if (str == "eq_texture") {
			return InputType::EQ_TEXTURE;
		}
		else {
			return InputType::NULL_T; 
		}
	}

	static bool isFloat(InputType t) {
		return t == InputType::VOLUME || t == InputType::KICK;
	}

	static float getFloat(InputState s, InputType t) {
		switch (t) {
		case InputType::VOLUME:
			return s.volume;
		case InputType::KICK:
			return s.kick;
		default:
            throw ci::Exception("That isn't a float input type.");
			return -1;
		}
	}

	static bool isTexture(InputType t) {
		return t == InputType::AUDIO_TEXTURE || t == InputType::CAMERA_TEXTURE || t == InputType::EQ_TEXTURE;
	}

	static ci::gl::TextureRef getTexture(InputState s, InputType t, float mod) {
		switch (t) {
		case InputType::AUDIO_TEXTURE:
			return s.audioTexture;
		case InputType::CAMERA_TEXTURE:
			return s.cameraTexture;
		case InputType::EQ_TEXTURE:
			return s.eqTexture(floor(mod));
		default:
            throw ci::Exception("That isn't a texture input type.");
			return nullptr;
		}
	}
}
