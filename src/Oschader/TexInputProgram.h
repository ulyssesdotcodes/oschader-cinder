#pragma once

#include "Program.h"

#include "cinder/Capture.h"

class TexInputProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

	virtual void updateInputUniform(std::string name, std::string val, std::vector<float> modifiers) override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	TexInputProgram(ProgramStateRef);

private:
	std::string mInput;
	ci::CaptureRef mCapture;
};
