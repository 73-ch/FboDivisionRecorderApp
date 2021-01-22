//
//  MultipleMoviePlayer.hpp
//  FboDivisionRecorderApp
//
//  Created by Kosaku Namikawa on 2021/01/22.
//

#ifndef MultipleMoviePlayer_hpp
#define MultipleMoviePlayer_hpp

#include "ofMain.h"

class MultipleMoviePlayer {
//    struct PlaceablePlayer  {
//        ofVideoPlayer player;
//        ofRectangle rect;
//        string path;
//    };

    map<string, ofVideoPlayer> players;
    map<string, ofRectangle> rects;
    
    
public:
    void playMovie(const string& path, glm::vec2 pos, glm::vec2 size);
    
    void stopAll();
    void update();
    void draw();
    
private:

    
};

#endif /* MultipleMoviePlayer_hpp */
