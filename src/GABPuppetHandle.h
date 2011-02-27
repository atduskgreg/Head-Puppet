/*
 *  GABPuppetHandle.h
 *  emptyExample
 *
 *  Created by Greg Borenstein on 2/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofxVec3f.h"
#include "ofx3dGraphics.h"

class GABPuppetHandleTarget {
public:
  ofPoint nearPoint;
  ofPoint farPoint;
  
  GABPuppetHandleTarget();
  GABPuppetHandleTarget(ofPoint _nearPoint, ofPoint _farPoint);
  
  bool includes( ofPoint p );
};

class GABPuppetHandle {
  public:
    
    ofxVec3f jointPosition;
    GABPuppetHandle();
  
    GABPuppetHandle(GABPuppetHandleTarget _target, ofxVec3f _scalingFactor);
  
    void setPosition(ofxVec3f pos);
  
    ofxVec3f getDisplacement();
  
    
    GABPuppetHandleTarget target;
    ofxVec3f scalingFactor;

  private:
    ofxVec3f initialJointPosition;
    bool  bInitialSet;
};

