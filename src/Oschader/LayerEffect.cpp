#include "LayerEffect.h"

using namespace ci;

ProgramRef LayerEffect::create(ProgramStateRef state, std::string frag)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new LayerEffect(state, batch));
}

ci::gl::Texture2dRef LayerEffect::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	gl::ScopedFramebuffer fbo(base);
	gl::ScopedTextureBind basebind(base->getColorTexture(), 0);

	Program::draw();

	auto e = getEffect();
	if (e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}

LayerEffect::LayerEffect(ProgramStateRef state, ci::gl::BatchRef b) : Program(b, state), ProgramRect(b, state)
{
	updateUniform("tex_base", 0);
}