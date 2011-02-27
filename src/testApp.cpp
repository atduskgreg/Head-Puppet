#include "testApp.h"


//GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
//GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};
//
//GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
//GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};
//GLfloat blue[] = { 0.2, 0.4, 1.0, 0.8 };
//GLfloat red[] = { 1.0, 0.3, 0.4, 0.5 };
//GLfloat white[] = {0.5, 0.5, 0.5, 0.7};



void testApp::setup(){
  // OSC SETUP ==================
  cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );  
	current_msg_string = 0;
  
  // SETUP APP RECORDER ===============
  fullAppBuffer.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
  
  r = 0;
  bRotating = false;
  
  ofBackground(255,255,255);
  ofSetFrameRate(30);
	ofSetVerticalSync(true);
  
  camWidth = 320;
  camHeight = 240;
  vid.setVerbose(true);
  vid.initGrabber(camWidth, camHeight);
  
  ofxVec3f scaleBy = ofxVec3f(ofGetWidth() / 8, ofGetHeight() / 8, 200 / 8);
  
  rEyebrow = GABPuppetHandleTarget( ofPoint(0, -25, 100), ofPoint(50, 25, 150) );
  rHand = GABPuppetHandle(rEyebrow, scaleBy);

  /*const GLfloat light0Ambient[] = {0.05, 0.05, 0.05, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
  const GLfloat light0Diffuse[] = {0.8, 0.8, 0.8, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
  const GLfloat light0Specular[] = {0.7, 0.7, 0.7, 1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
  const GLfloat light0Position[] = {10.0, 10.0, 10.0, 0.0}; 
  glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
  glLightfv(GL_LIGHT0, GL_POSITION, light0Position); 
  
  // Define a direction vector for the light, this one points right down the Z axis
  const GLfloat light0Direction[] = {0.0, 0.0, -1.0};
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0Direction);
  
  // Define a cutoff angle. This defines a 90¡ field of vision, since the cutoff
  // is number of degrees to each side of an imaginary line drawn from the light's
  // position along the vector supplied in GL_SPOT_DIRECTION above
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
  glShadeModel(GL_SMOOTH);
   */
    
  
  // reference is the undistorted model we iterate through
  // model is the one we actually distort
  
  model.load("self_portrait_final.obj");
  reference.load("self_portrait_final.obj");
  

}

