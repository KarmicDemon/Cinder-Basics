#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
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
	Surface image;

	std::vector<Rectf> faces;
};

void OpenCVFaceDetectionApp::setup() {
}


void OpenCVFaceDetectionApp::draw() {
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( OpenCVFaceDetectionApp, RendererGl )
