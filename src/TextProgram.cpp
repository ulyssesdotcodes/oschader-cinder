#include "TextProgram.h"

#include "cinder/Text.h"

using namespace ci;

ProgramRef TextProgram::create(ProgramStateRef state)
{
	return ProgramRef(new TextProgram(state));
}

std::shared_ptr<ci::Camera> TextProgram::camera()
{
	return std::shared_ptr<ci::Camera>();
}

std::shared_ptr<ci::ivec2> TextProgram::matrixWindow()
{
	return std::shared_ptr<ci::ivec2>();
}

void TextProgram::updateUniform(std::string name, std::string val)
{
	if (name.compare("text") == 0 && val.compare(mText) != 0) {
		mText = val;
		auto font = Font(mFont, 72);
		TextBox tbox = TextBox().alignment( TextBox::RIGHT ).font( font ).text( mText );
		tbox.setColor( Color::white() );
		mTextSize = tbox.measure();
		mTextTexture = gl::Texture2d::create( tbox.render() );
	}
}

ci::gl::Texture2dRef TextProgram::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra)
{
	if(mTextTexture) {
		gl::ScopedFramebuffer fbo(base);
		gl::clear(Color::black());

		gl::pushViewport();
		gl::pushMatrices();
		gl::setMatricesWindow(app::getWindow()->getSize());
		vec2 offset = (vec2)(app::getWindowSize() - mTextTexture->getSize()) * 0.5f;
		Area dst = Area(Rectf(vec2(0), mTextSize));
		dst.offset(offset);
		gl::draw(mTextTexture, dst);
		gl::popMatrices();
		gl::popViewport();
	}

	auto e = getEffect();
	if(e) {
		return e->getColorTexture(base, extra);
	}

	return base->getColorTexture();
}

TextProgram::TextProgram(ProgramStateRef state) : Program(nullptr, state), mFont("Arial")
{
}
