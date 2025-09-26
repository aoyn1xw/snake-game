# Contributing to Snake Game

Thank you for your interest in contributing to the Snake Game project! 🎮

## 🚀 Quick Start for Contributors

### Prerequisites
- **C++17** compatible compiler
- **CMake 3.10+**
- **Git** for version control
- **SFML 2.5+** (optional, for GUI development)

### Development Setup
```bash
# 1. Fork the repository on GitHub
# 2. Clone your fork
git clone https://github.com/aoyn1xw/snake-game.git
cd snake-game

# 3. Add upstream remote
git remote add upstream https://github.com/aoyn1xw/snake-game.git

# 4. Create a feature branch
git checkout -b feature/your-feature-name

# 5. Build and test
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
./snake-game
```

## 🐛 Reporting Issues

### Before Creating an Issue
1. **Search existing issues** to avoid duplicates
2. **Test with the latest version** from the main branch
3. **Check the documentation** (README.md, BUILD.md)

### Issue Template
When creating an issue, please include:

**Bug Reports:**
```markdown
## 🐛 Bug Description
Brief description of the issue

## 🔄 Steps to Reproduce
1. Step one
2. Step two  
3. Step three

## 💭 Expected Behavior
What should happen

## 🔍 Actual Behavior
What actually happens

## 🖥️ Environment
- OS: [Ubuntu 20.04, Windows 11, macOS 13]
- Compiler: [GCC 11.2, Clang 14, MSVC 2022]
- CMake version: [3.22.1]
- SFML version: [2.5.1] (if applicable)
- Build mode: [CLI only, GUI enabled]

## 📎 Additional Context
Screenshots, logs, or other relevant information
```

**Feature Requests:**
```markdown
## 💡 Feature Description
Clear description of the proposed feature

## 🎯 Use Case
Why this feature would be useful

## 💭 Proposed Implementation
How you think this could be implemented

## 🔀 Alternatives Considered
Other approaches you've thought about
```

## 🔧 Development Guidelines

### Code Style
- **C++17 standard** compliance
- **4 spaces** for indentation (no tabs)
- **LF line endings** (Unix style)
- **const-correctness** where applicable
- **RAII** for resource management
- **Clear naming conventions**:
  - Variables: `camelCase` (`snakeBody`, `gameScore`)
  - Functions: `camelCase` (`updateGame()`, `renderScreen()`)
  - Classes: `PascalCase` (`SnakeGame`, `CLIRenderer`)
  - Constants: `UPPER_SNAKE_CASE` (`BOARD_WIDTH`, `MAX_SCORE`)

### Code Structure
```cpp
// File header example
/*
 * SnakeGame.cpp
 * Core game logic implementation
 */

#include "SnakeGame.h"
#include <algorithm>
#include <random>

// Implementation...
```

### Documentation
- **Public interfaces** must have clear documentation
- **Complex algorithms** should be explained
- **TODO comments** for planned improvements
- **FIXME comments** for known issues

### Testing
Before submitting a pull request, ensure:
- [ ] **Compiles** on Linux (GCC/Clang)
- [ ] **Compiles** on Windows (MSVC)  
- [ ] **Compiles** on macOS (Clang)
- [ ] **Works** with SFML (GUI mode)
- [ ] **Works** without SFML (CLI only)
- [ ] **Menu navigation** functions correctly
- [ ] **Game controls** are responsive
- [ ] **No memory leaks** (test with Valgrind on Linux)

## 🎯 Contribution Areas

### 🐛 Bug Fixes
- Platform-specific issues
- Memory leaks or performance problems
- Input handling edge cases
- Rendering glitches

### ✨ New Features
- **High Priority:**
  - Sound effects and background music
  - Game pause/resume functionality
  - Settings menu for controls/speed
  - High score persistence

- **Medium Priority:**
  - Theme/color customization
  - Additional game modes
  - Improved AI for demonstration
  - Better error messages

- **Low Priority:**
  - Network multiplayer
  - Mobile platform support
  - Level editor
  - Achievement system

### 📚 Documentation
- README improvements
- Code comments and documentation
- Build instructions for new platforms
- Tutorial videos or guides

### 🛠️ Infrastructure
- CI/CD improvements
- Build system enhancements
- Automated testing
- Package management

## 📋 Pull Request Process

### Before Submitting
1. **Update** your fork with latest upstream changes:
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

2. **Test thoroughly** on your platform
3. **Update documentation** if needed
4. **Write clear commit messages**:
   ```
   Add pause functionality to game loop
   
   - Implement pause/resume with spacebar
   - Add pause indicator to CLI renderer
   - Update GUI renderer with pause overlay
   - Add tests for pause state management
   
   Fixes #42
   ```

### Pull Request Template
```markdown
## 📝 Description
Brief description of changes

## 🔗 Related Issues  
Fixes #123, Closes #456

## 🧪 Testing
- [ ] Tested on Linux
- [ ] Tested on Windows  
- [ ] Tested on macOS
- [ ] CLI mode works
- [ ] GUI mode works
- [ ] No regressions

## 📸 Screenshots
If UI changes, include before/after screenshots

## ✅ Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] Tests added/updated
- [ ] No breaking changes
```

### Review Process
1. **Automated checks** must pass (CI/CD pipeline)
2. **Code review** by maintainers
3. **Testing** on multiple platforms
4. **Documentation** review
5. **Merge** when approved

## 🏷️ Release Process

### Version Numbering
We use [Semantic Versioning](https://semver.org/):
- **MAJOR.MINOR.PATCH** (e.g., 1.2.3)
- **Major**: Breaking changes
- **Minor**: New features, backwards compatible
- **Patch**: Bug fixes, backwards compatible

### Release Workflow
1. **Feature freeze** for release candidate
2. **Testing** across all platforms
3. **Documentation** updates
4. **Tag creation**: `git tag -a v1.2.3 -m "Release v1.2.3"`
5. **Automated release** via GitHub Actions
6. **Release notes** generation

## 🤝 Code of Conduct

### Our Standards
- **Be respectful** and inclusive
- **Be constructive** in feedback
- **Be patient** with newcomers
- **Be collaborative** in discussions

### Unacceptable Behavior
- Harassment or discrimination
- Trolling or insulting comments  
- Publishing private information
- Other unprofessional conduct

### Enforcement
Violations may result in temporary or permanent bans from the project.

## 🆘 Getting Help

### Community Support
- **GitHub Discussions**: General questions and ideas
- **GitHub Issues**: Bug reports and feature requests
- **Code Reviews**: Technical guidance during PR process

### Direct Contact
- **Project Maintainer**: [@aoyn1xw](https://github.com/aoyn1xw)
- **Response Time**: Usually within 2-3 business days

## 🎉 Recognition

Contributors will be recognized in:
- **README.md** contributors section
- **Release notes** for significant contributions
- **GitHub contributors** graph
- **Special thanks** in major releases

---

Thank you for contributing to Snake Game! Every contribution, no matter how small, helps make the project better. 🚀