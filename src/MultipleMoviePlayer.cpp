#include "MultipleMoviePlayer.hpp"

void MultipleMoviePlayer::playMovie(const string& path, glm::vec2 pos, glm::vec2 size) {
    ofVideoPlayer player;
    
    ofRectangle rect(pos, pos + size);
    
    player.load(path);
    player.setLoopState(OF_LOOP_NORMAL);

    players.insert(make_pair(path, player));
    rects.insert(make_pair(path, rect));
}

void MultipleMoviePlayer::update() {
    for (auto p : players) {
        p.second.update();
    }
}

void MultipleMoviePlayer::stopAll() {
    players.clear();
    rects.clear();
}

void MultipleMoviePlayer::draw() {
    for (auto p : players) {
        auto rect = rects[p.first];
        if (p.second.isPlaying()) {
            p.second.draw(rect.x, rect.y, rect.width, rect.height);
        }
    }
}
