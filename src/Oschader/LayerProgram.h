#pragma once

#include "EffectRect.h"

class LayerProgram : public virtual ProgramRect {
public:
	static ProgramRef create(ProgramStateRef, std::string);
	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef base, ci::gl::FboRef extra) override;
	virtual void addLayer(std::string) override;
	virtual void clearLayers() override;

protected:
	LayerProgram(ProgramStateRef, ci::gl::BatchRef);

private:
	std::vector<std::string> mLayers;
	ci::gl::FboRef mFbo; 
};