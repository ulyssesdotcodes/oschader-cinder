#pragma once

#include "Program.h"

typedef std::shared_ptr<class BaseProgram> BaseProgramRef;

class BaseProgram : public Program {
public:
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();

	virtual ci::gl::TextureRef getColorTexture(ci::gl::FboRef);
	virtual void mappend(BaseProgramRef);

protected:
	BaseProgram(ProgramRef prog);
	virtual void update();

private:
	ProgramRef mProg;

	uint32_t mLastUpdatedFrame;
};