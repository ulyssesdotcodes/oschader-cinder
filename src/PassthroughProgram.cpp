#include "PassthroughProgram.h"

ProgramRef PassthroughProgram::create(ProgramStateRef state)
{
	return std::shared_ptr<PassthroughProgram>(new PassthroughProgram(state));
}

std::shared_ptr<ci::Camera> PassthroughProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> PassthroughProgram::matrixWindow()
{
	return std::shared_ptr<ci::ivec2>();
}

ci::gl::Texture2dRef PassthroughProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	auto e = getEffect();
	if(e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}

PassthroughProgram::PassthroughProgram(ProgramStateRef state) : Program(nullptr, state) // Note: VERY CAREFUL HERE
{
}
