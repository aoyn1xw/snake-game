# Changelog

All notable changes to the Snake Game project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Comprehensive CI/CD pipeline with GitHub Actions
- Automated release builds for Windows, Linux, and macOS
- Security scanning with CodeQL
- Documentation validation in CI

### Changed
- Enhanced README with better formatting and comprehensive information
- Improved build instructions with platform-specific guidance

## [1.0.0] - 2025-09-26

### Added
- **Core Game Engine**
  - Classic Snake game mechanics with collision detection
  - Configurable board size (40x20 default)
  - Score tracking and food generation system
  - Game over detection and handling

- **Dual Rendering System**
  - CLI mode with ASCII graphics (`#` for snake, `*` for food)
  - GUI mode with SFML graphics (green rectangles, red circles)
  - Polymorphic renderer architecture with abstract base class

- **Cross-Platform Support**
  - Windows support with `conio.h` for input handling
  - Linux/macOS support with `termios` for terminal control
  - Platform-specific cursor and terminal management

- **Input Handling**
  - CLI mode: WASD keys and arrow key support
  - GUI mode: Arrow key navigation
  - Quit functionality (Q/ESC in CLI, ESC/window close in GUI)

- **Build System**
  - CMake build configuration with automatic SFML detection
  - Graceful degradation to CLI-only mode if SFML unavailable
  - Cross-platform compiler support (GCC, Clang, MSVC)

- **Menu System**  
  - Interactive start menu with mode selection
  - Input validation and error handling
  - Clean program flow and exit handling

### Technical Details
- **Language**: C++17 standard compliance
- **Architecture**: Clean separation between game logic and rendering
- **Memory Management**: RAII principles, no memory leaks
- **Performance**: Fixed timestep game updates (10 FPS CLI, 60 FPS GUI)
- **Error Handling**: Comprehensive error messages and graceful failures

### Project Structure
```
snake-game/
├── CMakeLists.txt      # Build configuration
├── README.md          # Project documentation
├── src/
│   ├── main.cpp       # Entry point and menu
│   ├── game/          # Core game logic
│   ├── cli/           # Terminal renderer
│   └── gui/           # SFML renderer
```

### Dependencies
- **Required**: C++17 standard library, CMake 3.10+
- **Optional**: SFML 2.5+ (enables GUI mode)

### Platform Compatibility
- ✅ **Ubuntu 18.04+** (GCC 7+, Clang 5+)
- ✅ **Windows 10+** (MSVC 2017+, MinGW)
- ✅ **macOS 10.14+** (Xcode 10+, Homebrew GCC/Clang)

---

## Release Notes Format

### Types of Changes
- **Added** - New features
- **Changed** - Changes to existing functionality  
- **Deprecated** - Soon-to-be removed features
- **Removed** - Removed features
- **Fixed** - Bug fixes
- **Security** - Vulnerability fixes

### Version History Links
- [Unreleased]: https://github.com/aoyn1xw/snake-game/compare/v1.0.0...HEAD
- [1.0.0]: https://github.com/aoyn1xw/snake-game/releases/tag/v1.0.0