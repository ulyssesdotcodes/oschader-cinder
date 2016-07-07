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

ci::gl::TextureRef BaseProgram::getColorTexture(ci::gl::FboRef fbo)
{
	gl::ScopedFramebuffer sfbo(fbo);
	gl::ScopedViewport svp(fbo->getSize());

	draw();

	return fbo->getColorTexture();
}

void BaseProgram::mappend(BaseProgramRef)
{
}
