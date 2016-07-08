#include "AdditiveProgram.h"

using namespace ci;

AdditiveProgramRef AdditiveProgram::create(ProgramRef a)
{
	return AdditiveProgramRef(new AdditiveProgram(FragmentProgram::create("shaders/additive_blend.frag"), a));
}

std::shared_ptr<ci::Camera> AdditiveProgram::camera()
{
	return mBlendProg->camera();
}

std::shared_ptr<ci::ivec2> AdditiveProgram::matrixWindow()
{
	return mBlendProg->matrixWindow();
}

ci::gl::TextureRef AdditiveProgram::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	if(mB) {
		return mBlendProg->getColorTexture(b, a);
	}

	return mA->getColorTexture(a, b);
}

void AdditiveProgram::updateUniform(std::string name, float val)
{
	mA->updateUniform(name, val);
}

void AdditiveProgram::draw(ci::gl::FboRef a, ci::gl::FboRef b)
{
	if(mB) {
		gl::ScopedTextureBind texA(mA->getColorTexture(), 0);
		gl::ScopedTextureBind texB(mB->getColorTexture(), 1);
		mBlendProg->draw();
	}
	else {
		mA->draw();
	}
}

AdditiveProgram::AdditiveProgram(EffectProgramRef blendProg, EffectProgramRef a) : EffectProgram(blendProg)
{
	mBlendProg = blendProg;
	mA = a;

	mBlendProg->updateUniform("tex_A", 0);
	mBlendProg->updateUniform("tex_B", 1);
}

