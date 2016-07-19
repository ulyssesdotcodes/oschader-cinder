#pragma once

#include "Program.h"

class ProgramRect : public virtual Program {
public:
	static ProgramRef create(ci::gl::GlslProgRef prog, ProgramStateRef);
	static ProgramRef create(std::string, ProgramStateRef);

	virtual std::shared_ptr<ci::Camera> camera() override;
	virtual std::shared_ptr<ci::ivec2> matrixWindow() override;

protected:
	ProgramRect(ci::gl::BatchRef, ProgramStateRef);
};