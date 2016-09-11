#pragma once

#include "Program.h"

#include "cinder/Capture.h"

class TexInputProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

	virtual void updateUniform(std::string name, std::string val, float mod) override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;
	virtual void update(input::InputState) override;

protected:
	TexInputProgram(ProgramStateRef);

private:
	input::InputState mLastInputState;
	ci::CaptureRef mCapture;
	input::InputType mInput;
	float mMod;

};
