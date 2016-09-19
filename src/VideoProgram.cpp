#include "VideoProgram.h"

using namespace ci;

VideoProgram::VideoProgram(ProgramStateRef state) : Program(nullptr, state), mLoaded(false)
{
}

ProgramRef VideoProgram::create(ProgramStateRef state)
{
	return ProgramRef(new VideoProgram(state));
}

std::shared_ptr<ci::Camera> VideoProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> VideoProgram::matrixWindow()
{
	return std::shared_ptr<ci::ivec2>();
}

void VideoProgram::updateUniform(std::string name, std::string val)
{
	if (name.compare("video") == 0 && val.compare(mPath) != 0 && fs::exists(app::getAssetPath("videos/" + val))) {
		mPath = val;
		mVideoPos = 0.0f;
		mVideo.loadMovie(app::getAssetPath("videos/" + val).string());
		mVideo.setLoop(true);
		mVideo.play();
		mLoaded = true;
	}
}

void VideoProgram::onUpdateUniform(std::string name, float val)
{
	if (name.compare("speed") == 0 && mVideo.getSpeed() != val) {
		mVideo.setSpeed(val);
	}
}

void VideoProgram::update(input::InputState s)
{
	Program::update(s);
	if (mLoaded) {
		mVideo.update();
	}
}

ci::gl::Texture2dRef VideoProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	if(mVideo.isPlaying()) {
		gl::ScopedFramebuffer fbo(base);
		gl::clear(Color::black());

		gl::pushViewport();
		gl::pushMatrices();
		gl::setMatricesWindow(app::getWindow()->getSize());
		vec2 offset = (vec2)(app::getWindowSize() - mVideo.getTexture()->getSize()) * 0.5f;
		auto dst = Area(Rectf(0, 0, mVideo.getWidth(), mVideo.getHeight()));
		dst.offset(offset);
		mVideo.draw(dst.x1, dst.y1);
		gl::popMatrices();
		gl::popViewport();
	}

	auto e = getEffect();
	if(e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}
