#include "player.h"
#include "ui.h"

#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    PlayerState state;

    if(argc < 2){
        std::cerr << "No arguments found!";
        std::cout << "\nUsage: " << argv[0] <<  " <filename>\n";
        return 1;
    }
        
        std::string file = argv[1];
        if(!validExtension(file)){
            std::cerr << "Invalid file format\n";
            return 1;
        }
        if(!std::filesystem::exists(file)){
            std::cerr << "File not found!\n";
            return 1;
        }
        if(!state.music.openFromFile(file)){
            std::cerr << "Can't open file\n";
            return -1;
        }
        
        state.filename = std::filesystem::path(file).filename().string();
            if(state.filename.size() > 20){
        state.filename = state.filename.substr(0,15) + "...";
    }
        state.duration = state.music.getDuration().asSeconds();
        state.hasFile = true;
        state.playing  = true;
        state.status   = "Playing";
        state.music.play();

    runUI(state);
    return 0;
    }
