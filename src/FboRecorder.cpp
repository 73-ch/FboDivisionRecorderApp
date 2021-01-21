#include "FboRecorder.hpp"

FboRecorder::FboRecorder(const FboRecorder &obj) {
    fileName = obj.fileName;
    captureResolution = obj.captureResolution;
    
    recorder.setup(true, false, captureResolution);
    recorder.setOverWrite(true);
    recorder.setFFmpegPath(FFMPEG_PATH);
}

void FboRecorder::setup(const string &name, glm::vec2 _captureResolution) {
    fileName = name;
    captureResolution = _captureResolution;

    recorder.setup(true, false, captureResolution);
    recorder.setOverWrite(true);
    
    recorder.setFFmpegPath(FFMPEG_PATH);
}

void FboRecorder::startRecord() {
    if (recorder.isRecording()) {
        ofLogWarning() << fileName <<  ": recording, so can't start recording.";
    } else {
        takeCount++;
        
        auto file = getFileNameFromCount(takeCount);

        recorder.setOutputPath(ofToDataPath(file, true));
        recorder.setVideoCodec("libx264");
        recorder.setBitRate(8000);
        recorder.startCustomRecord();
        ofLogNotice() << "start recording";
    }
}

void FboRecorder::threadedFunction() {
    recorder.stop();
}

void FboRecorder::updateFrame(const ofFbo &fbo) {
    if (recorder.isRecording() && !stopped) {
        fbo.readToPixels(tmpPixels);
        
        if (tmpPixels.getWidth() > 0 && tmpPixels.getHeight() > 0) {
            recorder.addFrame(tmpPixels);
        }
    }
}

void FboRecorder::updateFrame(const ofPixels &pixels) {
    if (recorder.isRecording() && !stopped) {
        recorder.addFrame(pixels);
    }
}

void FboRecorder::stopRecord() {
    if (recorder.isRecording()) {
        stopped = true;
        startThread();
    } else {
        ofLogWarning() << fileName <<  ": NOT recording, so can't stop recording.";
    }
}


bool FboRecorder::isRecording() const {
    return recorder.isRecording();
}

int FboRecorder::getCurrentTakeCount() const {
    return takeCount;
}

string FboRecorder::getLatestPlayableFilePath() const {
    if (recorder.isRecording()) {
        return getFileNameFromCount(takeCount - 1);
    } else {
        return getFileNameFromCount(takeCount);
    }
    
}

string FboRecorder::getFileNameFromCount(const int count) const {
    return fileName + "-" + ofToString(count) + ".mp4";
}
