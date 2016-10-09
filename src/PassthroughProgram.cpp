#include "PassthroughProgram.h"

#include <boost/algorithm/string.hpp>

using namespace ci;

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

void PassthroughProgram::updateUniform(std::string name, std::string val)
{
	if (name.compare("program") == 0) {
		boost::trim(val);
		mProgram = val;
	}
}

ci::gl::Texture2dRef PassthroughProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	auto p = getProgram(mProgram);
	if(p) {
		gl::pushViewport();
		gl::pushMatrices();

		gl::setMatricesWindow(extra->getSize());
		gl::ScopedFramebuffer fbo(extra);
		gl::clear(Color::black());
		gl::draw(p->getColorTexture(base, extra));

		gl::popMatrices();
		gl::popViewport();
	}

	auto e = getEffect();
	if(e) {
		return e->getColorTexture(extra, base);
	}

	return extra->getColorTexture();
}

PassthroughProgram::PassthroughProgram(ProgramStateRef state) : Program(nullptr, state) // Note: VERY CAREFUL HERE
{
}
