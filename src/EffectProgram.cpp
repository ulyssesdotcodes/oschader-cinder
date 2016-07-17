#include "EffectProgram.h"

using namespace ci;

EffectProgram::EffectProgram(std::shared_ptr<ProgramState> state, ci::gl::BatchRef prog) :
	Program(prog), mLastUpdatedFrame(0)
{
	mState = state;
	updateUniform("tex_base", 0);
}

EffectProgramRef EffectProgram::create(std::shared_ptr<ProgramState> state, std::string frag) {
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return EffectProgramRef(new EffectProgram(state, batch));
}

std::shared_ptr<ci::Camera> EffectProgram::camera()
{
	return nullptr;
}

std::shared_ptr<ci::ivec2> EffectProgram::matrixWindow()
{
	return std::make_shared<ivec2>(app::getWindowSize());
}

ci::gl::Texture2dRef EffectProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef fbo)
{
	gl::ScopedTextureBind tex(base->getColorTexture(), 0);

	return Program::getColorTexture(fbo, base);
}

void EffectProgram::setCombinator(std::string)
{
	throw Exception("Can't set the base of an effect prog.");
}
