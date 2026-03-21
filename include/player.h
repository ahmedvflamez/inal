#pragma once

#include <SFML/Audio/Music.hpp>

#include <string>
#include <atomic>
#include <chrono>

struct PlayerState{
    sf::Music music;
    
    std::string filename;
    std::string cmd = "";
    std::string status = "Stopped";

    float current = 0.f;
    float duration = 0.f;
    float progress = 0.f;

    std::atomic<bool> loop{false};
    std::atomic<bool> playing{true};
    std::atomic<bool> replaying{false};
    
    std::atomic<bool> isRunning{true};
    std::atomic<bool> hasFile{false};

    std::atomic<bool> showHelp{false};
    std::atomic<bool> showFileError{false};

    std::chrono::steady_clock::time_point noteTime;
};
void handleCommands(const std::string& cmd, PlayerState& state);
bool validExtension(const std::string& file);
