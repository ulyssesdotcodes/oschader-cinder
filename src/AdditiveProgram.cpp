#include "AdditiveProgram.h"

using namespace ci;

AdditiveProgramRef AdditiveProgram::create(BaseProgramRef a)
{
	return AdditiveProgramRef(new AdditiveProgram(FragmentProgram::create("shaders/additive_blend.frag"), a));
}

void AdditiveProgram::mappend(BaseProgramRef b)
{
	mB = b;
}

std::shared_ptr<ci::Camera> AdditiveProgram::camera()
{
	return mBlendProg->camera();
}

std::shared_ptr<ci::ivec2> AdditiveProgram::matrixWindow()
{
	return mBlendProg->matrixWindow();
}

ci::gl::TextureRef AdditiveProgram::getColorTexture()
{
	return mBlendProg->getColorTexture();
}

void AdditiveProgram::draw()
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

AdditiveProgram::AdditiveProgram(BaseProgramRef blendProg, BaseProgramRef a) : BaseProgram(blendProg)
{
	mBlendProg = blendProg;
	mA = a;

	mBlendProg->updateUniform("tex_A", 0);
	mBlendProg->updateUniform("tex_B", 1);
}

