#include "FragmentProgram.h"

using namespace ci;

BaseProgramRef FragmentProgram::create(const ci::fs::path path)
{
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(path));
	prog->uniform("i_resolution", (vec2) app::getWindowSize());
	return ProgramRect::create(prog);
}
