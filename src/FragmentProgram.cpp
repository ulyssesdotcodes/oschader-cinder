#include "FragmentProgram.h"

using namespace ci;

ProgramRef FragmentProgram::create(ProgramStateRef state, const ci::fs::path path)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(path));
	prog->uniform("i_resolution", (vec2) app::getWindowSize());
	return ProgramRect::create(prog, state);
}
