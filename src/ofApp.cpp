#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    
    gui.setup();
    gui.add( threshold.setup("Threshold",20,0,255*3) );
//    vidGrabber.setDeviceID(0);
//    vidGrabber.setDesiredFrameRate(60);
//    vidGrabber.initGrabber(camWidth,camHeight);
    
    kinect.init();
    kinect.open(0);
    
    background 	= new unsigned char[camWidth*camHeight*3];
    output = new unsigned char[camWidth*camHeight*3];
    
    bBack = false;
    
    totalPixels = camWidth*camHeight;
    for (int i = 0; i < totalPixels*3; i++)
        background[i]=0;
    
    ch.assign(3,0);
    
    dataLen = 400;
    
    scopes.resize(3);
    
    for(int i =0;i<3;i++)
    {
        scopes[i].setup(dataLen);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
//   	ofBackground(100,100,100);
    
//    vidGrabber.update();
    kinect.update();
    
    if (kinect.isFrameNew()){

        unsigned char * pixels = kinect.getPixels();

        if( bBack)
        {
            for (int i = 0; i < totalPixels*3; i++){
                background[i] = pixels[i];
            }
            bBack = false;
        }
        
        int dist;
        
        ch[0]=0;
        ch[1]=0;
        ch[2]=0;
        
        for (int i = 0; i < totalPixels; i++){
            int ii = i*3;
            dist = 0;
            for(int j = 0; j < 3; j++)
            {
                dist +=  abs(pixels[ii+j] - background[ii+j]) ;
                output[ii+j] = 0;
            }
            
            if (dist >= threshold)
            {
                for(int j = 0; j < 3; j++)
                {
                    ch[j]+= pixels[ii+j];
                    output[ii+j] = pixels[ii+j];
                }
            }
            
        }
        videoTexture.loadData( output , camWidth,camHeight, GL_RGB);
    }
    
    for(int j = 0; j < 3; j++)
    {
        scopes[j].add( 1 - ch[j]/totalPixels/100 );
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

//    ofSetHexColor(0xffffff);
//    vidGrabber.draw(20,20);

    videoTexture.draw(0,0,ofGetWidth(),ofGetHeight());
    
//    kinect.draw(100,0,ofGetWidth(),ofGetHeight());
    
    gui.draw();
    ofNoFill();
    
    for(int i = 0;i<3;i++)
    {
        ofPushStyle();
        ofPushMatrix();
        
        ofTranslate(32, 370+i*100, 0);
        
        ofSetColor((i==0)*255, (i==1)*255, (i==2)*255);
        ofSetLineWidth(3);
        
        scopes[i].draw( ofGetWidth()/2, 100 );
        
        ofPopMatrix();
        ofPopStyle();

    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='b')
    {
        bBack = true;
        cout << bBack << endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
