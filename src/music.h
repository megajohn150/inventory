#ifndef MUSIC_H
#define MUSIC_H

#include "displaylist.h"
#include "miniaudio.h"
#include <string>

class Music : public DisplayList
{
private:
    int currentlyPlaying;
    bool playing;
    int volume;

    ma_engine engine;
    ma_sound sound;
    bool soundLoaded; // FIX

    std::string getPath(int id);

public:
    Music();
    ~Music();

    void play(int id);
    void stop();
    void pause();
    void resume();

    void display();

    int getCurrentlyPlaying() const;
    void setCurrentlyPlaying(int newCurrentlyPlaying);

    bool getPlaying() const;
    void setPlaying(bool newPlaying);

    void toggle();

    int getVolume() const;
    void setVolume(int newVolume);
};

#endif // MUSIC_H