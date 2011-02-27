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
	GABPuppetHandle(ofxVec3f(1,1,1)); 
}

GABPuppetHandle::GABPuppetHandle(ofxVec3f _scalingFactor) {
	jointPosition.x = jointPosition.y = jointPosition.z = 0;
  bInitialSet = false;
  scalingFactor = _scalingFactor;
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