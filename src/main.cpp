#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

#include "game/SnakeGame.h"
#include "cli/CLIRenderer.h"
#include "gui/GUIRenderer.h"

void showMainMenu() {
    std::cout << "================================\n";
    std::cout << "       SNAKE GAME SELECTOR\n";
    std::cout << "================================\n";
    std::cout << "[1] Play in Terminal (CLI)\n";
    std::cout << "[2] Play with Graphics (GUI)\n";
    std::cout << "[3] Quit\n";
    std::cout << "Enter choice (1-3): ";
}

int getMenuChoice() {
    int choice;
    if (std::cin >> choice) {
        std::cin.ignore(10000, '\n'); // Clear the rest of the line
        if (choice >= 1 && choice <= 3) {
            return choice;
        }
    } else {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(10000, '\n'); // Clear the rest of the line
    }
    
    return -1;
}

void runCLIMode() {
    std::cout << "Starting CLI mode...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    SnakeGame game;
    CLIRenderer renderer;
    
    renderer.clear();
    
    auto lastUpdate = std::chrono::steady_clock::now();
    const auto updateInterval = std::chrono::milliseconds(100); // 10 FPS
    
    bool quit = false;
    
    while (!quit && !game.isGameOver()) {
        auto now = std::chrono::steady_clock::now();
        
        // Handle input
        if (renderer.hasInput()) {
            char input = renderer.getInput();
            if (input == 'q' || input == 'Q' || input == 27) { // 'q' or ESC
                quit = true;
                break;
            } else {
                Direction dir = renderer.getDirectionFromInput(input);
                game.setDirection(dir);
            }
        }
        
        // Update game at fixed intervals
        if (now - lastUpdate >= updateInterval) {
            game.update();
            renderer.render(game);
            lastUpdate = now;
        }
        
        // Small sleep to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    if (game.isGameOver()) {
        renderer.showGameOver(game.getScore());
        std::cin.get(); // Wait for any key
    }
    
    renderer.clear();
}

void runGUIMode() {
    std::cout << "Starting GUI mode...\n";
    
    GUIRenderer renderer;
    
    if (!renderer.initialize()) {
        std::cout << "Failed to initialize GUI mode. SFML might not be available.\n";
        std::cout << "Press Enter to return to menu...";
        std::cin.get();
        return;
    }
    
    SnakeGame game;
    
    auto lastUpdate = std::chrono::steady_clock::now();
    const auto updateInterval = std::chrono::milliseconds(150); // ~6.7 FPS for gameplay
    
    Direction lastDirection = game.getCurrentDirection();
    
    while (renderer.isWindowOpen() && !renderer.shouldQuit()) {
        auto now = std::chrono::steady_clock::now();
        
        // Handle events and get direction input
        renderer.pollEvents();
        
        if (renderer.shouldQuit()) {
            break;
        }
        
        // Check if direction changed and update game
        Direction currentDirection = renderer.getCurrentDirection();
        if (currentDirection != lastDirection) {
            game.setDirection(currentDirection);
            lastDirection = currentDirection;
        }
        
        // Update game at fixed intervals
        if (now - lastUpdate >= updateInterval) {
            if (!game.isGameOver()) {
                game.update();
            }
            
            renderer.render(game);
            lastUpdate = now;
        }
        
        if (game.isGameOver()) {
            renderer.showGameOver(game.getScore());
            
            // Wait for ESC key to exit
            while (renderer.isWindowOpen() && !renderer.shouldQuit()) {
                renderer.pollEvents();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            break;
        }
        
        // Small sleep to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS for rendering
    }
}

int main() {
    std::cout << "Welcome to the Snake Game!\n\n";
    
    while (true) {
        showMainMenu();
        
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                runCLIMode();
                break;
                
            case 2:
                runGUIMode();
                break;
                
            case 3:
                std::cout << "Thanks for playing! Goodbye!\n";
                return 0;
                
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n\n";
                break;
        }
        
        std::cout << "\n";
    }
    
    return 0;
}