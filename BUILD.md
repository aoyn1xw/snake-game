# Build Instructions for Snake Game

## Quick Build Guide

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or later
- SFML 2.5+ (optional, for GUI mode)

### Building the Project

1. **Create build directory:**
   ```bash
   mkdir build && cd build
   ```

2. **Configure with CMake:**
   ```bash
   cmake ..
   ```

3. **Build:**
   ```bash
   make
   # Or on Windows with Visual Studio:
   # cmake --build . --config Release
   ```

### Install SFML (Optional for GUI Mode)

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### Fedora/RHEL:
```bash
sudo dnf install SFML-devel
```

#### macOS (Homebrew):
```bash
brew install sfml
```

#### Windows:
Download SFML from https://www.sfml-dev.org/ and extract to `C:\SFML\`

### Running the Game

```bash
./snake-game  # Linux/macOS
snake-game.exe  # Windows
```

### Game Controls

**CLI Mode:**
- Movement: `WASD` or Arrow Keys
- Quit: `Q` or `ESC`

**GUI Mode:**
- Movement: Arrow Keys
- Quit: `ESC` or close window

### Build Output Status

The build system will automatically detect SFML and provide status:
- ✅ **SFML found** - Both CLI and GUI modes available
- ⚠️  **SFML not found** - CLI mode only

### Troubleshooting

1. **SFML not found:** Install SFML development packages and rebuild
2. **Build errors:** Ensure C++17 support and CMake 3.10+
3. **Runtime issues:** Check that all dependencies are properly installed

### Cross-platform Notes

- **Linux/macOS:** Uses `termios` for CLI input
- **Windows:** Uses `conio.h` for CLI input
- **All platforms:** SFML handles GUI windowing uniformly