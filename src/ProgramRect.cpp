#include "ProgramRect.h"

using namespace ci;

ProgramRect::ProgramRect(gl::BatchRef batch, ProgramStateRef state) : Program(batch, state)
{
	updateUniform("tex_base", 0);
}

ProgramRef ProgramRect::create(gl::GlslProgRef prog, ProgramStateRef state)
{
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return ProgramRef(new ProgramRect(batch, state));
}

ProgramRef ProgramRect::create(std::string frag, ProgramStateRef state)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	return create(prog, state);
}

std::shared_ptr<Camera> ProgramRect::camera()
{
	return nullptr;
}

std::shared_ptr<ci::ivec2> ProgramRect::matrixWindow()
{
	return std::make_shared<ci::ivec2>(app::getWindow()->getSize());
}