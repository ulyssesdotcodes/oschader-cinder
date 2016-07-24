#pragma once

#include "Program.h"

class PassthroughProgram : public virtual Program {
public:
	static ProgramRef create(ProgramStateRef state);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

	virtual void updateUniform(std::string name, float val) override { ci::app::console() << "Tried to set uniform of passthrough" << std::endl; };
	virtual void updateUniform(std::string name, std::string, float modifier) override {ci::app::console() << "Tried to set uniform of passthrough" << std::endl; };
	virtual void updateUniform(std::string name, int val) override {ci::app::console() << "Tried to set uniform of passthrough" << std::endl; };

protected:
	PassthroughProgram(ProgramStateRef state);
};
