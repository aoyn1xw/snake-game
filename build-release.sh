#!/bin/bash

# Snake Game - Release Build Script
# This script builds optimized release binaries for distribution

set -e  # Exit on any error

# Configuration
PROJECT_NAME="snake-game"
BUILD_DIR="build-release"
PACKAGE_DIR="packages"
VERSION=${1:-"1.0.0"}

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Helper functions
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Print banner
echo "=========================================="
echo "  Snake Game - Release Build Script"
echo "  Version: $VERSION"
echo "=========================================="
echo

# Check prerequisites
log_info "Checking prerequisites..."

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    log_error "CMake not found. Please install CMake 3.10 or later."
    exit 1
fi

# Check CMake version
CMAKE_VERSION=$(cmake --version | head -n1 | grep -o '[0-9]\+\.[0-9]\+')
CMAKE_MAJOR=$(echo $CMAKE_VERSION | cut -d. -f1)
CMAKE_MINOR=$(echo $CMAKE_VERSION | cut -d. -f2)

if [ "$CMAKE_MAJOR" -lt 3 ] || ([ "$CMAKE_MAJOR" -eq 3 ] && [ "$CMAKE_MINOR" -lt 10 ]); then
    log_error "CMake version $CMAKE_VERSION found. Please install CMake 3.10 or later."
    exit 1
fi

log_success "CMake $CMAKE_VERSION found"

# Check for compiler
if command -v g++ &> /dev/null; then
    COMPILER="g++"
    COMPILER_VERSION=$(g++ --version | head -n1)
elif command -v clang++ &> /dev/null; then
    COMPILER="clang++"
    COMPILER_VERSION=$(clang++ --version | head -n1)
else
    log_error "No suitable C++ compiler found. Please install g++ or clang++."
    exit 1
fi

log_success "Compiler: $COMPILER_VERSION"

# Check for SFML (optional)
if pkg-config --exists sfml-all 2>/dev/null; then
    SFML_VERSION=$(pkg-config --modversion sfml-all)
    log_success "SFML $SFML_VERSION found - GUI mode will be available"
    SFML_AVAILABLE=true
elif find /usr -name "libsfml*" 2>/dev/null | head -1 | grep -q sfml; then
    log_success "SFML libraries found - GUI mode will be available"
    SFML_AVAILABLE=true
else
    log_warning "SFML not found - only CLI mode will be available"
    SFML_AVAILABLE=false
fi

# Clean previous builds
log_info "Cleaning previous builds..."
rm -rf "$BUILD_DIR" "$PACKAGE_DIR"
mkdir -p "$BUILD_DIR" "$PACKAGE_DIR"

# Configure build
log_info "Configuring release build..."
cd "$BUILD_DIR"

cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-O3 -DNDEBUG -march=native" \
    -DCMAKE_INSTALL_PREFIX="install"

# Build
log_info "Building project..."
NPROC=$(nproc 2>/dev/null || echo 4)
make -j$NPROC

if [ ! -f "$PROJECT_NAME" ]; then
    log_error "Build failed - executable not found"
    exit 1
fi

log_success "Build completed successfully"

# Test the executable
log_info "Testing executable..."
if echo "3" | timeout 5 ./$PROJECT_NAME > /dev/null 2>&1; then
    log_success "Executable test passed"
else
    log_warning "Executable test failed or timed out (this may be normal)"
fi

# Get build information
EXECUTABLE_SIZE=$(ls -la $PROJECT_NAME | awk '{print $5}')
EXECUTABLE_SIZE_KB=$((EXECUTABLE_SIZE / 1024))

# Check what libraries are linked
log_info "Checking dependencies..."
if command -v ldd &> /dev/null; then
    LINKED_LIBS=$(ldd $PROJECT_NAME 2>/dev/null | wc -l)
    SFML_LINKED=$(ldd $PROJECT_NAME 2>/dev/null | grep -c sfml || echo 0)
    
    if [ "$SFML_LINKED" -gt 0 ]; then
        log_success "SFML successfully linked ($SFML_LINKED libraries)"
        PACKAGE_SUFFIX="gui"
    else
        log_warning "SFML not linked - CLI mode only"
        PACKAGE_SUFFIX="cli"
    fi
    
    log_info "Total linked libraries: $LINKED_LIBS"
fi

# Create package
cd ..
log_info "Creating release package..."

