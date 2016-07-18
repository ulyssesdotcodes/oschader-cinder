#include "FadeEffect.h"

using namespace ci;

ProgramRef FadeEffect::create(ProgramStateRef state)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset("fade.frag"));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new FadeEffect(state, batch));
}

ci::gl::Texture2dRef FadeEffect::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef last)
{
	{
		gl::ScopedFramebuffer fbo(last);
		if (getEffect()) {
			// Draw last frame with the effects
			gl::draw(getEffect()->getColorTexture(mLastFrame, last));
		}
		else {
			gl::pushViewport();
			gl::pushMatrices();

			gl::setMatricesWindow(*matrixWindow());

			gl::draw(mLastFrame->getColorTexture());

			gl::popMatrices();
			gl::popViewport();
		}
	}

	{
		// Scope mLastFrame to be updated
		gl::ScopedFramebuffer lastF(mLastFrame);

		gl::ScopedTextureBind baseT(base->getColorTexture(), 0);
		gl::ScopedTextureBind lastT(last->getColorTexture(), 1);

		// Draw the base 
		Program::draw();
	}

	return mLastFrame->getColorTexture();
}

FadeEffect::FadeEffect(ProgramStateRef state, ci::gl::BatchRef r) : Program(r, state), ProgramRect(r, state)
{
	mLastFrame = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
	updateUniform("tex_last", 1);
	updateUniform("tex_base", 0);
}
