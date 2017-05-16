#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicAnimationApp : public App {
public:
	void draw() override;
	void setup() override;
private:
	vec2 position;
};

void BasicAnimationApp::setup() {
	position = getWindowCenter();
}

void BasicAnimationApp::draw() {
	gl::clear(Color(0, 0, 0)); 

	position.x++;
	position.y++;

	gl::color(Color(1, 1, 0));
	gl::drawSolidCircle(position, 100);
}

CINDER_APP(BasicAnimationApp, RendererGl, [&](App::Settings * settings) {
	settings->setFrameRate(60);
	settings->setWindowSize(800, 600);
})
