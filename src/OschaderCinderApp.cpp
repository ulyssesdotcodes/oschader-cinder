#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Osc.h"

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

private:
	std::shared_ptr<osc::ReceiverUdp> mOscReceiver;

	ci::gl::FboRef a, b;

	ProgramFactory mFactory;
	ProgramState mState;
};

//s $ p "fade" ["a" 0.98] "s1"
//pr "s1" $ p "sine"
//pr "a" $ p "moveY" [1] "a1"
//pr "a1" $ p "scale" [1]
//
//["/shader", "fade"]
//["/shader/uniform/prog", ["a"]]
//["/shader/uniform/fade", [0.98]]
//["/shader/next", ["s1"]]
//
//["/progs/s1", "sine"]
//
//["/progs/a", "moveY"]
//["/progs/a/uniform", [1]]
//["/progs/a/next", ["a1"]]
//
//["/progs/a1", ["scale"]]
//["/progs/a1/uniform/scale", [1]]


void OschaderCinderApp::setup()
{
	mOscReceiver = std::shared_ptr<osc::ReceiverUdp>(new osc::ReceiverUdp(9001));
	mOscReceiver->bind();
	mOscReceiver->listen();

	mOscReceiver->setListener("/shader", [&](const osc::Message msg) {
		mState.setProgram("s", msg.getArgString(0));
	});

	mOscReceiver->setListener("/shader/uniform/*", [&](const osc::Message msg) {
		ProgramRef s = mState.getProgram("s");
		if (s) {
			s->updateUniform(msg.getAddress().substr(16), msg.getArgFloat(0));
		}
	});

	mOscReceiver->setListener("/progs/*", [&](const osc::Message msg) {
		mState.setProgram(msg.getAddress().substr(7), msg.getArgString(0));
	});

	//for (int i = 0; i < mPrograms.size(); i++) {
		//mOscReceiver->setListener("/shaders/" + std::to_string(i), [&, i](osc::Message msg) {
		//	addProgram(mFactory.createProgram(msg.getArgString(0)), i);
		//});

		//mOscReceiver->setListener("/shaders/" + std::to_string(i) + "/uniform", [&](osc::Message msg) {
		//	if (mPrograms[i]) {
		//		mPrograms[i]->updateUniform(msg.getArgString(0), msg.getArgFloat(1));
		//	}
		//});
	//}

	a = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
	b = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
}

void OschaderCinderApp::update()
{
}

void OschaderCinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	ProgramRef s = mState.getProgram("s");
	if (s) {
		s->draw(a, b);
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
