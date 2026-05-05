# CFG3 - C Fighting Game 3

![GitHub repo](https://img.shields.io/badge/Language-C-00599C?logo=c)
![Raylib](https://img.shields.io/badge/Made%20with-raylib-000000?logo=raylib)
[![YouTube](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://youtube.com/roundbeargames)

**A lightweight, performant 2D fighting game prototype** written in pure **C** using the [raylib](https://github.com/raysan5/raylib) library.

CFG3 (C_Fighting_Game_3) is the third iteration of a minimalistic fighting game built from the ground up. The focus is on clean code, high performance, easy compilation, and educational readability — for learning game development with raylib or experimenting with fighting game mechanics in C.

**Current Status**: Early development / Prototype (as of May 2026)

---

## 🚀 Getting Started (Linux / Ubuntu / Debian / WSL2)

The process installs **raylib** system-wide (the simplest and most common method for raylib projects) and then builds and runs the game.

### Step 1: Install raylib (System-wide)

```bash
sudo apt update
sudo apt install -y build-essential git \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu1-mesa-dev libwayland-dev libxkbcommon-dev pkg-config

# Clone the exact pinned release (fast shallow clone)
git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git ~/raylib-temp
cd ~/raylib-temp/src

# Build static library (default & recommended) and install system-wide
make PLATFORM=PLATFORM_DESKTOP
sudo make install

# Clean up
cd ../..
rm -rf ~/raylib-temp

# Make sure the dynamic linker knows about the new library
sudo ldconfig
```

### Step 2: Clone and Run CFG3
```bash
# Clone the repository
git clone https://github.com/RoundBearChoi/CFG3.git
cd CFG3

# Build and run the game
make run
```

---
