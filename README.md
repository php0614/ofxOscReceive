# ofxOscReceive

ofxOsc wrapper header file that makes receiving osc data in openFrameworks simple and easy.
ofxOsc is needed in your project to use this. If ofxOsc is in your project, you don't need to decalre #include "ofxOsc.h" in your ofApp.h . it is already included in this header file, so you only need to #include "ofxOscReceive.h" in your ofApp.h.


example :

//ofApp.h :

#include "ofxOscReceive.h"

//int, float, string, char and bool can be used. Just decalre right vector and it's going to do everything for you.

vector< float > test;

// draw() or update() in your ofApp.cpp

oscR.receive( {"/x", "/y"}, test);

-then incoming values that has a path name /x and /y will be stored in test[0] and test[1] respectively, in every loop.
-default IP address is "12345". You need to change "this->setup(12345);" part of the file manually if you want to use other address. 
