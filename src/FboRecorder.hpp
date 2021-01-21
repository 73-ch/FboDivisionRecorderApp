#ifndef FboRecorder_hpp
#define FboRecorder_hpp

#include "ofMain.h"
#include "ofxFFmpegRecorder.h"

#define FFMPEG_PATH "/usr/local/bin/ffmpeg"

// startThreadは直接呼ぶな
class FboRecorder : public ofThread {

public:
    FboRecorder() = default;
    FboRecorder(const FboRecorder &obj);

    void setup(const string& name, glm::vec2 _captureResolution);
    void startRecord();
    void updateFrame(const ofFbo &fbo);
    void updateFrame(const ofPixels &pixels);
    void threadedFunction();
    void stopRecord();
    bool isRecording() const;
    int getCurrentTakeCount() const;
    string getLatestPlayableFilePath() const;
    
    ofPixels tmpPixels;
    ofxFFmpegRecorder recorder;
    bool stopped = false;
private:
    string getFileNameFromCount(const int count) const;
    
    int takeCount = 0;
    string fileName = "test";
    glm::vec2 captureResolution;
};

#endif /* FboRecorder_hpp */
