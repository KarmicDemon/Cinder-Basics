#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

class HelloCinderApp : public App {
  public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;
};

void HelloCinderApp::setup() {
}

void HelloCinderApp::mouseDown(MouseEvent event) {
}

void HelloCinderApp::update() {
}

void HelloCinderApp::draw() {
	/** Figuring stuff out
	// get time-oscillating hue value, "normalized" in range [0, 1]
	float hue = sin(getElapsedSeconds() * 0.5f + 0.5f);
	clear(Color(CM_HSV, hue, 1, 1));
	*/


	/**
	//makes 2 criss-cross lines
	clear(Color(0, 0, 0));

	lineWidth(5);

	color(Color(1, 1, 0));
	drawLine(vec2(0, 0), vec2(getWindowWidth(), getWindowHeight()));

	color(Color(0, 0, 1));
	drawLine(vec2(getWindowWidth(), 0), vec2(0, getWindowHeight()));
	*/


	/**
	//makes Japan flag
	clear(Color(1, 1, 1));

	color(Color(1, 0, 0));
	drawSolidCircle(getWindowCenter(), getWindowWidth() / 6.0f, 100000);
	**/


	/**
	//makes Italy flag
	const Color italy_r(.80f, .17f, .21f);
	const Color italy_g(0, .57f, .27f);
	const Color italy_w(1, 1, 1); 

	const int h = getWindowHeight();
	const int w = getWindowWidth();

	clear(italy_w);

	color(italy_g);
	drawSolidRect(Rectf(0, 0, w / 3.0f, h));

	color(italy_r);
	drawSolidRect(Rectf( (2.0f / 3.0f) * w, 0, w, h));
	**/
}

CINDER_APP(HelloCinderApp, RendererGl)
