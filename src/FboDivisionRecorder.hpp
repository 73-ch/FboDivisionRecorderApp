
#ifndef FboDivisionRecorder_hpp
#define FboDivisionRecorder_hpp

#include "ofMain.h"
#include "FboRecorder.hpp"

class FboDivisionRecorder {
  
    
public:
    FboDivisionRecorder(const int _divisionNum = 5, const glm::vec2& _fboResolution = glm::vec2(1280,720));
    FboDivisionRecorder(const FboDivisionRecorder& recorder);
    
    FboRecorder& getDivision(const int index);
    
    void startRecord(const int index);
    void updateFbo(const ofFbo& fbo);
    void stopRecord(const int index);
    bool isRecording(const int index);
    int getCurrentTakeCount(const int index);
    string getLatestPlayableFilePath(const int index);
    
private:
    void getDivideFbo(const int index);
    
    
private:
    
    ofPixels fboTmpPixels;
    ofPixels dividedTmpPixels;
//    vector<ofPixels> dividedTmpPixels;
    const int divisionNum;
    const int segmentWidth;
    const glm::vec2& fboResolution;
    
public:
    vector<FboRecorder> recorders;
    
};

#endif /* FboDivisionRecorder_hpp */
