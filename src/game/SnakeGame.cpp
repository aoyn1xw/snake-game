#include "SnakeGame.h"
#include <algorithm>

SnakeGame::SnakeGame() 
    : currentDirection(Direction::RIGHT)
    , nextDirection(Direction::RIGHT)
    , gameOver(false)
    , score(0)
    , rng(std::chrono::steady_clock::now().time_since_epoch().count())
    , xDist(0, BOARD_WIDTH - 1)
    , yDist(0, BOARD_HEIGHT - 1)
{
    reset();
}

void SnakeGame::reset() {
    snake.clear();
    snake.push_back(Position(BOARD_WIDTH / 2, BOARD_HEIGHT / 2));
    snake.push_back(Position(BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2));
    snake.push_back(Position(BOARD_WIDTH / 2 - 2, BOARD_HEIGHT / 2));
    
    currentDirection = Direction::RIGHT;
    nextDirection = Direction::RIGHT;
    gameOver = false;
    score = 0;
    
    generateFood();
}

bool SnakeGame::update() {
    if (gameOver) {
        return false;
    }
    
    currentDirection = nextDirection;
    moveSnake();
    
    if (checkCollision()) {
        gameOver = true;
        return false;
    }
    
    // Check if food is eaten
    if (snake[0] == food) {
        score += 10;
        generateFood();
        // Don't remove tail - snake grows
    } else {
        // Remove tail - normal movement
        snake.pop_back();
    }
    
    return true;
}

void SnakeGame::setDirection(Direction newDirection) {
    // Prevent reversing into itself
    if ((currentDirection == Direction::UP && newDirection == Direction::DOWN) ||
        (currentDirection == Direction::DOWN && newDirection == Direction::UP) ||
        (currentDirection == Direction::LEFT && newDirection == Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && newDirection == Direction::LEFT)) {
        return;
    }
    
    nextDirection = newDirection;
}

void SnakeGame::generateFood() {
    do {
        food.x = xDist(rng);
        food.y = yDist(rng);
    } while (isFoodOnSnake());
}

bool SnakeGame::isFoodOnSnake() const {
    return std::find(snake.begin(), snake.end(), food) != snake.end();
}

void SnakeGame::moveSnake() {
    Position newHead = getNextHeadPosition();
    snake.insert(snake.begin(), newHead);
}

bool SnakeGame::checkCollision() const {
    const Position& head = snake[0];
    
    // Wall collision
    if (head.x < 0 || head.x >= BOARD_WIDTH || head.y < 0 || head.y >= BOARD_HEIGHT) {
        return true;
    }
    
    // Self collision (check against body, starting from index 1)
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head == snake[i]) {
            return true;
        }
    }
    
    return false;
}

Position SnakeGame::getNextHeadPosition() const {
    Position head = snake[0];
    
    switch (currentDirection) {
        case Direction::UP:    head.y--; break;
        case Direction::DOWN:  head.y++; break;
        case Direction::LEFT:  head.x--; break;
        case Direction::RIGHT: head.x++; break;
    }
    
    return head;
}