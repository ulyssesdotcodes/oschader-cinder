#include "EffectProgram.h"

using namespace ci;

EffectProgram::EffectProgram(std::shared_ptr<ProgramState> state, ci::gl::BatchRef prog) :
	Program(prog, state)
{
}

ci::gl::Texture2dRef EffectProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef fbo)
{
	gl::ScopedTextureBind tex(base->getColorTexture(), 0);
	return Program::getColorTexture(fbo, base);
}