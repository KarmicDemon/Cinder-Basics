#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImagesApp : public App {
  public:
	void draw() override;
	void keyDown(KeyEvent event) override;
	void setup() override;
  private:
	gl::TextureRef picture;
	gl::TextureRef res;

	gl::TextureRef original;
	gl::TextureRef red;
	gl::TextureRef green; 
	gl::TextureRef blue;
	gl::TextureRef current;

	enum class ShowMode {
		Complete, Red, Green, Blue
	};

	ShowMode showMode;
	gl::TextureRef texture;
};

void ImagesApp::setup() {
	picture = gl::Texture::create(loadImage(loadAsset("karma.jpg")));
	res = gl::Texture::create(loadImage(loadResource(RES_KARMA)));

	Surface image = loadImage(loadResource(RES_KARMA));

	Surface redImage = image.clone();
	Surface::Iter redIter = redImage.getIter();
	while (redIter.line()) {
		while (redIter.pixel()) {
			redIter.g() = 0;
			redIter.b() = 0;
		}
	}

	Surface greenImage = image.clone();
	Surface::Iter greenIter = greenImage.getIter();
	while (greenIter.line()) {
		while (greenIter.pixel()) {
			greenIter.r() = 0;
			greenIter.b() = 0;
		}
	}

	Surface blueImage = image.clone();
	Surface::Iter blueIter = blueImage.getIter();
	while (blueIter.line()) {
		while (blueIter.pixel()) {
			blueIter.r() = 0;
			blueIter.g() = 0;
		}
	}

	original = gl::Texture::create(image);
	red = gl::Texture::create(redImage);
	green = gl::Texture::create(greenImage);
	blue = gl::Texture::create(blueImage);
	//current = original; 
	
	showMode = ShowMode::Complete;
}

void ImagesApp::draw() {
	gl::clear( Color( 0, 0, 0 ) ); 

	//loading from assets
	//gl::draw(picture, getWindowBounds());
	
	//loading from resources
	//gl::draw(res, getWindowBounds());

	//surfaces and showing individual primary color models
	//gl::draw(current, getWindowBounds());

	//texture primary color models
	switch (showMode) {
		case ShowMode::Complete:
			gl::color(1, 1, 1);
			break;
		case ShowMode::Red:
			gl::color(1, 0, 0);
			break;
		case ShowMode::Green:
			gl::color(0, 1, 0);
			break;
		case ShowMode::Blue:
			gl::color(0, 0, 1);
			break;
	}
	gl::draw(res, getWindowBounds());
}

void ImagesApp::keyDown(KeyEvent event) {
	const char ch = event.getChar();
	switch (ch) {
		case 'r':
			showMode = ShowMode::Red;
			current = red;
			break;
		case 'g':
			showMode = ShowMode::Green;
			current = green;
			break;
		case 'b':
			showMode = ShowMode::Blue;
			current = blue;
			break;
		case 'a':
			showMode = ShowMode::Complete;
			current = original;
			break;
		default:
			break;
	}
}

CINDER_APP( ImagesApp, RendererGl )
