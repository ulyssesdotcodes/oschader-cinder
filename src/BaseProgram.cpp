#include "BaseProgram.h"

using namespace ci;

BaseProgram::BaseProgram(ProgramRef prog) :
	Program(prog->batch()), mProg(prog), mLastUpdatedFrame(0)
{
}

std::shared_ptr<ci::Camera> BaseProgram::camera()
{
	return mProg->camera();
}

std::shared_ptr<ci::ivec2> BaseProgram::matrixWindow()
{
	return mProg->matrixWindow();
}

void BaseProgram::update()
{
}

void BaseProgram::draw()
{
	gl::pushViewport();
	gl::pushMatrices();

	gl::setMatricesWindow(getColorTexture()->getBounds().getSize());
	gl::draw(getColorTexture());

	gl::popMatrices();
	gl::popViewport();
}

void BaseProgram::mappend(BaseProgramRef)
{
}
