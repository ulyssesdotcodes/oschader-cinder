#include "LayerProgram.h"

using namespace ci;

ProgramRef LayerProgram::create(ProgramStateRef state, std::string frag)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new LayerProgram(state, batch));
}

ci::gl::Texture2dRef LayerProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{

	ProgramRef effect = getEffect();
	if(effect) {
		gl::ScopedTextureBind texl(effect->getColorTexture(extra, mFbo), 1);
		gl::ScopedTextureBind tex(base->getColorTexture(), 0);

		gl::ScopedFramebuffer fbob(mFbo);
		Program::draw();

		return mFbo->getColorTexture();
	}

	return base->getColorTexture();
}

LayerProgram::LayerProgram(ProgramStateRef state, ci::gl::BatchRef b) : Program(b, state), ProgramRect(b, state)
{
	updateUniform("tex_base", 0);
	updateUniform("tex_layer", 1);
	mFbo = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
}

ProgramRef LayerProgram::getConnection()
{
	return getProgram(mConnection);
}
