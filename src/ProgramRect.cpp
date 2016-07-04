#include "ProgramRect.h"

using namespace ci;

ProgramRect::ProgramRect(gl::BatchRef batch) : Program(batch)
{
}

BaseProgramRef ProgramRect::create(gl::GlslProgRef prog)
{
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	ProgramRef rectProg = ProgramRef(new ProgramRect(batch));
	return FboProgram::create(rectProg);
}

std::shared_ptr<Camera> ProgramRect::camera()
{
	return nullptr;
}

std::shared_ptr<ci::ivec2> ProgramRect::matrixWindow()
{
	return std::make_shared<ci::ivec2>(app::getWindow()->getSize());
}