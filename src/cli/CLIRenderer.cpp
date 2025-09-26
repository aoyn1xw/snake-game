#include "CLIRenderer.h"
#include <sstream>

CLIRenderer::CLIRenderer()
#ifndef _WIN32
    : terminalModified(false)
#endif
{
    setupTerminal();
    hideCursor();
}

CLIRenderer::~CLIRenderer() {
    showCursor();
    restoreTerminal();
}

void CLIRenderer::render(const SnakeGame& game) {
    moveCursor(0, 0);
    
    const auto& snake = game.getSnakeBody();
    const auto& food = game.getFoodPosition();
    int width = game.getBoardWidth();
    int height = game.getBoardHeight();
    
    std::ostringstream output;
    
    // Top border
    output << "+";
    for (int i = 0; i < width; ++i) output << "-";
    output << "+\n";
    
    // Game area
    for (int y = 0; y < height; ++y) {
        output << "|";
        for (int x = 0; x < width; ++x) {
            Position pos(x, y);
            
            if (pos == food) {
                output << "*";
            } else {
                bool isSnake = false;
                for (const auto& segment : snake) {
                    if (segment == pos) {
                        output << "#";
                        isSnake = true;
                        break;
                    }
                }
                if (!isSnake) {
                    output << " ";
                }
            }
        }
        output << "|\n";
    }
    
    // Bottom border
    output << "+";
    for (int i = 0; i < width; ++i) output << "-";
    output << "+\n";
    
    // Score
    output << "Score: " << game.getScore() << "\n";
    output << "Controls: WASD or Arrow Keys | Q to quit\n";
    
    std::cout << output.str() << std::flush;
}

void CLIRenderer::clear() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H" << std::flush;
#endif
}

void CLIRenderer::showGameOver(int score) {
    std::cout << "\n=== GAME OVER ===\n";
    std::cout << "Final Score: " << score << "\n";
    std::cout << "Press any key to return to menu...";
    std::cout << std::flush;
}

bool CLIRenderer::hasInput() {
#ifdef _WIN32
    return _kbhit();
#else
    int ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
#endif
}

char CLIRenderer::getInput() {
#ifdef _WIN32
    return _getch();
#else
    return getchar();
#endif
}

Direction CLIRenderer::getDirectionFromInput(char input) {
    switch (input) {
        case 'w': case 'W': 
            return Direction::UP;
        case 's': case 'S': 
            return Direction::DOWN;
        case 'a': case 'A': 
            return Direction::LEFT;
        case 'd': case 'D': 
            return Direction::RIGHT;
        case 27: // Escape sequence for arrow keys on Unix
            {
                char seq1 = getInput(); // consume '['
                if (seq1 == '[') {
                    char seq2 = getInput();
                    switch (seq2) {
                        case 'A': return Direction::UP;
                        case 'B': return Direction::DOWN;
                        case 'C': return Direction::RIGHT;
                        case 'D': return Direction::LEFT;
                    }
                }
            }
            break;
#ifdef _WIN32
        case 72: // Arrow up on Windows
            return Direction::UP;
        case 80: // Arrow down on Windows
            return Direction::DOWN;
        case 75: // Arrow left on Windows
            return Direction::LEFT;
        case 77: // Arrow right on Windows
            return Direction::RIGHT;
#endif
    }
    return Direction::UP; // Default fallback, won't be used if input is invalid
}

void CLIRenderer::setupTerminal() {
#ifdef _WIN32
    // Windows console setup
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    // Unix/Linux terminal setup
    tcgetattr(STDIN_FILENO, &originalTermios);
    terminalModified = true;
    
    struct termios newTermios = originalTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    newTermios.c_cc[VMIN] = 0;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    
    // Make stdin non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
#endif
}

void CLIRenderer::restoreTerminal() {
#ifndef _WIN32
    if (terminalModified) {
        tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
        terminalModified = false;
    }
#endif
}

void CLIRenderer::hideCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    std::cout << "\033[?25l" << std::flush;
#endif
}

void CLIRenderer::showCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    std::cout << "\033[?25h" << std::flush;
#endif
}

void CLIRenderer::moveCursor(int x, int y) {
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H" << std::flush;
#endif
}