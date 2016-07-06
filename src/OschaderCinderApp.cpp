#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Osc.h"

#include "ProgramFactory.h"

#include "AdditiveProgram.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OschaderCinderApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;

	void addProgram(BaseProgramRef, int);

private:
	std::shared_ptr<osc::ReceiverUdp> mOscReceiver;

	std::array<BaseProgramRef, 8> mPrograms;
};

void OschaderCinderApp::setup()
{
	ProgramFactory factory;

	mOscReceiver = std::shared_ptr<osc::ReceiverUdp>(new osc::ReceiverUdp(9001));

	for (int i = 0; i < mPrograms.size(); i++) {
		mOscReceiver->setListener("/shaders/" + std::to_string(i), [&](osc::Message msg) {
			addProgram(AdditiveProgram::create(factory.createProgram(msg.getArgString(0))), i);
		});

		mOscReceiver->setListener("/shaders/" + std::to_string(i) + "/uniform", [&](osc::Message msg) {
			if (mPrograms[i]) {
				mPrograms[i]->updateUniform(msg.getArgString(0), msg.getArgFloat(1));
			}
		});
	}
}

void OschaderCinderApp::update()
{
	float time = app::getElapsedSeconds();
	std::for_each(mPrograms.begin(), mPrograms.end(), [time](ProgramRef prog) {
		if (prog) {
			prog->updateUniform("time", time);
		}
	});
}

void OschaderCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	if (mPrograms[0]) {
		mPrograms[0]->draw();
	}
}

void OschaderCinderApp::addProgram(BaseProgramRef p, int i)
{
	mPrograms[i] = p;
	if (i > 0 && mPrograms[i - 1]) {
		mPrograms[i - 1]->mappend(p);
	}
	if (i < mPrograms.size() - 1 && mPrograms[i + 1]) {
		p->mappend(mPrograms[i + 1]);
	}
}

CINDER_APP(OschaderCinderApp, RendererGl(), [&](App::Settings *settings) {
	//FullScreenOptions options;
	//std::vector<DisplayRef> displays = Display::getDisplays();
	//settings->setConsoleWindowEnabled();
	//settings->setFullScreen(true, options);	
	//if (displays.size() > 1) {
	//	settings->setDisplay(displays[1]);
	//}
	//settings->setFrameRate(60.0f);
})