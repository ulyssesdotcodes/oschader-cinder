#include "EffectRect.h"

using namespace ci;

ProgramRef EffectRect::create(ProgramStateRef state, std::string frag)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new EffectRect(state, batch));
}

ci::gl::Texture2dRef EffectRect::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	ci::gl::ScopedTextureBind tex(base->getColorTexture(), 0);
	return Program::getColorTexture(extra, base);
}

EffectRect::EffectRect(ProgramStateRef state, gl::BatchRef b) : Program(b, state), ProgramRect(b, state) {}
