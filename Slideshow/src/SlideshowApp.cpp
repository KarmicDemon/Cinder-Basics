#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class SlideshowApp : public App {
  public:
	void draw() override;
	void keyDown(KeyEvent event) override;
	void setup() override;
  private:
	vector<gl::TextureRef> slides;
	int current;
};

void SlideshowApp::setup() {
	slides.push_back(gl::Texture::create(loadImage(loadResource(RES_SLIDE_1))));
	slides.push_back(gl::Texture::create(loadImage(loadResource(RES_SLIDE_2))));
	slides.push_back(gl::Texture::create(loadImage(loadResource(RES_SLIDE_3))));
	slides.push_back(gl::Texture::create(loadImage(loadResource(RES_SLIDE_4))));

	current = 0;
}

void SlideshowApp::keyDown(KeyEvent event) {
	if (event.getCode() == KeyEvent::KEY_RIGHT) {
		current++;

		if (current >= static_cast<int>(slides.size())) {
			current = 0;
		}
	} else if (event.getCode() == KeyEvent::KEY_LEFT) {
		current--;

		if (current < 0) {
			current = static_cast<int>(slides.size() - 1);
		}
	}
}

void SlideshowApp::draw() {
	gl::clear(Color(0, 0, 0));
	gl::draw(slides[current], getWindowBounds());
}

CINDER_APP( SlideshowApp, RendererGl )
