#pragma once

#include "ProgramRect.h"

class EffectRect : public ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, std::string);

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra);

protected:
	EffectRect(ProgramStateRef, ci::gl::BatchRef);
};