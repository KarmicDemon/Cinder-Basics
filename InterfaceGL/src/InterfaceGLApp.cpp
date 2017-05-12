#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/params/Params.h"
#include "cinder/Surface.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class InterfaceGLApp : public App {
public:
	void draw() override;
	void keyDown(KeyEvent event) override;
	void setup() override;
	void update() override;
private:
	bool showOriginal;

	gl::TextureRef in;
	gl::TextureRef out;

	Surface32f imageInput;
	Surface32f imageOutput;

	float brightness;
	float prevBrightness;
	float contrast;
	float prevContrast;

	params::InterfaceGl params;

	float adjustBrightnessContrast(float value) {
		return (value - 0.5f) * contrast + 0.5f + brightness;
	}

	static bool equal(float x, float y, float tolerance = 0.001) {
		if (fabs(y - x) >= tolerance) return false;
		else return true;
	}
};

void InterfaceGLApp::keyDown(KeyEvent event) {
	if (event.getChar() == ' ') showOriginal = !showOriginal;
}

void InterfaceGLApp::setup() {
	imageInput = loadImage(loadAsset("karma.jpg"));
	imageOutput = Surface32f(imageInput.getWidth(), 
		imageInput.getHeight(), false);

	in = gl::Texture::create(imageInput);

	brightness = 0.0f;
	prevBrightness = 0.1f;
	contrast = 1.0f; 
	prevContrast = 0.0f;

	showOriginal = false;

	params = params::InterfaceGl("Adjustment Params", 
		ivec2(200, 80));
	params.addParam("Brightness", &brightness,
		"min=-0.5 max=0.5 step=0.01 keyIncr=b keyDecr=v");
	params.addParam("Contrast", &contrast,
		"min=0.0 max=2.0 step=0.01 keyIncr=c keyDecr=x"); 
}

void InterfaceGLApp::update() {
	if (equal(brightness, prevBrightness) &&
		equal(contrast, prevContrast)) {
		return;
	}

	Surface32f::ConstIter pixelInIter = imageInput.getIter();
	Surface32f::Iter pixelOutIter = imageOutput.getIter();

	while (pixelInIter.line() && pixelOutIter.line()) {
		//pixelOutIter.line(); 
		while (pixelOutIter.pixel()) {
			pixelOutIter.r() = adjustBrightnessContrast(pixelInIter.r());
			pixelOutIter.g() = adjustBrightnessContrast(pixelInIter.g());
			pixelOutIter.b() = adjustBrightnessContrast(pixelInIter.b());
		}
	}

	out = gl::Texture::create(imageOutput);

	prevBrightness = brightness;
	prevContrast = contrast;
}

void InterfaceGLApp::draw() {
	if (showOriginal) {
		gl::draw(in, getWindowBounds());
	} else {
		gl::draw(out, getWindowBounds());
		params.draw();
	}
}

CINDER_APP( InterfaceGLApp, RendererGl )
