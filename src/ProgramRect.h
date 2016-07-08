#pragma once

#include "Program.h"
#include "FboProgram.h"

class ProgramRect : public Program {
public:
	static ProgramRef create(ci::gl::GlslProgRef prog);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

protected:
	ProgramRect(ci::gl::BatchRef);
};