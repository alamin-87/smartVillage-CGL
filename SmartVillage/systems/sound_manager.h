#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>

class SoundManager {
public:
    static SoundManager& getInstance();

    void playRain();
    void stopRain();
    
    void playStorm();
    void stopStorm();
    
    void playWind();
    void stopWind();

    void playCow();
    void playGoat();
    void playHen();

private:
    SoundManager();
    ~SoundManager();
    
    void sendCmd(const std::string& cmd);
    
    bool rainPlaying;
    bool stormPlaying;
    bool windPlaying;
};

#endif
