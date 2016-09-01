#include "ScaleEffect.h"

using namespace ci;

ProgramRef ScaleEffect::create(ProgramStateRef s)
{
	return ProgramRef(new ScaleEffect(s));
}

ci::gl::Texture2dRef ScaleEffect::getColorTexture(ci::gl::FboRef base, ci::gl::FboRef _)
{
	auto effect = getEffect();

	if (effect) {
		gl::scale(mScale);
		gl::Texture2dRef eff = effect->getColorTexture(base, _);
		gl::scale(vec2(1) / mScale);
		return eff;
	}

	return base->getColorTexture();
}

void ScaleEffect::onUpdateUniform(std::string name, float val)
{
	if (name == "scale") {
		if (abs(val) < 0.01) {
			val = glm::sign(val) * 0.01;
		}
		mScale = vec2(val);
	}
}

ScaleEffect::ScaleEffect(ProgramStateRef state) : PassthroughProgram(state), Program(nullptr, state), mScale(vec2(1))
{
}
