#pragma once

#include "Program.h"

typedef std::shared_ptr<class EffectProgram> EffectProgramRef;

class EffectProgram : public Program {
public:
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef);

	static EffectProgramRef create(std::string frag);

	virtual void draw(ci::gl::FboRef, ci::gl::FboRef);

	virtual void setBase(ProgramRef);

protected:
	EffectProgram(ci::gl::BatchRef prog);

private:
	ProgramRef mBaseProg;

	uint32_t mLastUpdatedFrame;
};