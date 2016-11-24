#pragma once

#include "Program.h"

#include "cinder/gl/gl.h"

class TextProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

	virtual void updateUniform(std::string name, std::string val) override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	TextProgram(ProgramStateRef);

private:
	std::string mText;
	std::string mFont;
	ci::gl::TextureRef mTextTexture;
	ci::vec2 mTextSize;
};
