# inal

> A CLI audio player written in C++.

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2-8CC445?style=flat&logo=sfml&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green?style=flat)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=flat)

---

## 📖 About

**inal** is an audio player that runs entirely in your terminal.

---

## 🧱 Dependencies

| Library | How to get it |
|---|---|
| [SFML 2](https://www.sfml-dev.org/) | Install manually (see below) |
| [FTXUI v6.1.9](https://github.com/ArthurSonzogni/ftxui) | Auto-downloaded by CMake via FetchContent |

> You only need to install SFML. CMake handles FTXUI automatically at build time.

---

## ⚙️ Installation

### Prerequisites

- C++17 compatible compiler (`g++`, `clang++`, or MSVC)
- CMake 3.16+
- Git (required for CMake to fetch FTXUI)
- SFML 2

**Install SFML 2:**

```bash
# Ubuntu / Debian
sudo apt install libsfml-dev

# Fedora
sudo dnf install SFML-devel

# macOS
brew install sfml

# Windows
# Download from https://www.sfml-dev.org/download.php
```

### Build

```bash
git clone https://github.com/yourusername/player.git
cd player
mkdir build && cd build
cmake ..
cmake --build .
```

> CMake will automatically download FTXUI during the first build | internet connection required.

---

## 🚀 Usage

```bash
./inal <filename>
```

**Examples:**

```bash
./inal file.mp3
./inal "file.mp3"
./inal /home/user/music/song.wav
```

**Supported formats:** `.mp3` `.wav` `.ogg` `.flac`

---

## 🎮 Commands

Type commands into the `inal♪: ` prompt while the player is running.

| Command | Description |
|---|---|
| `play` | Replay current song from the start |
| `stop` | Stop playback |
| `loop` | Toggle loop (run again to stop looping) |
| `seek <seconds>` | Jump to a position — e.g. `seek 50` |
| `volume <0-100>` | Set volume — e.g. `volume 75` |
| `switch <file>` | Switch to a different file |
| `help` | Show all commands (disappears after 3 seconds) |
| `quit` | Exit the program |

> Filenames with spaces are supported: `switch "my song.mp3"` or `switch my song.mp3`

---

> **Note:** Windows/MacOS compatibility is not tested but expected.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
