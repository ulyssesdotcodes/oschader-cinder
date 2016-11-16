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

#include "ParticleSystem.h"

using namespace ci;

float sfrand()
{
	return ci::randPosNegFloat( -1.0f, 1.0f );
}

ParticleSystem::ParticleSystem(ProgramStateRef state, gl::BatchRef b, gl::VboRef indices, gl::SsboRef pos, gl::SsboRef vel, gl::GlslProgRef update, int numParticles) : Program(b, state),
	mCam(new CameraPersp( app::getWindowWidth(), app::getWindowHeight(), 90.0f, 5.f, 500.0f )),
	  mNoiseSize( 16 ),
	  mSpriteSize( 0.1f ),
	  mEnableAttractor( false ),
	  mAnimate( true ),
	  mReset( false ),
	  mTime( 0.0f ),
	mLastUpdate(0.0f),
	  mPrevElapsedSeconds( 0.0f ),
	mDrawnOnce(false),
	mNumParticles(numParticles),
	mRotation(0.0f)
{
	mPos = pos;
	mVel = vel;
	mIndicesVbo = indices;
	mUpdateProg = update;

	mEnableAttractor = false;
	mAnimate = true;
	mReset = false;
	mTime = 0.0f;
	mPrevElapsedSeconds = 0.0f;
	mNoiseSize = 16;

	setupNoiseTexture3D();
	mNumParticles = numParticles;

	CI_CHECK_GL();

	mCam->lookAt( vec3( 0.0f, 0.0f, -40.0f ), vec3( 0 ) );
}

ParticleSystemRef ParticleSystem::create(ProgramStateRef state, std::string comp, int numParticles)
{
	std::vector<uint32_t> indices( numParticles  * 6);
	// the index buffer is a classic "two-tri quad" array.
	// This may seem odd, given that the compute buffer contains a single
	// vector for each particle.  However, the shader takes care of this
	// by indexing the compute shader buffer with a /4.  The value mod 4
	// is used to compute the offset from the vertex site, and each of the
	// four indices in a given quad references the same center point
	for( size_t i = 0, j = 0; i < numParticles; ++i ) {
		size_t index = i << 2;
		indices[j++] = index;
		indices[j++] = index + 1;
		indices[j++] = index + 2;
		indices[j++] = index;
		indices[j++] = index + 2;
		indices[j++] = index + 3;
	}

	gl::enableVertexAttribArray(0);
	auto vbo = gl::Vbo::create<uint32_t>( GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW );

	gl::GlslProgRef renderProg = gl::GlslProg::create( gl::GlslProg::Format().vertex( app::loadAsset( "shaders/particles/render.vert" ) )
			.fragment( app::loadAsset( "shaders/particles/render.frag" ) ) );
	renderProg->uniform("spriteSize", 0.25f);
	gl::VboMeshRef vboMesh = gl::VboMesh::create(numParticles * 6, GL_TRIANGLES, { gl::VboMesh::Layout().usage(GL_STATIC_DRAW).attrib(geom::POSITION, 1) }, numParticles * 6, GL_UNSIGNED_INT, vbo);
	gl::BatchRef batch = gl::Batch::create(vboMesh, renderProg);
	auto pos = gl::Ssbo::create( sizeof(vec4) * numParticles, nullptr, GL_STATIC_DRAW );
	auto vel = gl::Ssbo::create( sizeof(vec4) * numParticles, nullptr, GL_STATIC_DRAW );

	float size = 1;
	vec4 *posp = reinterpret_cast<vec4*>( pos->map( GL_WRITE_ONLY ) );
	for( size_t i = 0; i < numParticles; ++i ) {
		posp[i] = vec4( sfrand() * size, sfrand() * size, sfrand() * size, 0.0f );
	}
	pos->unmap();

	vec4 *velp = reinterpret_cast<vec4*>( vel->map( GL_WRITE_ONLY ) );
	for( size_t i = 0; i < numParticles; ++i ) {
		velp[i] = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	}
	vel->unmap();

	CI_CHECK_GL();

	auto update = gl::GlslProg::create( gl::GlslProg::Format().compute( app::loadAsset( "shaders/particles/" +  comp)));
	update->uniform("numParticles", (float) numParticles);
	update->uniform("i_delta", 0.016f);
	update->uniform("i_speed", 64.f);
	update->uniform("i_separation", 0.01f);
	update->uniform("i_cohesion", 0.01f);
	update->uniform("i_alignment", 0.01f);
	update->uniform("i_lastUpdate", 0.0f);

	return ParticleSystemRef(new ParticleSystem(state, batch, vbo, pos, vel, update, numParticles));
}

