#pragma once

#include "Oschader/InputResolver.h"

static const int AUDIO_TEXTURE = 0;
static const int CAMERA_TEXTURE = 1;
static const int KICK = 2;
static const int EQ_TEXTURE = 3;
static const int VOLUME = 4;

struct InputState {
	ci::gl::TextureRef audioTexture;
	ci::gl::TextureRef cameraTexture;
	float volume;
	float kick;
	std::function<ci::gl::TextureRef(int)> eqTexture;
};

class OschaderInputResolver : virtual public input::InputResolver {
public:
	virtual void update(InputState state);
	virtual int parseInputType(std::string type);
	virtual bool isTexture(const input::InputParameters&);
	virtual bool isFloat(const input::InputParameters&);
	virtual float getFloat(const input::InputParameters& ip);
	virtual ci::gl::TextureRef getTexture(const input::InputParameters& ip);

private:
	InputState mState;
};