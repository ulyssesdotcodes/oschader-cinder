#pragma once

#include "FragmentProgram.h"

typedef std::shared_ptr<class AdditiveProgram> AdditiveProgramRef;

class AdditiveProgram : public EffectProgram {
public:
	static AdditiveProgramRef create(ProgramRef a);
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();
	virtual ci::gl::TextureRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef);
	virtual void updateUniform(std::string name, float val);

private:
	AdditiveProgram(ProgramRef, ProgramRef);
	ProgramRef mBlendProg;

	ProgramRef mA;
	ProgramRef mB;
};