void testApp::processOSC(){
  // hide old messages
	for ( int i=0; i<NUM_MSG_STRINGS; i++ )
	{
		if ( timers[i] < ofGetElapsedTimef() )
			msg_strings[i] = "";
	}
  
	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
    
		// check for mouse moved message
		
    if ( m.getAddress() == "/joint" ){
      if(m.getArgAsString(0) == "r_hand"){
        rHand.setPosition(ofxVec3f(m.getArgAsFloat(2), m.getArgAsFloat(3), m.getArgAsFloat(4)));
      }
      
      if(m.getArgAsString(0) == "l_hand"){
        /*lHand.x = m.getArgAsFloat(2) * ofGetWidth();
        lHand.y = m.getArgAsFloat(3) * ofGetHeight();
        lHand.z = m.getArgAsFloat(4) * 200;*/
      }
      
      
    } else {
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for ( int i=0; i<m.getNumArgs(); i++ )
			{
				// get the argument type
				msg_string += m.getArgTypeName( i );
				msg_string += ":";
				// display the argument - make sure we get the right type
				if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
					msg_string += ofToString( m.getArgAsInt32( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
					msg_string += ofToString( m.getArgAsFloat( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
					msg_string += m.getArgAsString( i );
				else
					msg_string += "unknown";
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}
    
	}
  
}

//--------------------------------------------------------------
void testApp::update(){
  processOSC();
  
  vid.grabFrame();
  
	if (bRecording == true){
		saver.addFrame(fullAppBuffer.getPixels(), 1.0f / 30.0f); 
  }
  
  
  //ofxVec3f handDistance = rHandInitial - rHand;
  ofxVec3f handDistance = rHand.getDisplacement();
  
  cout << "handDistance x: " << handDistance.x << " y: " << handDistance.y << " z: " << handDistance.z << endl;
  
  // process face vertices
  
  vector<ObjFace*>& faces = model.meshes[0]->faces;
  vector<ObjFace*>& refFaces = reference.meshes[0]->faces;

  for(int j =0; j < faces.size(); j++){
    vector<ofPoint>& points = faces[j]->points;
    vector<ofPoint>& refPoints = refFaces[j]->points;
    
    for(int i =0; i < points.size(); i++){
      if(rEyebrow.includes(refPoints[i])){
        points[i].x = refPoints[i].x + rHand.getDisplacement().x;
        points[i].y = refPoints[i].y + rHand.getDisplacement().y;
        points[i].z = refPoints[i].z + rHand.getDisplacement().z;
        
      }
      /*if(refPoints[i].x > rightEyeMinX && refPoints[i].x < (rightEyeMinX + 50)){
        if(refPoints[i].y > rightEyeMinY && refPoints[i].y < (rightEyeMinY + 50)){
          if(refPoints[i].z > rightEyeMinZ && refPoints[i].z < (rightEyeMinZ + 50)){

            points[i].x = refPoints[i].x + handDistance.x;
            points[i].y = refPoints[i].y + handDistance.y;
            points[i].z = refPoints[i].z + handDistance.z ;
            
          }
        }
      }
      */
    }
  }
  
}


void drawRightEyeBox(){
  int boxSize = 50;
/*
   glBegin(GL_QUADS);
      glVertex3f(0, -25, 150);
      glVertex3f(50, -25, 150);
      glVertex3f(50, 25, 150);
      glVertex3f(0, 25, 150);
  
      glVertex3f(0, -25, 100);
      glVertex3f(50, -25, 100);
      glVertex3f(50, 25, 100);
      glVertex3f(0, 25, 100);
  

    
      glVertex3f(0, -25, 150);
      glVertex3f(50, -25, 150);
      glVertex3f(0, -25, 100);
      glVertex3f(50, -25, 100);

      glVertex3f(0, 25, 150);
      glVertex3f(50, 25, 150);
      glVertex3f(0, 25, 100);
      glVertex3f(50, 25, 100);
  
      glVertex3f(rightEyeMinX, rightEyeMinY, rightEyeMinZ);
      glVertex3f(rightEyeMinX, rightEyeMinY, rightEyeMinZ + boxSize);
      glVertex3f(rightEyeMinX, rightEyeMinY + boxSize, rightEyeMinZ + boxSize);

      glVertex3f(rightEyeMinX, rightEyeMinY + boxSize, rightEyeMinZ);
    glEnd;
*/
  
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  glPushMatrix();
  // LIGHTING ================
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);    
  glEnable(GL_NORMALIZE);
  
    glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
    ofRotate(180, 0, 0, 0);
    
    ofRotate(r, 0, 1, 0);
    if(bRotating){
      r++;  
    }
  
    ofSetColor(255, 255, 255);
  

    model.draw();
    

  
  // LIGHTING ================
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHT0);    
  glDisable(GL_NORMALIZE);
  glPopMatrix();
  
  ofSetColor(0xffffff);
  vid.draw(0, ofGetHeight() - 240);
  
  // ALWAYS LEAVE THIS LAST:
  if(bRecording == true){
    fullAppBuffer.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
  }
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
  if (key == ' ') {
      bRotating = !bRotating;
  }
  
  if (key == 'a'){
		saver.setup(ofGetWidth(),ofGetHeight(),"floating_transparent_head.mov");
	} else if (key == 's'){
		saver.finishMovie();
		bRecording = false;
	} else if (key == 'r'){
		bRecording = !bRecording;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

