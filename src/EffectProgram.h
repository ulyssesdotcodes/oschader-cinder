#pragma once

#include "Program.h"
#include "ProgramState.h"

typedef std::shared_ptr<class EffectProgram> EffectProgramRef;

class EffectProgram : public virtual Program {
public:
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef fbo);

protected:
	EffectProgram(std::shared_ptr<ProgramState>, ci::gl::BatchRef prog);
};