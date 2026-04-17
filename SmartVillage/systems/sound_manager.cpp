#include "sound_manager.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")

SoundManager::SoundManager() : rainPlaying(false), stormPlaying(false), windPlaying(false) {}

SoundManager::~SoundManager() {
    stopRain();
    stopStorm();
    stopWind();
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
    sendCmd("play cow_sound from 0");
}

void SoundManager::playGoat() {
    static bool opened = false;
    if (!opened) {
        sendCmd("open \"media/sounds/goat.mp3\" type mpegvideo alias goat_sound");
        opened = true;
    }
    sendCmd("play goat_sound from 0");
}

void SoundManager::playHen() {
    static bool opened = false;
    if (!opened) {
        sendCmd("open \"media/sounds/hen.mp3\" type mpegvideo alias hen_sound");
        opened = true;
    }
    sendCmd("play hen_sound from 0");
}
