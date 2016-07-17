#include "Program.h"

using namespace ci;

Program::Program(gl::BatchRef batch) : mBatch(batch)
{
}

ci::gl::BatchRef Program::batch()
{
	return mBatch;
}

void Program::updateUniform(std::string name, float val) {
	mBatch->getGlslProg()->uniform("i_" + name, val);
}

void Program::updateUniform(std::string name, int val) {
	mBatch->getGlslProg()->uniform("i_" + name, val);
}

// Note that it uses fbo a
gl::Texture2dRef Program::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef _)
{
	gl::ScopedFramebuffer fbo(base);
	gl::ScopedViewport vp(base->getSize());
	gl::ScopedMatrices ms();
	gl::setMatricesWindow(base->getSize());

	draw();

	auto effect = getEffect();
	if (effect) {
		return effect->getColorTexture(base, _);
	}

	return base->getColorTexture();
}

void Program::draw() {
	gl::pushViewport();
	gl::pushMatrices();

	auto cam = camera();
	std::shared_ptr<ci::ivec2> win = matrixWindow();
	if (cam) {
		gl::setMatrices(*cam);
	}
	else if (win) {
		gl::setMatricesWindow(*win);
	}

	mBatch->draw();

	gl::popMatrices();
	gl::popViewport();
}

ProgramRef Program::getEffect()
{
	if(mEffect) {
		return mState->getProgram(*mEffect);
	}

	return nullptr; 
}

void Program::setEffect(std::string eff)
{
	mEffect = std::make_shared<std::string>(eff);
}

void Program::setCombinator(std::string)
{
	throw Exception("Can't set the combinator of a regular prog.");
}
