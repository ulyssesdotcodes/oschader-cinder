#pragma once

#include "cinder/gl/gl.h"

#include "cinder/Exception.h"

namespace input {
	class InputResolver {
	public:
		virtual int parseInputType(std::string type) = 0;
		virtual bool isTexture(int inputType) = 0;
		virtual bool isFloat(int inputType) = 0;
		virtual float getFloat(int inputType) = 0;
		virtual ci::gl::TextureRef getTexture(int inputType, float mod) = 0;
	};
};