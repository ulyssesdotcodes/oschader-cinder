#pragma once

#include "cinder/gl/gl.h"

#include "cinder/Exception.h"

namespace input {
	struct InputParameters {
		std::string inputType;
		std::vector<float> params;
		InputParameters(std::string it, std::vector<float> ps) : inputType(it), params(ps) {}
	};

	class InputResolver {
	public:
		virtual int parseInputType(std::string type) = 0;
		virtual bool isTexture(int inputType) = 0;
		virtual bool isFloat(int inputType) = 0;
		virtual float getFloat(InputParameters) = 0;
		virtual ci::gl::TextureRef getTexture(InputParameters) = 0;
	};
};