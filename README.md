## 🛠️ Installing raylib on Linux (Ubuntu/Debian-based)

This project uses **[raylib](https://github.com/raysan5/raylib)** (latest version ~6.x as of May 2026). The following commands will install all required build tools and system dependencies, then build and install the **static library** system-wide (the recommended default for most projects).

### Quick Installation

```bash
# Update and install build tools + raylib dependencies
sudo apt update
sudo apt install -y build-essential git \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev \
    libgl1-mesa-dev libglu1-mesa-dev libwayland-dev libxkbcommon-dev pkg-config

# Clone raylib (shallow clone = fast, gets latest version)
git clone --depth 1 https://github.com/raysan5/raylib.git ~/raylib-temp
cd ~/raylib-temp/src

# Build static library (default & recommended) and install system-wide
make PLATFORM=PLATFORM_DESKTOP
sudo make install

# Clean up
cd ../..
rm -rf ~/raylib-temp

# Make sure the dynamic linker knows about the new library
# (important on some systems, WSL, and fresh installs)
sudo ldconfig
