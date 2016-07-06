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

void Program::draw()
{
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
