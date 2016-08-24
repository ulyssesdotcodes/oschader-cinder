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
	gl::ScopedFramebuffer fbob(mFbo);
	gl::clear();

	if(mLayers.size() > 0 && getProgram(mLayers[0])) {

		// Set up the first one separately
		gl::draw(getProgram(mLayers[0])->getColorTexture(base, extra));

		for (std::vector<std::string>::iterator iter = mLayers.begin() + 1; iter != mLayers.end(); ++iter) {
			ProgramRef layerProg = getProgram(*iter);

			if(layerProg) {
				gl::ScopedTextureBind tex(mFbo->getColorTexture(), 0);
				gl::ScopedTextureBind con(layerProg->getColorTexture(base, extra), 1);

				Program::draw();
			}
		}
	}

	ProgramRef effect = getEffect();
	if (effect) {
		return effect->getColorTexture(mFbo, extra);
	}

	return mFbo->getColorTexture();
}

void LayerProgram::addLayer(std::string layer)
{
	mLayers.push_back(layer);
}

void LayerProgram::clearLayers()
{
	mLayers.clear();
}

LayerProgram::LayerProgram(ProgramStateRef state, ci::gl::BatchRef b) : Program(b, state), ProgramRect(b, state)
{
	updateUniform("tex_base", 0);
	updateUniform("tex_layer", 1);
	mFbo = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
}