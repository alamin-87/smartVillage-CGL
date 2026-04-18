#include "sound_manager.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")

SoundManager::SoundManager() : rainPlaying(false), stormPlaying(false), windPlaying(false), childPlaying(false), birdPlaying(false), henPlaying(false) {}

SoundManager::~SoundManager() {
    stopRain();
    stopStorm();
    stopWind();
    stopChild();
    stopBird();
    stopHen();
}

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::sendCmd(const std::string& cmd) {
    MCIERROR err = mciSendStringA(cmd.c_str(), NULL, 0, NULL);
    if (err != 0) {
        char errText[256];
        mciGetErrorStringA(err, errText, 256);
        std::cerr << "[SoundManager] MCI Error for command \"" << cmd << "\": " << errText << std::endl;
        std::cerr << "[SoundManager] Please ensure you have placed the .wav files in media/sounds/!" << std::endl;
    }
}

void SoundManager::playRain() {
    if (rainPlaying) return;
    sendCmd("open \"media/sounds/rain.mp3\" type mpegvideo alias rain");
    sendCmd("play rain repeat");
    rainPlaying = true;
}

void SoundManager::stopRain() {
    if (!rainPlaying) return;
    sendCmd("stop rain");
    sendCmd("close rain");
    rainPlaying = false;
}

void SoundManager::playStorm() {
    if (stormPlaying) return;
    sendCmd("open \"media/sounds/strom.mp3\" type mpegvideo alias storm");
    sendCmd("play storm repeat");
    stormPlaying = true;
}

void SoundManager::stopStorm() {
    if (!stormPlaying) return;
    sendCmd("stop storm");
    sendCmd("close storm");
    stormPlaying = false;
}

void SoundManager::playWind() {
    if (windPlaying) return;
    sendCmd("open \"media/sounds/wind.mp3\" type mpegvideo alias wind");
    sendCmd("play wind repeat");
    windPlaying = true;
}

void SoundManager::stopWind() {
    if (!windPlaying) return;
    sendCmd("stop wind");
    sendCmd("close wind");
    windPlaying = false;
}

void SoundManager::playCow() {
    static bool opened = false;
    if (!opened) {
        sendCmd("open \"media/sounds/cow.mp3\" type mpegvideo alias cow_sound");
        opened = true;
    }
    sendCmd("stop cow_sound");
    sendCmd("play cow_sound from 0");
}

void SoundManager::playGoat() {
    static bool opened = false;
    if (!opened) {
        sendCmd("open \"media/sounds/goat.mp3\" type mpegvideo alias goat_sound");
        opened = true;
    }
    sendCmd("stop goat_sound");
    sendCmd("play goat_sound from 0");
}

void SoundManager::playHen() {
    if (henPlaying) return;
    sendCmd("open \"media/sounds/hen.mp3\" type mpegvideo alias hen_sound");
    sendCmd("play hen_sound repeat");
    henPlaying = true;
}

void SoundManager::stopHen() {
    if (!henPlaying) return;
    sendCmd("stop hen_sound");
    sendCmd("close hen_sound");
    henPlaying = false;
}

void SoundManager::playBird() {
    if (birdPlaying) return;
    sendCmd("open \"media/sounds/bird.mp3\" type mpegvideo alias bird_sound");
    sendCmd("play bird_sound repeat");
    birdPlaying = true;
}

void SoundManager::stopBird() {
    if (!birdPlaying) return;
    sendCmd("stop bird_sound");
    sendCmd("close bird_sound");
    birdPlaying = false;
}

void SoundManager::playChild() {
    if (childPlaying) return;
    sendCmd("open \"media/sounds/child.mp3\" type mpegvideo alias child_sound");
    sendCmd("play child_sound repeat");
    childPlaying = true;
}

void SoundManager::stopChild() {
    if (!childPlaying) return;
    sendCmd("stop child_sound");
    sendCmd("close child_sound");
    childPlaying = false;
}

void SoundManager::playDuck() {
    static bool opened = false;
    if (!opened) {
        sendCmd("open \"media/sounds/duck.mp3\" type mpegvideo alias duck_sound");
        opened = true;
    }
    sendCmd("stop duck_sound");
    sendCmd("play duck_sound from 0");
}
