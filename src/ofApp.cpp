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
    
    ofxSubscribeOsc(3333, "/playback", [&](const int index) {
        auto path = divisionRecorder->getLatestPlayableFilePath(index);
        if (path == "") {
            ofLogWarning() << "no recording on index: " << index;
        } else {
//            ofVideoPlayer player;
//            player.load(path);
//            player.play();
//            players.push_back(player);

            const int segmentWidth = grabber.getWidth() / 5;

            player.playMovie(path, glm::vec2(segmentWidth * index, 0), glm::vec2(segmentWidth, grabber.getHeight()));
        }
    });
    
    
    ofxSubscribeOsc(3333, "/movie_recorder/start", [&](const int index) {
        if (!divisionRecorder->isRecording(index)) {
            divisionRecorder->startRecord(index);
        }
    });
    
    ofxSubscribeOsc(3333, "/movie_recorder/stop", [&](const int index) {
        if (divisionRecorder->isRecording(index)) {
            divisionRecorder->stopRecord(index);
        }
    });
    
    ofxSubscribeOsc(3333, "/movie_player/stopAll", [&]() {
        player.stopAll();
    });
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
//    for (auto p : players) p.update();
    
    player.update();
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
    player.draw();
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
