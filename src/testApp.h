// TODO:
// - align right hand box with eyebrow
// - build class for representing moveable parts and handles


#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxQTVideoSaver.h"
#include "ofxOBJModel.h"
#include "ofxOsc.h"
#include "ofxVec3f.h"
#include "ofx3dGraphics.h"
#include "GABPuppetHandle.h"

#define PORT 59907
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
  
  
    ofxOBJModel model;
    ofxOBJModel reference;
  
  
    // "r" and "l" here refer to screen left and right
    GABPuppetHandle rHand;
    GABPuppetHandleTarget rEyebrow;
  
    GABPuppetHandle lHand;
    GABPuppetHandleTarget lEyebrow;
  
    GABPuppetHandle lKnee;
    GABPuppetHandleTarget lMouth;
  
    GABPuppetHandle rKnee;
    GABPuppetHandleTarget rMouth;
  
    GABPuppetHandle head;
    GABPuppetHandleTarget forehead;
    
    GABPuppetHandle rElbow;
    GABPuppetHandleTarget rCheek;
  
    GABPuppetHandle lElbow;
    GABPuppetHandleTarget lCheek;
  
     
    int r;
    bool bRotating;
    
    // VIDEO RECORDING
    ofVideoGrabber vid;
    int camWidth;
    int camHeight;
  
    ofxQtVideoSaver saver;
    bool bRecording;
    ofImage fullAppBuffer;

private:
  void processOSC();

  ofxOscReceiver	receiver;
  
  int				current_msg_string;
  string		msg_strings[NUM_MSG_STRINGS];
  float			timers[NUM_MSG_STRINGS];

};

#endif
