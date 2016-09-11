#pragma once

#include "ProgramRect.h"

class FadeEffect : public ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, std::string);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef) override;

protected:
	FadeEffect(ProgramStateRef, ci::gl::BatchRef);

private:
	ci::gl::FboRef mLastFrame;
};