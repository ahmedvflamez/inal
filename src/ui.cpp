
#include "ui.h"
#include "player.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>

using namespace ftxui;

void runUI(PlayerState& s){
    auto screen = ScreenInteractive::Fullscreen();

    InputOption style;
        style.transform = [](InputState state) {
        if(state.is_placeholder) {
        return state.element | color(Color::GrayDark);
    }
        return state.element | color(Color::Default);
    };
    
    Component input = Input(&s.cmd, R"(type "help"?)", style) | size(WIDTH, LESS_THAN, 30) | italic;

    auto ui = Renderer(input, [&]{

    Color statusColor = [&]() -> Color {
        if (s.loop)  return Color::Yellow;;
        if (s.playing)   return Color::Green;
    return Color::Red;
    }();

        return vbox({
            text("" + s.status + ": "+ std::string(s.filename)) | color(statusColor) | bold | italic,
            gauge(s.progress) | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 25) | color(Color::Green),
            text("        " + std::to_string((int)s.current) + "s / " + std::to_string((int)s.duration) + "s") | dim | color(Color::GrayLight),
            separator() | size(WIDTH, EQUAL, 25),
            hbox({             hbox({
                text("i") | color(Color::RGB(192, 132, 168)),
                text("n") | color(Color::RGB(164, 123, 181)),
                text("a") | color(Color::RGB(139, 116, 199)),
                text("l") | color(Color::RGB(123, 143, 212)),
                text("♪: "),
            }), input->Render()}),

        s.showHelp ? vbox({
            text("  stop              - Stop playing") | dim,
            text("  loop              - Toggle loop") | dim,
            text("  seek <secs>       - Jump to position") | dim,
            text("  volume <0-100>    - Set volume") | dim,
            text("  play <filename>   - Restart file") | dim,
            text("  quit              - Quit program") | dim,
            text("  switch <filename> - Switches to other file") | dim,
    }) : s.showFileError ? vbox({
            text("Error opening file!") | color(Color::Red) | dim,
    })  : text(""),
        
        });
    });
        auto cmds = CatchEvent(ui, [&](Event event) {
        if (event == Event::Return) {
            s.cmd.erase(s.cmd.find_last_not_of(" \n\r\t") + 1);
 
            if (s.cmd == "quit") {
                s.isRunning = false;
                screen.ExitLoopClosure()();
                return true;
            }
 
            handleCommands(s.cmd, s);
            s.cmd = "";
            return true;
        }
        return false;
    });

std::thread refresh([&]{
        while (true){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            s.current = s.music.getPlayingOffset().asSeconds();
            s.progress = (s.duration > 0) ? s.current / s.duration : 0.f;

            if (s.showHelp || s.showFileError) {
                auto time = std::chrono::steady_clock::now() - s.noteTime;
                if (time >= std::chrono::seconds(3)) {
                    s.showHelp = false;
                    s.showFileError = false;
                }
            }

            if(!s.replaying && s.playing && s.music.getStatus() == sf::Music::Stopped) {
                if(s.loop){
                    s.music.setPlayingOffset(sf::seconds(0));
                    s.music.play();
                } else {
                s.status = "Ended";
                s.playing = false;
            }
        }
            screen.PostEvent(Event::Custom);
        }
    });

    refresh.detach();
    screen.Loop(cmds);
}
