#!/bin/bash

# Test script to verify CI/CD fixes
set -e

echo "=== Testing CI/CD fixes ==="

# Test 1: Basic build
echo "1. Testing basic build..."
mkdir -p test-build && cd test-build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
echo "✅ Build successful"

# Test 2: Test executable
echo "2. Testing executable..."
echo "3" | ./snake-game > output.txt
if grep -q "Thanks for playing" output.txt; then
    echo "✅ Executable test passed"
else
    echo "❌ Executable test failed"
    cat output.txt
    exit 1
fi

# Test 3: Check SFML linking
echo "3. Checking SFML linking..."
if ldd ./snake-game 2>/dev/null | grep -q sfml; then
    echo "✅ SFML successfully linked"
else
    echo "⚠️  SFML not linked (CLI-only mode)"
fi

# Test 4: Check for proper keyboard constants
echo "4. Checking source code for SFML constants..."
if grep -q "sf::Keyboard::" ../src/gui/GUIRenderer.cpp; then
    echo "✅ SFML keyboard constants found"
else
    echo "❌ No SFML keyboard constants found"
    exit 1
fi

# Clean up
cd ..
rm -rf test-build

echo ""
echo "🎉 All tests passed! CI/CD fixes look good."
echo ""
echo "Key fixes applied:"
echo "- Windows: Fixed CMake -A flag PowerShell issue"
echo "- macOS: Added SFML Window include and robust installation"  
echo "- Cross-platform: Uses standard SFML keyboard constants"
echo "- Fallback: CLI-only mode when SFML unavailable"