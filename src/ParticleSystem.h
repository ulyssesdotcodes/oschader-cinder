//----------------------------------------------------------------------------------
// File:        ComputeParticles/ParticleSystem.cpp
// Url:         https://github.com/NVIDIAGameWorks/OpenGLSamples/tree/master/samples/es3aep-kepler/ComputeParticles
// SDK Version: v1.2 
// Email:       gameworks@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------------


#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/Utilities.h"
#include "cinder/Rand.h"
#include "cinder/params/Params.h"
#include "cinder/gl/Ssbo.h"
#include "cinder/Arcball.h"

#include "Program.h"


#define LIGHT_RADIUS	1.5f // Must be at least 1

const static int WORK_GROUP_SIZE = 128;
const static int NUM_PARTICLES = 1 << 14;

class ParticleSystem;
typedef std::shared_ptr<ParticleSystem> ParticleSystemRef;

//! This sample was ported from https://github.com/NVIDIAGameWorks/OpenGLSamples/tree/master/samples/es3aep-kepler/ComputeParticles
class ParticleSystem : public Program {
  public:
	 static ParticleSystemRef create(ProgramStateRef, std::string);
	ParticleSystem(ProgramStateRef, ci::gl::BatchRef, ci::gl::VboRef, ci::gl::SsboRef, ci::gl::SsboRef, ci::gl::GlslProgRef);

	virtual std::shared_ptr<ci::Camera> camera();
	virtual std::shared_ptr<ci::ivec2> matrixWindow();

	virtual void update(input::InputState) override;
	virtual void draw();
	virtual void onUpdateUniform(std::string name, float val) override;

	
	void updateParticleSystem();
	void setupNoiseTexture3D();
	
	ci::gl::VboRef mVBO;
	ci::gl::GlslProgRef mRenderProg;
	ci::gl::GlslProgRef mUpdateProg;
	ci::gl::SsboRef mPos;
	ci::gl::SsboRef mVel;
	ci::gl::VboRef mIndicesVbo;

	ci::gl::Texture3dRef mNoiseTex;
	std::shared_ptr<ci::CameraPersp>	mCam;
	int mNoiseSize;
	float mSpriteSize;
	bool mEnableAttractor;
	bool mAnimate;
	bool mReset;
	float mTime;
	float mPrevElapsedSeconds;

	bool mDrawnOnce;
};
