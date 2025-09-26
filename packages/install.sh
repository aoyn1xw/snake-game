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
