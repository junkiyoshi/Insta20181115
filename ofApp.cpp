#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->frame = cv::Mat(200, 200, CV_8UC3);

	this->draw_image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	this->draw_frame = cv::Mat(this->draw_image.getHeight(), this->draw_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->draw_image.getPixels().getNumChannels()), this->draw_image.getPixels().getData(), 0);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int x = 0; x < this->frame.cols; x++) {

		unsigned char value = ofNoise(x * 0.05, ofGetFrameNum() * 0.05) * 255;
		this->frame.at<cv::Vec3b>(0, x) = cv::Vec3b(value, 0, 0);
	}

	for (int x = 0; x < this->frame.cols; x++) {

		for (int y = 1; y < this->frame.rows; y++) {

			int sum = 0;
			int count = 0;

			sum += this->frame.at<cv::Vec3b>(y - 1, x)[0];
			count++;

			if (x >= 0) {

				sum += this->frame.at<cv::Vec3b>(y - 1, x - 1)[0];
				count++;
			}

			if (x < this->frame.rows - 1) {

				sum += this->frame.at<cv::Vec3b>(y - 1, x + 1)[0];
				count++;
			}

			if (y > 1) {

				sum += this->frame.at<cv::Vec3b>(y - 2, x)[0];
				count++;
			}

			int avg = sum / count;
			unsigned char r = 0;
			unsigned char g = 0;
			if (avg > 255) {

				r = 255;
			}
			else if (avg < 0) {

				r = 0;
			}
			else {

				r = avg;
				if (avg > 150) {

					g = (unsigned char)ofMap(avg, 150, 255, 0, 100);
				}

			}

			this->frame.at<cv::Vec3b>(y, x) = cv::Vec3b(r,  g, g * 0.1);
		}
	}

	this->frame *= 1.02;

	cv::resize(this->frame, this->draw_frame, cv::Size(ofGetWidth(), ofGetHeight()));
	this->draw_image.update();
}
//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofRotate(180);

	this->draw_image.draw(ofGetWidth() * -0.5, ofGetHeight() * -0.5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}