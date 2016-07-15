#include "EffectProgram.h"

using namespace ci;

EffectProgram::EffectProgram(std::shared_ptr<ProgramState> state, ci::gl::BatchRef prog) :
	Program(prog), mLastUpdatedFrame(0)
{
	mState = state;
	updateUniform("tex_base", 0);
}

ProgramRef EffectProgram::getBaseProgram()
{
	return mState->getProgram(mBaseProg);
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

ci::gl::Texture2dRef EffectProgram::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	gl::ScopedTextureBind tex(getBaseProgram()->getColorTexture(b, a), 0);

	gl::ScopedFramebuffer sfbo(a);
	gl::ScopedViewport svp(a->getSize());
	gl::ScopedMatrices mats();
	gl::setMatricesWindow(a->getSize());

	Program::draw();

	return a->getColorTexture();
}

void EffectProgram::draw(ci::gl::FboRef a, ci::gl::FboRef b) {
	ProgramRef p = getBaseProgram();
	if (p) {
		gl::ScopedTextureBind tex(getBaseProgram()->getColorTexture(b, a), 0);
		Program::draw();
	}
}

void EffectProgram::setBase(std::string base)
{
	mBaseProg = base;
}
