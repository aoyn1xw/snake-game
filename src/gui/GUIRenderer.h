#pragma once

#include "../game/SnakeGame.h"

#ifdef ENABLE_GUI
#include <SFML/Graphics.hpp>
#endif

class GUIRenderer : public Renderer {
public:
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int CELL_SIZE = 20;
    
    GUIRenderer();
    ~GUIRenderer();
    
    bool initialize();
    void render(const SnakeGame& game) override;
    void clear() override;
    void showGameOver(int score) override;
    
    // Input handling
    Direction getCurrentDirection() const { return lastDirection; }
    bool shouldQuit() const { return quit; }
    bool isWindowOpen() const;
    void pollEvents();
    
private:
#ifdef ENABLE_GUI
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::RectangleShape snakeSegment;
    sf::CircleShape foodShape;
#endif
    bool quit;
    bool initialized;
    Direction lastDirection;
    
    void drawSnake(const std::vector<Position>& snake);
    void drawFood(const Position& food);
    void drawScore(int score);
};