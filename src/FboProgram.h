#pragma once

#include "BaseProgram.h"

class FboProgram : public BaseProgram {
public:
	static BaseProgramRef create(ProgramRef);
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();

	virtual ci::gl::TextureRef getColorTexture();

protected:
	FboProgram(ProgramRef, ci::gl::FboRef);
	virtual void update();

private:
	ProgramRef mProg;
	ci::gl::FboRef mFbo;

	uint32_t mLastUpdatedFrame;
};