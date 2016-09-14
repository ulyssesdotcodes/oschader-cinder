#include "ImageProgram.h"

using namespace ci;

ImageProgram::ImageProgram(ProgramStateRef state) : Program(nullptr, state)
{
}

ProgramRef ImageProgram::create(ProgramStateRef state)
{
	return ProgramRef(new ImageProgram(state));
}

std::shared_ptr<ci::Camera> ImageProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> ImageProgram::matrixWindow()
{
	return std::shared_ptr<ci::ivec2>();
}

void ImageProgram::updateUniform(std::string name, std::string val)
{
	if (name.compare("image") == 0 && val.compare(mPath) != 0) {
		mPath = val;
		mImage = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset("images/" + val)));
	}
}

ci::gl::Texture2dRef ImageProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	if(mImage) {
		gl::ScopedFramebuffer fbo(base);
		gl::clear(Color::black());

		gl::pushViewport();
		gl::pushMatrices();
		gl::setMatricesWindow(app::getWindow()->getSize());
		vec2 offset = (vec2)(app::getWindowSize() - mImage->getSize()) * 0.5f;
		auto dst = mImage->getBounds();
		dst.offset(offset);
		gl::draw(mImage, dst);
		gl::popMatrices();
		gl::popViewport();
	}

	auto e = getEffect();
	if(e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}