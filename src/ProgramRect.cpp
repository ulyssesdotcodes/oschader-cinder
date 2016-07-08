#include "ProgramRect.h"

using namespace ci;

ProgramRect::ProgramRect(gl::BatchRef batch) : Program(batch)
{
}

ProgramRef ProgramRect::create(gl::GlslProgRef prog)
{
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new ProgramRect(batch));
}

std::shared_ptr<Camera> ProgramRect::camera()
{
	return nullptr;
}

std::shared_ptr<ci::ivec2> ProgramRect::matrixWindow()
{
	return std::make_shared<ci::ivec2>(app::getWindow()->getSize());
}