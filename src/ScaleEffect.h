#pragma once

#include "PassthroughProgram.h"

class ScaleEffect : public PassthroughProgram {
public:
	static ProgramRef create(ProgramStateRef);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef) override;
	virtual void onUpdateUniform(std::string name, float val) override;

protected:
	ScaleEffect(ProgramStateRef);

private:
	ci::vec2 mScale;
};
