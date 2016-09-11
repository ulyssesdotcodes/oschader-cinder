#include "CameraProgram.h"

using namespace ci;

ProgramRef CameraProgram::create(ProgramStateRef state)
{
	return ProgramRef(new CameraProgram(state));
}

std::shared_ptr<ci::Camera> CameraProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> CameraProgram::matrixWindow()
{
	return std::make_shared<ci::ivec2>(mCapture->getSize());
}

ci::gl::Texture2dRef CameraProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	gl::ScopedFramebuffer fbo(base);
	gl::draw(mCaptureTex, Area(ivec2(0), *matrixWindow()), app::getWindowBounds());
	ProgramRef e = getEffect();
	if (e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}

void CameraProgram::update(input::InputState)
{
}

CameraProgram::CameraProgram(ProgramStateRef state) : Program(nullptr, state), mCaptureTex(gl::Texture::create(1280, 720))
{
}
