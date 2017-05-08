#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

class Circle {
public: 
	Circle(vec2 center, float radius, Color fillColor) 
		: center(center), radius(radius), fillColor(fillColor) {}

	void draw() {
		color(fillColor);
		drawSolidCircle(center, radius);	
	}
 private:
	Color fillColor;
	float radius;
	vec2 center;
};

class HelloCinderApp : public App {
public:
	void draw() override;
	void keyDown(KeyEvent event) override;
	void mouseDown(MouseEvent event) override;
	void setup() override;
	void update() override;
 private:
	vector<Circle> circles;

	Circle generateRandomCircleAt(vec2 center) {
		float radius = Rand::randFloat(10.0f, 50.0f);
		Color color(CM_HSV, Rand::randFloat(0.0f, 1.0f), 1.0f, 1.0f);

		return Circle(center, radius, color);
	}
};

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

	
	//uses user input
	clear(Color(0, 0, 0));

	for (auto& circle : circles) {
		circle.draw();
	}

}

void HelloCinderApp::keyDown(KeyEvent event) {
	if (event.getChar() == 'c' || event.getChar() == 'C') {
		circles.clear();
	}

	return;
}

void HelloCinderApp::mouseDown(MouseEvent event) {
	if (event.isLeft()) {
		circles.push_back(generateRandomCircleAt(event.getPos()));
		return;
	}

	if (event.isRight() && !circles.empty()) {
		circles.pop_back();
		return;
	}
}

void HelloCinderApp::setup() {
	Rand::randomize();
}

void HelloCinderApp::update() {
}


CINDER_APP(HelloCinderApp, RendererGl)
