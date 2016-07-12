#include "ScaleEffectProgram.h"

using namespace ci;

ci::gl::Texture2dRef ScaleEffectProgram::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	gl::scale(vec2(mScale));
	gl::ScopedTextureBind tex(getBaseProgram()->getColorTexture(b, a), 0);
	gl::scale(vec2(1.f / mScale));

	Program::draw();

	return a->getColorTexture();
}

void ScaleEffectProgram::draw(ci::gl::FboRef a, ci::gl::FboRef b) {
	gl::scale(vec2(30.0f));
	gl::ScopedTextureBind tex(getBaseProgram()->getColorTexture(b, a), 0);
	gl::scale(vec2(1.f / 30.f));

	Program::draw();
}

void ScaleEffectProgram::updateUniform(std::string name, float val)
{
	if (name == "scale") {
		mScale = val;
	}
	else {
		EffectProgram::updateUniform(name, val);
	}
}

EffectProgramRef ScaleEffectProgram::create(std::shared_ptr<ProgramState> state)
{
	gl::GlslProgRef prog = gl::context()->getStockShader(gl::ShaderDef().texture());
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	return EffectProgramRef(new ScaleEffectProgram(state, batch));
}

ScaleEffectProgram::ScaleEffectProgram(std::shared_ptr<ProgramState> state, gl::BatchRef batch) : EffectProgram(state, batch), mScale(2.0f)
{
}
