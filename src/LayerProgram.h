#pragma once

#include "EffectRect.h"

class LayerProgram : public virtual ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, std::string);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;

protected:
	LayerProgram(ProgramStateRef, ci::gl::BatchRef);
	ProgramRef getConnection();

private:
	std::string mConnection;
	ci::gl::FboRef mFbo; 
};