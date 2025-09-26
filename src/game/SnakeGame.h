#pragma once

#include <vector>
#include <random>
#include <chrono>

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Position {
    int x, y;
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class SnakeGame {
public:
    static constexpr int BOARD_WIDTH = 40;
    static constexpr int BOARD_HEIGHT = 20;
    
    SnakeGame();
    void reset();
    bool update();
    bool isGameOver() const { return gameOver; }
    int getScore() const { return score; }
    
    void setDirection(Direction newDirection);
    Direction getCurrentDirection() const { return currentDirection; }
    
    const std::vector<Position>& getSnakeBody() const { return snake; }
    const Position& getFoodPosition() const { return food; }
    
    int getBoardWidth() const { return BOARD_WIDTH; }
    int getBoardHeight() const { return BOARD_HEIGHT; }
    
private:
    std::vector<Position> snake;
    Position food;
    Direction currentDirection;
    Direction nextDirection;
    bool gameOver;
    int score;
    
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;
    
    void generateFood();
    bool isFoodOnSnake() const;
    void moveSnake();
    bool checkCollision() const;
    Position getNextHeadPosition() const;
};

// Abstract base class for renderers
class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const SnakeGame& game) = 0;
    virtual void clear() = 0;
    virtual void showGameOver(int score) = 0;
};