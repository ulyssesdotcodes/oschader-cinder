#pragma once

#include "Program.h"

class PassthroughProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;
	virtual void updateUniform(std::string name, std::string val) override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	PassthroughProgram(ProgramStateRef state);

private:
	std::string mProgram;
};
