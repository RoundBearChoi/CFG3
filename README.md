# CFG3 - C Fighting Game 3
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://www.c-language.org/)
[![raylib](https://img.shields.io/badge/raylib-00599C?style=for-the-badge&logo=raylib&logoColor=white)](https://www.raylib.com/)
[![GNU Make](https://img.shields.io/badge/GNU%20Make-00599C?style=for-the-badge&logo=gnu&logoColor=white)](https://www.gnu.org/software/make/)

CFG3 is a lightweight, performant 2D fighting game written in pure C using [raylib](https://github.com/raysan5/raylib) library. Focus is on clean code, high performance, easy compilation, and educational readability — for learning game development with raylib or experimenting with fighting game mechanics.

Follow dev journey on [YouTube](https://youtube.com/roundbeargames), [Discord](https://discord.gg/hAFTgcA)

---

## 🚀 Getting Started (Linux / Ubuntu / Debian / WSL2)

### Step 1: Install raylib system-wide (simplest and most common)

```bash
sudo apt update
sudo apt install -y build-essential git \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu1-mesa-dev libwayland-dev libxkbcommon-dev pkg-config

# Clone exact pinned release
git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git ~/raylib-temp
cd ~/raylib-temp/src

# Build static library (default & recommended) and install system-wide
make PLATFORM=PLATFORM_DESKTOP
sudo make install

# Clean up
cd ../..
rm -rf ~/raylib-temp

# Make sure dynamic linker knows about new library
sudo ldconfig
```

### Step 2: Clone and Run CFG3
```bash
# Clone repository
git clone https://github.com/RoundBearChoi/CFG3.git
cd CFG3

# Build and run game
make run
```

---
