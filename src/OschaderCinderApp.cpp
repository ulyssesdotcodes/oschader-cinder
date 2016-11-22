#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <regex>

#include "Osc.h"

#include "AudioSource.h"
#include "CameraSource.h"
#include "InputResolver.h"
#include "OschaderInputState.h"
#include "ProgramFactory.h"
#include "ProgramState.h"

//#include "AdditiveProgram.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OschaderCinderApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
	void resize() override;

private:
	std::shared_ptr<OschaderInputResolver> mInputResolver;

	std::shared_ptr<osc::ReceiverUdp> mOscReceiver;

	ci::gl::FboRef a, b;

	std::shared_ptr<ProgramState> mState;
	ProgramFactory mFactory;
	std::shared_ptr<AudioSource> mAudioSource;
	std::shared_ptr<CameraSource> mCameraSource;
};

void OschaderCinderApp::setup()
{
	mState = std::make_shared<ProgramState>();
	mFactory.setup(mState);
	
	mAudioSource = std::shared_ptr<AudioSource>(new AudioSource());
	mAudioSource->setup();

	mCameraSource = std::shared_ptr<CameraSource>(new CameraSource());

	mOscReceiver = std::shared_ptr<osc::ReceiverUdp>(new osc::ReceiverUdp(9001));
	mOscReceiver->bind();
	mOscReceiver->listen();

	mOscReceiver->setListener("/progs/effect", [&](const osc::Message msg) {
		ProgramRef s = mState->getProgram(msg.getArgString(0));
		if (s) {
			app::console() << msg.getArgString(0) << " eff: " << msg.getArgString(1) << std::endl;
			s->setEffect(msg.getArgString(1));
		}
	});

	mOscReceiver->setListener("/progs/effect/clear", [&](const osc::Message msg) {
		ProgramRef s = mState->getProgram(msg.getArgString(0));
		if (s) {
			s->clearEffect();
		}
	});

	mOscReceiver->setListener("/progs/connections", [&](const osc::Message msg) {
		ProgramRef s = mState->getProgram(msg.getArgString(0));
		if (s) {
			s->clearLayers();
			for (int i = 1; i < msg.getNumArgs(); ++i) {
				s->addLayer(msg.getArgString(i));
			}
		}
	});

	mOscReceiver->setListener("/progs", [&](const osc::Message msg) {
		mState->setProgram(msg.getArgString(0), msg.getArgString(1), std::bind(&ProgramFactory::createProgram, mFactory, msg.getArgString(1)));
	});

	mOscReceiver->setListener("/progs/clear", [&](const osc::Message msg) {
		mState->clearProgram(msg.getArgString(0));
	});

	mOscReceiver->setListener("/progs/uniform", [&](const osc::Message msg) {
		ProgramRef p = mState->getProgram(msg.getArgString(0));
		if (p) {
			if(msg.getArgType(2) == osc::ArgType::FLOAT) {
				p->updateUniform(msg.getArgString(1), msg.getArgFloat(2));
			}
			else if (msg.getArgType(2) == osc::ArgType::STRING) {
				std::string arg = msg.getArgString(2);
				if (arg.compare("input") == 0) {
					std::vector<float> inputArgs;
					for (int i = 3; i < msg.getNumArgs(); ++i) {
						if (msg.getArgType(i) == osc::ArgType::FLOAT) {
							inputArgs.push_back(msg.getArgFloat(i));
						}
					}

					p->updateInputUniform(msg.getArgString(1), msg.getArgString(3), inputArgs);
				}
				else if (arg.compare("string") == 0) {
					p->updateUniform(msg.getArgString(1), msg.getArgString(3));
				}
			}
		}
	});


	gl::Texture::Format fmt;
	fmt.setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	fmt.setBorderColor(ColorA(0, 0, 0));

	gl::Fbo::Format fboFmt;
	fboFmt.setColorTextureFormat(fmt);
	a = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight(), fboFmt);
	b = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight(), fboFmt);

	mInputResolver = std::make_shared<OschaderInputResolver>();
	update();
}

void OschaderCinderApp::update()
{
	InputState is;
	is.audioTexture = mAudioSource->getMagSpectrumTexture();
	is.volume = mAudioSource->getVolume();
	auto eqs = mAudioSource->getEqs(128);
	is.kick = eqs[1] + eqs[2];
	is.eqTexture = std::bind(&AudioSource::getEqTexture, mAudioSource, std::placeholders::_1);
	is.cameraTexture = mCameraSource->getTexture();

	mInputResolver->update(is);

	mState->update([&, is](std::shared_ptr<Program> prog) {
		prog->update(mInputResolver);
	});
}

void OschaderCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	ProgramRef s = mState->getProgram("s0");
	if (s) {
		gl::draw(s->getColorTexture(a, b));
	}

	CI_CHECK_GL();
}

void OschaderCinderApp::resize()
{
	gl::Texture::Format fmt;
	fmt.setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	fmt.setBorderColor(ColorA(0, 0, 0));

	gl::Fbo::Format fboFmt;
	fboFmt.setColorTextureFormat(fmt);
	a = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight(), fboFmt);
	b = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight(), fboFmt);
}

CINDER_APP(OschaderCinderApp, RendererGl(), [&](App::Settings *settings) {
	FullScreenOptions options;
	std::vector<DisplayRef> displays = Display::getDisplays();
	settings->setFullScreen(false);	
	settings->setWindowSize(1920 * 2, 1080);
	if (displays.size() > 1) {
		settings->setDisplay(displays[1]);
		settings->setWindowSize(displays[1]->getSize());
	}
	settings->setFrameRate(60.0f);
})
