/*
 *  GABPuppetHandle.h
 *  emptyExample
 *
 *  Created by Greg Borenstein on 2/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofxVec3f.h"

class GABPuppetHandle {
  public:
    
    ofxVec3f jointPosition;
    GABPuppetHandle();
  
    GABPuppetHandle(ofxVec3f _scalingFactor);
  
    void setPosition(ofxVec3f pos);
  
    ofxVec3f getDisplacement();
  
    ofxVec3f scalingFactor;

  private:
    ofxVec3f initialJointPosition;
    bool  bInitialSet;
};