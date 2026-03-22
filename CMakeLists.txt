cmake_minimum_required(VERSION 3.16)
project(inal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(SFML 2 REQUIRED COMPONENTS audio)

fetchcontent_declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v6.1.9
)
fetchcontent_makeavailable(ftxui)

add_executable(inal
    src/main.cpp
    src/player.cpp
    src/ui.cpp         
)

target_include_directories(inal PRIVATE include)
target_link_libraries(inal PRIVATE
    ftxui::component
    ftxui::dom
    ftxui::screen
    sfml-audio
)
