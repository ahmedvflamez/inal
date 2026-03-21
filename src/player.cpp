#include "player.h"

#include <SFML/System/Time.hpp>
#include <filesystem>
#include <algorithm>

bool validExtension(const std::string &file){
    std::string ex = std::filesystem::path(file).extension().string();
    return ex == ".mp3" || ex == ".wav" || ex == ".ogg" || ex == ".flac";
}

void loadFile(const std::string& file, PlayerState& s){
    s.music.stop();
    s.music.openFromFile(file);
    s.filename = std::filesystem::path(file).filename().string();
    s.current = 0.f;
    s.duration = s.music.getDuration().asSeconds();
    s.progress = 0.f;
    s.playing = true;
    s.hasFile = true;
    s.status = "Playing";
    s.music.play();
}

void handleCommands(const std::string &cmd, PlayerState &s){
    s.showFileError = false;

    auto removeQuote = [](std::string s){
        if(s.size() >= 2 && s.front() == '"' && s.back() == '"'){
            s = s.substr(1, s.size() - 2);
        }
        return s;
    };
    if(cmd == "quit") {
            s.isRunning = false;
        } else if(cmd == "stop") {
            if(!s.hasFile) {
                s.showFileError = true;
            }
            s.playing = false;
            s.loop    = false;
            s.music.stop();
            s.status = "Stopped";
        } else if(cmd == "loop") {
            if(!s.hasFile) {
                s.showFileError = true;
                s.noteTime = std::chrono::steady_clock::now();
            }
            s.loop = !s.loop;
            if(s.loop){
                s.playing = true;
                s.status = "Looping";
                s.music.play();
            } else {
                s.playing = false;
                s.music.stop();
                s.status = "Ended";
            }
        } else if(cmd.substr(0, 4) == "seek") {
            if(!s.hasFile) {
                s.showFileError = true;
                s.noteTime = std::chrono::steady_clock::now();
            }
            if(cmd.size() > 5 && s.playing == true){
            float secs = std::clamp(stof(cmd.substr(5)), 0.f, s.duration);
            s.music.setPlayingOffset(sf::seconds(secs));
            }
        } else if(cmd.substr(0, 6) == "volume") {
            if(cmd.size() > 7 && s.playing == true) {
            float vol = std::clamp(stof(cmd.substr(7)), 0.f, 100.f);
            s.music.setVolume(vol);
        }
        } else if(cmd == "play"){
            s.replaying = true;
            s.loop = false;
            s.playing = true;
            s.music.stop();
            s.music.setPlayingOffset(sf::seconds(0));
            s.music.play();
            s.status = "Playing";
            s.replaying = false;
    } else if(cmd.substr(0,6) == "switch"){
            if(cmd.size() > 7){
                std::string file = removeQuote(cmd.substr(7));
                if(!validExtension(file)){
                    s.showFileError = true;
                    s.noteTime = std::chrono::steady_clock::now();
                } else if(!std::filesystem::exists(file)){
                s.showFileError = true;
                s.noteTime = std::chrono::steady_clock::now();
            } else {
                loadFile(file, s);
            }
        }
    } else if(cmd == "help"){
        s.showHelp = true;
        s.noteTime = std::chrono::steady_clock::now();
    }
}
