#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "scope.h"
#include "sendKeyEvent.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

//        ofVideoGrabber 		vidGrabber;
    ofxKinect   kinect;
    int 				camWidth;
    int 				camHeight;
    unsigned char * 	background;
    unsigned char *     output;
    ofTexture			videoTexture;
    int totalPixels;
    bool bBack;
    int dataLen;

    vector<float> ch;

    ofxIntSlider threshold;
    ofxPanel gui;

    vector<scope> scopes;

};

