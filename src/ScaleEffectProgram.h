#pragma once

#include "EffectProgram.h"

class ScaleEffectProgram : public EffectProgram {
public:
	static EffectProgramRef create(std::shared_ptr<ProgramState>);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef);
	virtual void draw(ci::gl::FboRef, ci::gl::FboRef) override;
	virtual void updateUniform(std::string, float) override;

protected:
	float mScale;
	ScaleEffectProgram(std::shared_ptr<ProgramState>, ci::gl::BatchRef);
};