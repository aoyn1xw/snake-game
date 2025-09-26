# 🐍 Snake Game

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.10+-green.svg)](https://cmake.org/)
[![SFML](https://img.shields.io/badge/SFML-2.5+-red.svg)](https://www.sfml-dev.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

A modern, cross-platform Snake game implemented in C++17 that supports both CLI (Terminal) and GUI (Graphical) modes with a unified codebase. Features clean architecture, real-time input handling, and professional game development practices.

![Snake Game Demo](https://img.shields.io/badge/Demo-Available-brightgreen.svg)

## 📸 Screenshots

### CLI Mode (Terminal)
```
+----------------------------------------+
|                   *                    |
|                                        |
|     ###                                |
|     #                                  |
|     #                                  |
|                                        |
|                                        |
+----------------------------------------+
Score: 30
Controls: WASD or Arrow Keys | Q to quit
```

### GUI Mode (Graphics)
*Clean SFML-based interface with smooth animations, green snake segments, and red food items on a black background.*

## ✨ Features

### 🎮 **Dual Mode Support**
- **CLI Mode**: Play in your terminal with ASCII graphics
- **GUI Mode**: Modern graphical interface using SFML
- **Seamless switching**: Choose your preferred mode at startup

### 🛠 **Technical Excellence**
- **Cross-Platform**: Runs on Windows, Linux, and macOS
- **Modern C++17**: Clean, efficient, and maintainable code
- **Unified Architecture**: Single game logic, multiple renderers
- **Polymorphic Design**: Abstract base classes for extensibility
- **Real-time Input**: Responsive controls in both modes
- **Smart Build System**: Automatic dependency detection

### 🎯 **Game Features**
- Classic Snake gameplay mechanics
- Score tracking and display
- Collision detection (walls and self)
- Food generation with overlap prevention
- Game over handling
- Configurable game speed

## 🚀 Quick Start

### Download Pre-built Binaries
Check the [Releases](../../releases) page for pre-compiled binaries for your platform:
- **Windows**: `snake-game-windows.zip`
- **Linux**: `snake-game-linux.tar.gz`  
- **macOS**: `snake-game-macos.tar.gz`

### Run from Binary
```bash
# Extract the archive and run
./snake-game    # Linux/macOS
snake-game.exe  # Windows
```

## 🎮 Game Modes

### 🖥️ CLI Mode
- **Rendered in terminal** using ASCII characters
- **Snake segments**: `#` (hash symbols)
- **Food items**: `*` (asterisks)  
- **Controls**: `WASD` or Arrow keys
- **Quit**: `Q` or `ESC`
- **Frame rate**: 10 FPS for optimal terminal performance
- **Compatibility**: Works in any terminal emulator

### 🎨 GUI Mode  
- **Graphical interface** using SFML library
- **Window size**: 800x600 pixels with centered game area
- **Visual elements**:
  - 🟢 Green snake segments (rectangles)
  - 🔴 Red food items (circles)
  - ⚪ Score display (top-left corner)
  - ⬛ Grid-based movement (20x20 pixel cells)
- **Controls**: Arrow keys only
- **Quit**: `ESC` or close window
- **Frame rate**: 60 FPS rendering, ~6.7 FPS gameplay

## 📋 Prerequisites & Installation

### 🎯 System Requirements
| Component | Minimum | Recommended |
|-----------|---------|-------------|
| **OS** | Windows 10, Ubuntu 18.04, macOS 10.14 | Latest stable versions |
| **Compiler** | GCC 7+, Clang 5+, MSVC 2017+ | GCC 11+, Clang 13+ |
| **CMake** | 3.10+ | 3.20+ |
| **Memory** | 50MB RAM | 100MB RAM |
| **Storage** | 10MB | 20MB |

### 🛠 Required (CLI Mode Only)
- C++17 compatible compiler
- CMake 3.10 or higher
- Standard library (no external dependencies)

### 🎨 Optional (Enable GUI Mode)
- **SFML 2.5+** development libraries
- OpenGL-compatible graphics driver

### 📦 Installing SFML

#### 🐧 Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### 🎩 Fedora/RHEL/CentOS
```bash
sudo dnf install SFML-devel
# or for older versions:
sudo yum install SFML-devel
```

#### 🍎 macOS (Homebrew)
```bash
brew install sfml
```

#### 🍎 macOS (MacPorts)
```bash
sudo port install sfml
```

#### 🪟 Windows

**Option 1: vcpkg (Recommended)**
```cmd
vcpkg install sfml:x64-windows
```

**Option 2: Manual Installation**
1. Download SFML from [official website](https://www.sfml-dev.org/download.php)
2. Extract to `C:\SFML\` 
3. Set environment variables or use CMake options

## 🔧 Building from Source

### 🚀 Quick Build (Linux/macOS)
```bash
git clone https://github.com/aoyn1xw/snake-game.git
cd snake-game
mkdir build && cd build
cmake ..
make -j$(nproc)
./snake-game
```

### 🪟 Windows Build (Visual Studio)
```cmd
git clone https://github.com/aoyn1xw/snake-game.git
cd snake-game
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
.\Release\snake-game.exe
```

### ⚙️ Advanced Build Options

#### Custom SFML Path
```bash
cmake .. -DCMAKE_PREFIX_PATH="/path/to/sfml"
```

#### Debug Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

#### Release with Optimizations
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

#### CLI Only (No SFML)
If you want to build without SFML dependency:
```bash
# Remove or rename SFML libraries temporarily
sudo apt-get remove libsfml-dev  # Ubuntu
cmake .. && make
```

### 📊 Build Status Indicators
During build, CMake will report:
- ✅ **SFML found** → Both CLI and GUI modes available
- ⚠️ **SFML not found** → CLI mode only (still fully functional)

### 🎯 Build Verification
```bash
# Test the executable
echo "3" | ./snake-game  # Should show menu and quit gracefully

# Check SFML linking (if GUI enabled)
ldd ./snake-game | grep sfml  # Linux
otool -L ./snake-game | grep sfml  # macOS
```

## Usage

1. Run the executable: `./snake-game`
2. Choose from the main menu:
   - `[1]` CLI Mode - Play in terminal
   - `[2]` GUI Mode - Play with graphics (requires SFML)
   - `[3]` Quit - Exit the game

### Controls

#### CLI Mode
- **Movement**: `W`/`A`/`S`/`D` or Arrow keys
- **Quit**: `Q` or `ESC`

#### GUI Mode  
- **Movement**: Arrow keys only
- **Quit**: `ESC` or close window

## 🏗️ Architecture & Design

### 📐 Project Structure
```
snake-game/
├── 📄 CMakeLists.txt          # Build configuration
├── 📘 README.md              # This file
├── 📗 BUILD.md               # Detailed build guide
├── 📜 LICENSE                # MIT License
├── 🙈 .gitignore             # Git ignore rules
├── 🔧 .github/               # GitHub workflows & templates
│   └── workflows/
│       └── release.yml       # Automated releases
├── 🏗️  build/                 # Build artifacts (local)
└── 📁 src/                   # Source code
    ├── main.cpp              # Entry point & menu system  
    ├── 🎮 game/
    │   ├── SnakeGame.h       # Core game logic interface
    │   └── SnakeGame.cpp     # Game mechanics implementation
    ├── 💻 cli/
    │   ├── CLIRenderer.h     # Terminal renderer interface
    │   └── CLIRenderer.cpp   # ASCII graphics implementation
    └── 🎨 gui/
        ├── GUIRenderer.h     # SFML renderer interface  
        └── GUIRenderer.cpp   # Graphics implementation
```

### 🧩 Core Components

#### 1. **Game Engine** (`SnakeGame`)
- 🐍 Snake movement and growth logic
- 🍎 Food generation and placement
- 💥 Collision detection (walls, self-collision)  
- 🎯 Score calculation and tracking
- ⏱️ Game state management

#### 2. **Renderer System** (Polymorphic)
```cpp
class Renderer {
public:
    virtual void render(const SnakeGame& game) = 0;
    virtual void clear() = 0;
    virtual void showGameOver(int score) = 0;
};
```

#### 3. **Platform Abstraction**
- **Cross-platform input handling**
- **Terminal control** (cursor, colors, clearing)
- **Window management** (SFML integration)

### 🎨 Design Patterns Used

| Pattern | Implementation | Benefits |
|---------|----------------|----------|
| **Strategy** | `CLIRenderer` vs `GUIRenderer` | Interchangeable rendering modes |
| **Template Method** | Game loop structure | Consistent update cycle |  
| **RAII** | Resource management | Automatic cleanup, no leaks |
| **Facade** | `SnakeGame` public interface | Simple API, complex internals |

## 🤝 Contributing

We welcome contributions! Here's how you can help improve the Snake Game:

### 🐛 Reporting Bugs
1. Check [existing issues](../../issues) first
2. Create a new issue with:
   - **OS and version** (Ubuntu 20.04, Windows 11, etc.)
   - **Compiler version** (`gcc --version`)
   - **Steps to reproduce**
   - **Expected vs actual behavior**
   - **Build configuration** (CLI only, GUI enabled, etc.)

### 💡 Feature Requests  
- 🎵 Sound effects and background music
- 🎨 Theme customization and color schemes
- 🏆 High score persistence and leaderboards
- 🌐 Multiplayer support (local/network)
- 📱 Mobile platform support (Android/iOS)
- 🎮 Gamepad/controller support

### 🔧 Development Setup
```bash
# Fork and clone your fork
git clone https://github.com/YOUR_USERNAME/snake-game.git
cd snake-game

# Create feature branch
git checkout -b feature/awesome-new-feature

# Make your changes and test
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make

# Run tests (if applicable)
./snake-game

# Commit with clear message
git commit -m "Add awesome new feature"
git push origin feature/awesome-new-feature

# Open Pull Request
```

### 📋 Code Style Guidelines
- **C++17 standard** compliance
- **4-space indentation** (no tabs)
- **Clear variable names** (`snakeBody` not `sb`)
- **RAII principles** for resource management
- **const-correctness** where applicable
- **Documentation** for public interfaces

### 🧪 Testing Checklist
- [ ] Compiles on Linux (GCC)
- [ ] Compiles on Windows (MSVC)
- [ ] Compiles on macOS (Clang)
- [ ] Works without SFML (CLI only)
- [ ] Works with SFML (GUI mode)
- [ ] No memory leaks (Valgrind)
- [ ] Menu navigation works
- [ ] Game controls responsive
- [ ] Game over handling correct

## 🎯 Roadmap

### 🚀 Version 1.1 (Planned)
- [ ] **Sound System**: Background music and sound effects
- [ ] **Settings Menu**: Customizable controls and game speed  
- [ ] **High Scores**: Local score persistence
- [ ] **Pause Function**: Pause/resume gameplay

### 🌟 Version 2.0 (Future)
- [ ] **Network Multiplayer**: Real-time online gameplay
- [ ] **AI Players**: Computer-controlled snakes
- [ ] **Level Editor**: Custom game maps
- [ ] **Mobile Support**: Android and iOS versions

## 🐛 Known Issues

### ⚠️ Current Limitations
- **Terminal resize**: CLI mode doesn't handle terminal resizing
- **Arrow keys**: May not work in all terminal emulators
- **Windows fonts**: Default font might not load on some systems
- **High DPI**: GUI scaling issues on high-DPI displays

### 🔧 Workarounds
- Use WASD keys if arrows don't work
- Restart after terminal resize
- Install system fonts for better GUI experience

## 📊 Performance

### 🎮 Benchmarks (Typical Performance)
| Mode | CPU Usage | Memory Usage | Frame Rate |
|------|-----------|--------------|------------|
| CLI  | < 1%      | ~2MB        | 10 FPS     |
| GUI  | < 5%      | ~15MB       | 60 FPS     |

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### � What this means:
- ✅ **Commercial use** allowed
- ✅ **Modification** allowed  
- ✅ **Distribution** allowed
- ✅ **Private use** allowed
- ❌ **No warranty** provided
- ❌ **No liability** assumed

## 🙏 Acknowledgments

### 🛠️ Technologies Used
- **[SFML](https://www.sfml-dev.org/)** - Simple and Fast Multimedia Library
- **[CMake](https://cmake.org/)** - Cross-platform build system
- **C++17** - Modern C++ standard

### 🎨 Inspiration
- Classic Snake games from Nokia phones
- Modern terminal-based games
- Cross-platform game development principles

### 📚 References
- [SFML Documentation](https://www.sfml-dev.org/documentation/)
- [CMake Documentation](https://cmake.org/documentation/)
- [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines)

## 📞 Support

### 💬 Community
- **Issues**: [GitHub Issues](../../issues)
- **Discussions**: [GitHub Discussions](../../discussions)

### 📧 Contact
- **Project Maintainer**: [@aoyn1xw](https://github.com/aoyn1xw)
- **Email**: Create an issue for bug reports and feature requests

### ⭐ Show Your Support
If you found this project helpful:
- ⭐ **Star** this repository
- 🍴 **Fork** it for your own modifications
- 📢 **Share** it with others
- 🐛 **Report bugs** you find
- 💡 **Suggest features** you'd like to see

---

<div align="center">

**Made with ❤️ and C++17**

[⬆️ Back to Top](#-snake-game)

</div>