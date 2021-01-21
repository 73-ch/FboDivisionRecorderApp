#include "ofApp.h"

ofApp::ofApp() {
    // initialize fbo
    grabber.setup(1280, 720);
    
    fbo.allocate(grabber.getWidth(), grabber.getHeight(), GL_RGB);
    
    divisionRecorder = new FboDivisionRecorder(5, glm::vec2(grabber.getWidth(), grabber.getHeight()));
    
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    // fboRecorder.setup(glm::vec2(grabber.getWidth(), grabber.getHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // 録画するものをfboに書き込む
    fbo.begin();
    ofClear(0);
    
    ofSetColor(255);
    ofPushMatrix();
    grabber.draw(0, 0, fbo.getWidth(), fbo.getHeight());
    ofPopMatrix();
    
    fbo.end();
    

    // update recorder
    // fboRecorder.updateFrame(fbo);
    
    divisionRecorder->updateFbo(fbo);


    // sceneの描画処理
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == '1') {
        if (divisionRecorder->isRecording(1)) {
            divisionRecorder->stopRecord(1);
        } else {
            divisionRecorder->startRecord(1);
        }
    } else if (key == '2') {
        if (divisionRecorder->isRecording(2)) {
            divisionRecorder->stopRecord(2);
        } else {
            divisionRecorder->startRecord(2);
        }
    } else if (key == '3') {
        if (divisionRecorder->isRecording(3)) {
            divisionRecorder->stopRecord(3);
        } else {
            divisionRecorder->startRecord(3);
        }
    } else if (key == '4') {
        if (divisionRecorder->isRecording(4)) {
            divisionRecorder->stopRecord(4);
        } else {
            divisionRecorder->startRecord(4);
        }
    } else if (key == '0') {
        if (divisionRecorder->isRecording(0)) {
            divisionRecorder->stopRecord(0);
        } else {
            divisionRecorder->startRecord(0);
        }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
