#pragma once

#include "EffectRect.h"

class LayerEffect : public virtual ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, std::string);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	LayerEffect(ProgramStateRef, ci::gl::BatchRef);
};
