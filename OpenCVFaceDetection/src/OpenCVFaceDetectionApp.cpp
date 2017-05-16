#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "CinderOpenCV.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class OpenCVFaceDetectionApp : public App {
  public:
	void draw() override;
	void setup() override;
	
  private:
	cv::CascadeClassifier faceClf;
	Surface img;
	vector<Rectf> faces;
};

vector<Rectf> allFromOCV(const vector<cv::Rect>& cvRects) {
	vector<Rectf> rects;

	for (const auto& cvRect : cvRects) {
		ci::Rectf rect = ci::fromOcv(cvRect);
		rects.push_back(rect);
	}

	return rects; 
}

void OpenCVFaceDetectionApp::setup() {
	img = loadImage(loadAsset("hans_and_nan.jpg"));
	faceClf.load(getAssetPath("face_clf.xml").string());

	setWindowSize(img.getWidth(), img.getHeight());
	cv::Mat cvImage(toOcv(img, CV_8UC1));
	vector<cv::Rect> cvFaces;
	faceClf.detectMultiScale(cvImage, cvFaces);
	faces = allFromOCV(cvFaces);
}

void OpenCVFaceDetectionApp::draw() {
	gl::clear(Color(0, 0, 0)); 
	gl::draw(gl::Texture::create(img));

	//gl::color(ColorA(0.0f, 0.0f, 1.0f, 0.2f));
	for (const auto& face : faces) {
		gl::drawStrokedRect(face, 2.0f);
	}
}

CINDER_APP( OpenCVFaceDetectionApp, RendererGl )
