#include "FboDivisionRecorder.hpp"


FboDivisionRecorder::FboDivisionRecorder(const int _divisionNum, const glm::vec2& _fboResolution)
    :divisionNum(_divisionNum),
    fboResolution(_fboResolution),
    segmentWidth(_fboResolution.x / _divisionNum)
{
    for (int i = 0; i < divisionNum; ++i) {
        FboRecorder recorder;
        recorder.setup(ofToString(i), glm::vec2(segmentWidth, fboResolution.y));
        recorders.push_back(recorder);
    }
    
    fboTmpPixels.resize(fboResolution.x, fboResolution.y);
    dividedTmpPixels.resize(segmentWidth, fboResolution.y);
}

FboDivisionRecorder::FboDivisionRecorder(const FboDivisionRecorder& recorder)
    :divisionNum(recorder.divisionNum),
    fboResolution(recorder.fboResolution),
    segmentWidth(recorder.segmentWidth)
{
    for (auto r: recorder.recorders) {
        recorders.push_back(r);
    }
}

FboRecorder& FboDivisionRecorder::getDivision(const int index) {
    if (index >= recorders.size()) {
        ofLogWarning() << "invalid index";
        return;
    }
    
    return recorders[index];
}


void FboDivisionRecorder::startRecord(const int index) {
    getDivision(index).startRecord();
}

void FboDivisionRecorder::updateFbo(const ofFbo& fbo) {
    fbo.readToPixels(fboTmpPixels);
    
    if (fboTmpPixels.getWidth() == 0 || fboTmpPixels.getHeight() == 0) return;
    
    for (int i = 0; i < recorders.size(); ++i) {
        if (!recorders[i].isRecording()) continue;
        
        fboTmpPixels.cropTo(dividedTmpPixels, segmentWidth * i, 0, segmentWidth, fboTmpPixels.getHeight());
        recorders[i].updateFrame(dividedTmpPixels	);
    }
    
}

void FboDivisionRecorder::stopRecord(const int index) {
    getDivision(index).stopRecord();
}

bool FboDivisionRecorder::isRecording(const int index) {
    return getDivision(index).isRecording();
}

int FboDivisionRecorder::getCurrentTakeCount(const int index) {
    return getDivision(index).getCurrentTakeCount();
}

string FboDivisionRecorder::getLatestPlayableFilePath(const int index) {
    return getDivision(index).getLatestPlayableFilePath();
}