std::shared_ptr<ci::Camera> ParticleSystem::camera()
{
	return mCam;
}

std::shared_ptr<ci::ivec2> ParticleSystem::matrixWindow()
{
	return nullptr;
}

void ParticleSystem::onUpdate()
{
	bindInputTexes(mUpdateProg);

	updateParticleSystem();
	mDrawnOnce = true;
}

void ParticleSystem::draw()
{
	gl::clear(Color::black());
	gl::bindBufferBase( mPos->getTarget(), 1, mPos );
	gl::ScopedBuffer scopedindices(mIndicesVbo);
	Program::draw();
}

void ParticleSystem::onUpdateUniform(std::string name, float val)
{
	if(mDrawnOnce) {
		if (name.compare("time") == 0) {
			if (val < mTime) {
				mRotation++;
				mUpdateProg->uniform("i_timeRot", mRotation);
			}

			mTime = val;
		}
		mUpdateProg->uniform("i_" + name, val);
	}
}

void ParticleSystem::updateParticleSystem()
{
	// Invoke the compute shader to integrate the particles
	gl::ScopedGlslProg prog( mUpdateProg );

	//mUpdateProg->uniform("i_lastUpdate", mLastUpdate);
	mLastUpdate = mTime;

	//gl::ScopedTextureBind scoped3dTex( mNoiseTex );

	//ScopedBufferBase scopedPosBuffer( mPos, 1 );
	//ScopedBufferBase scopedVelBuffer( mVel, 2 );
	gl::bindBufferBase( mPos->getTarget(), 1, mPos );
	gl::bindBufferBase( mPos->getTarget(), 2, mVel );

	gl::dispatchCompute( mNumParticles / WORK_GROUP_SIZE, 1, 1 );
	// We need to block here on compute completion to ensure that the
	// computation is done before we render
	gl::memoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT  );
}

void ParticleSystem::setupNoiseTexture3D()
{
	gl::Texture3d::Format tex3dFmt;
	tex3dFmt.setWrapR( GL_REPEAT );
	tex3dFmt.setWrapS( GL_REPEAT );
	tex3dFmt.setWrapT( GL_REPEAT );
	tex3dFmt.setMagFilter( GL_LINEAR );
	tex3dFmt.setMinFilter( GL_LINEAR );
	tex3dFmt.setDataType( GL_FLOAT );
	tex3dFmt.setInternalFormat( GL_RGBA8_SNORM );

	const int width = mNoiseSize;
	const int height = mNoiseSize;
	const int depth = mNoiseSize;

	std::vector<float> data( width * height * depth * 4 );
	int i = 0;
	for( int z = 0; z < depth; ++z ) {
		for( int y = 0; y < height; ++y ) {
			for( int x = 0; x < width; ++x ) {
				data[i++] = sfrand();
				data[i++] = sfrand();
				data[i++] = sfrand();
				data[i++] = sfrand();
			}
		}
	}

	mNoiseTex = gl::Texture3d::create( mNoiseSize, mNoiseSize, mNoiseSize, tex3dFmt );
	mNoiseTex->update( data.data(), GL_RGBA, tex3dFmt.getDataType(), 0, mNoiseTex->getWidth(),
		mNoiseTex->getHeight(), mNoiseTex->getDepth() );
}