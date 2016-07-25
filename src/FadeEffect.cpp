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
    ProgramRef effect = getEffect();
    if(effect) {
        
        {
        	gl::ScopedFramebuffer fbo(last);
        	gl::ScopedTextureBind texl(mLastFrame->getColorTexture(), 1);
        	gl::ScopedTextureBind tex(effect->getColorTexture(base, last), 0);
            
            gl::clear(Color::black());

        	Program::draw();
        }
        
        {
        	gl::ScopedFramebuffer fbo(mLastFrame);
            gl::clear(Color::black());
            gl::draw(last->getColorTexture());
        }
    }
    else {
        gl::ScopedFramebuffer fbo(mLastFrame);
        
    	gl::ScopedTextureBind tex(base->getColorTexture(), 0);
    	gl::ScopedTextureBind texl(mLastFrame->getColorTexture(), 1);
        
        Program::draw();
    }
    

	return mLastFrame->getColorTexture();

}

FadeEffect::FadeEffect(ProgramStateRef state, ci::gl::BatchRef r) : Program(r, state), ProgramRect(r, state)
{
	gl::Texture::Format fmt;
	fmt.setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	fmt.setBorderColor(Color::black());
	gl::Fbo::Format fboFmt;
	fboFmt.setColorTextureFormat(fmt);
	mLastFrame = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight(), fboFmt);
	updateUniform("tex_base", 0);
	updateUniform("tex_last", 1);
}
