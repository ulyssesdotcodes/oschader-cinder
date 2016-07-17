#pragma once

#include "Program.h"
#include "ProgramState.h"

typedef std::shared_ptr<class EffectProgram> EffectProgramRef;

class EffectProgram : public Program {
public:
	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();

	virtual ci::gl::Texture2dRef getColorTexture(ci::gl::FboRef, ci::gl::FboRef);

	static EffectProgramRef create(std::shared_ptr<ProgramState>, std::string frag);

	virtual void setCombinator(std::string) override;

protected:
	EffectProgram(std::shared_ptr<ProgramState>, ci::gl::BatchRef prog);

private:
	std::string mBaseProg;

	uint32_t mLastUpdatedFrame;
};