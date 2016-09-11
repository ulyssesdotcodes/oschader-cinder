#include "TexInputProgram.h"

using namespace ci;
using namespace input;

ProgramRef TexInputProgram::create(ProgramStateRef state)
{
	return ProgramRef(new TexInputProgram(state));
}

ci::gl::Texture2dRef TexInputProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	if(isTexture(mInput)) {
		gl::ScopedFramebuffer fbo(base);

		auto tex = getTexture(mLastInputState, mInput, mMod);
		gl::draw(tex, tex->getBounds(), base->getBounds());
	}

	auto e = getEffect();
	if (e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}

void TexInputProgram::update(input::InputState in)
{
	mLastInputState = in;
}

TexInputProgram::TexInputProgram(ProgramStateRef state) : Program(nullptr, state)
{
	
}

std::shared_ptr<ci::Camera> TexInputProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> TexInputProgram::matrixWindow()
{
	return std::shared_ptr<ci::ivec2>();
}

void TexInputProgram::updateUniform(std::string name, std::string val, float mod)
{
	if (name.compare("program") != 0) {
		return;
	}

	InputType it = parseInputType(val);

	if (it == InputType::NULL_T || !isTexture(it)) {
		throw Exception("Invalid input type"); // Can do because it's haskell and we'll constrain types
		return;
	}

	mInput = it;
	mMod = mod;
}