/*
 *  GABPuppetHandle.cpp
 *  emptyExample
 *
 *  Created by Greg Borenstein on 2/27/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GABPuppetHandle.h"

GABPuppetHandle::GABPuppetHandle() {
	GABPuppetHandle(GABPuppetHandleTarget(), ofxVec3f(1,1,1)); 
}

GABPuppetHandle::GABPuppetHandle(GABPuppetHandleTarget _target, ofxVec3f _scalingFactor) {
	jointPosition.x = jointPosition.y = jointPosition.z = 0;
  bInitialSet = false;
  scalingFactor = _scalingFactor;
  target = target;
}


void GABPuppetHandle::setPosition(ofxVec3f pos) {
  if(!bInitialSet){
    initialJointPosition = pos;
    
    bInitialSet = true;
  }
  
  jointPosition = pos;
}

ofxVec3f GABPuppetHandle::getDisplacement(){
  ofxVec3f result;
  result.x = (initialJointPosition.x - jointPosition.x) * scalingFactor.x;
  result.y = (initialJointPosition.y - jointPosition.y) * scalingFactor.y;
  result.z = (initialJointPosition.z - jointPosition.z) * scalingFactor.z;
  return result;
}


GABPuppetHandleTarget::GABPuppetHandleTarget(){
  GABPuppetHandleTarget(ofPoint(0,0,0), ofPoint(100,100,100));
}

GABPuppetHandleTarget::GABPuppetHandleTarget(ofPoint _nearPoint, ofPoint _farPoint){
  nearPoint = _nearPoint;
  farPoint = _farPoint;
}

bool GABPuppetHandleTarget::includes( ofPoint p ){

  bool r = false;
  
  if(p.x > nearPoint.x && p.x < farPoint.x){
    if(p.y > nearPoint.y && p.y < farPoint.y){
      if(p.z > nearPoint.z && p.z < farPoint.z){
        r = true;
      }
    }
  }
  
  return r;
}
