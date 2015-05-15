#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"

void sendKeyEvent( int keycode )
{
    
    ProcessSerialNumber psn;
    GetFrontProcess( &psn );
    CGEventRef e = CGEventCreateKeyboardEvent (NULL, (CGKeyCode) keycode, true);
    //CGEventPost(kCGSessionEventTap, e);
    //CGEventPost(&psn, e);
    CGEventPostToPSN (&psn,e);
    CFRelease(e);
}

class scope
{
public:
   
    scope(){}
    
    scope(int _bufferLen)
    {
        bufferLen = _bufferLen;
        buffer.resize(bufferLen,0);
    }
    
    void setup(int _bufferLen)
    {
        bufferLen = _bufferLen;
        buffer.resize(bufferLen,0);
    }
    
    void add(float value)
    {
        buffer.push_back( value );
        
        if( buffer.size() >= bufferLen )
            buffer.erase(buffer.begin(), buffer.begin()+1);
        
    }
    
    void draw(int width, int height)
    {
        ofBeginShape();
        
        for (unsigned int i = 0; i < bufferLen; i++){
            float x =  ofMap(i, 0, bufferLen, 0, width, true);
            ofVertex(x, buffer[i]*height);
        }
        
        ofEndShape(false);
        
    }
    
   int bufferLen;
               
   vector<float> buffer;
    
    
    
};

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

