#include "EffectProgram.h"

using namespace ci;

EffectProgram::EffectProgram(ProgramRef prog) :
	Program(prog->batch()), mEffectProg(prog), mLastUpdatedFrame(0)
{
	mEffectProg->updateUniform("tex_base", 0);
}

std::shared_ptr<ci::Camera> EffectProgram::camera()
{
	return mEffectProg->camera();
}

std::shared_ptr<ci::ivec2> EffectProgram::matrixWindow()
{
	return mEffectProg->matrixWindow();
}

ci::gl::Texture2dRef EffectProgram::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	gl::ScopedTextureBind tex(mBaseProg->getColorTexture(b, a), 0);

	gl::ScopedFramebuffer sfbo(a);
	gl::ScopedViewport svp(a->getSize());
	gl::ScopedMatrices mats();
	gl::setMatricesWindow(a->getSize());

	mEffectProg->draw();

	return a->getColorTexture();
}

void EffectProgram::draw(ci::gl::FboRef a, ci::gl::FboRef b) {
	gl::ScopedTextureBind tex(mBaseProg->getColorTexture(b, a), 0);

	mEffectProg->draw();
}

void EffectProgram::draw() {
	throw new Exception("Can't draw with no fbos");
}

void EffectProgram::setBase(ProgramRef p)
{
	mBaseProg = p;
}
