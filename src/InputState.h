#pragma once

#include "cinder/gl/gl.h"

namespace input {

	enum class InputType { AUDIO_TEXTURE, EQ_TEXTURE, VOLUME, NULL_T };

	struct InputState {
		ci::gl::TextureRef audioTexture;
		float volume;
		std::function<ci::gl::TextureRef(int)> eqTexture;
	};

	static InputType parseInputType(std::string str) {
		if (str == "audio_texture") {
			return InputType::AUDIO_TEXTURE;
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
		return t == InputType::VOLUME;
	}

	static float getFloat(InputState s, InputType t) {
		switch (t) {
		case InputType::VOLUME:
			return s.volume;
		default:
			throw std::exception("That isn't a float input type.");
			return -1;
		}
	}

	static bool isTexture(InputType t) {
		return t == InputType::AUDIO_TEXTURE || t == InputType::EQ_TEXTURE;
	}

	static ci::gl::TextureRef getTexture(InputState s, InputType t, float mod) {
		switch (t) {
		case InputType::AUDIO_TEXTURE:
			return s.audioTexture;
		case InputType::EQ_TEXTURE:
			return s.eqTexture(floor(mod));
		default:
			throw std::exception("That isn't a texture input type.");
			return nullptr;
		}
	}
}
