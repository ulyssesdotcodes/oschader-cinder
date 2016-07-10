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
gl::Texture2dRef Program::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	gl::ScopedFramebuffer fbo(a);
	gl::ScopedViewport vp(a->getSize());
	gl::ScopedMatrices ms();
	gl::setMatricesWindow(a->getSize());

	draw(b, a);

	return a->getColorTexture();
}
void Program::draw(ci::gl::FboRef, ci::gl::FboRef) {
	draw();
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

void Program::setBase(std::string)
{
	throw Exception("Can't set the base of a regular prog.");
}
