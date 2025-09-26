#pragma once

#include "../game/SnakeGame.h"
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

class CLIRenderer : public Renderer {
public:
    CLIRenderer();
    ~CLIRenderer();
    
    void render(const SnakeGame& game) override;
    void clear() override;
    void showGameOver(int score) override;
    
    // Input handling
    bool hasInput();
    char getInput();
    Direction getDirectionFromInput(char input);
    
private:
    void setupTerminal();
    void restoreTerminal();
    void hideCursor();
    void showCursor();
    void moveCursor(int x, int y);
    
#ifndef _WIN32
    struct termios originalTermios;
    bool terminalModified;
#endif
};