PLATFORM=$(uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(uname -m)
PACKAGE_NAME="${PROJECT_NAME}-v${VERSION}-${PLATFORM}-${ARCH}-${PACKAGE_SUFFIX}"

# Copy files to package directory
cp "$BUILD_DIR/$PROJECT_NAME" "$PACKAGE_DIR/"
cp README.md "$PACKAGE_DIR/"
cp LICENSE "$PACKAGE_DIR/"
cp BUILD.md "$PACKAGE_DIR/"
cp CHANGELOG.md "$PACKAGE_DIR/"

# Create installation script
cat > "$PACKAGE_DIR/install.sh" << 'EOF'
#!/bin/bash
# Snake Game - Installation Script

echo "Installing Snake Game..."

# Make executable
chmod +x snake-game

# Try to install to /usr/local/bin (requires sudo)
if [ "$EUID" -eq 0 ] || sudo -n true 2>/dev/null; then
    echo "Installing to /usr/local/bin..."
    sudo cp snake-game /usr/local/bin/
    echo "Installation complete! Run 'snake-game' from anywhere."
else
    echo "No sudo access. You can run ./snake-game from this directory"
    echo "or manually copy snake-game to a directory in your PATH."
fi
EOF

chmod +x "$PACKAGE_DIR/install.sh"

# Create README for package
cat > "$PACKAGE_DIR/README-PACKAGE.txt" << EOF
Snake Game v$VERSION
===================

Thank you for downloading Snake Game!

QUICK START:
1. Extract this package
2. Run: ./snake-game
3. Choose [1] CLI or [2] GUI mode

INSTALLATION (Optional):
- Run: ./install.sh
- This will install to /usr/local/bin

SYSTEM REQUIREMENTS:
- OS: Linux (tested on Ubuntu 18.04+)
- Memory: 50MB RAM
- Storage: 10MB disk space
$([ "$SFML_AVAILABLE" = true ] && echo "- Graphics: OpenGL support (GUI mode)")

FEATURES:
- Cross-platform Snake game
- CLI mode: Terminal-based ASCII graphics
$([ "$SFML_LINKED" -gt 0 ] && echo "- GUI mode: Modern graphics with SFML")
- Real-time controls (WASD/Arrow keys)
- Score tracking and collision detection

CONTROLS:
- CLI Mode: WASD or Arrow keys, Q to quit
$([ "$SFML_LINKED" -gt 0 ] && echo "- GUI Mode: Arrow keys, ESC to quit")

SUPPORT:
- Issues: https://github.com/aoyn1xw/snake-game/issues
- Documentation: https://github.com/aoyn1xw/snake-game

Build Information:
- Version: $VERSION
- Platform: $PLATFORM-$ARCH
- Compiler: $COMPILER_VERSION
- Executable size: ${EXECUTABLE_SIZE_KB}KB
$([ "$SFML_LINKED" -gt 0 ] && echo "- SFML support: Yes" || echo "- SFML support: No (CLI only)")
- Build date: $(date)

Enjoy the game! 🐍
EOF

# Create archive
cd "$PACKAGE_DIR"
tar -czf "../${PACKAGE_NAME}.tar.gz" *
cd ..

# Generate checksums
log_info "Generating checksums..."
sha256sum "${PACKAGE_NAME}.tar.gz" > "${PACKAGE_NAME}.sha256"

# Final summary
echo
echo "=========================================="
echo "        BUILD SUMMARY"
echo "=========================================="
echo "✅ Version: $VERSION"
echo "✅ Platform: $PLATFORM-$ARCH ($COMPILER)"
echo "✅ Executable size: ${EXECUTABLE_SIZE_KB}KB"
echo "✅ SFML support: $([ "$SFML_LINKED" -gt 0 ] && echo "Yes (GUI + CLI)" || echo "No (CLI only)")"
echo "✅ Package: ${PACKAGE_NAME}.tar.gz"
echo "✅ Checksum: ${PACKAGE_NAME}.sha256"
echo
echo "📦 Package contents:"
ls -la "$PACKAGE_DIR/"
echo
echo "📋 Package size: $(ls -la "${PACKAGE_NAME}.tar.gz" | awk '{print $5}') bytes"
echo

log_success "Release build completed successfully!"
echo
echo "🚀 To distribute:"
echo "   Upload ${PACKAGE_NAME}.tar.gz and ${PACKAGE_NAME}.sha256"
echo
echo "🧪 To test:"
echo "   cd $PACKAGE_DIR && ./snake-game"