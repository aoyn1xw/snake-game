#include "GUIRenderer.h"
#include <iostream>
#include <sstream>

GUIRenderer::GUIRenderer() 
#ifdef ENABLE_GUI
    : scoreText()
    , gameOverText()
    , quit(false)
    , initialized(false)
    , lastDirection(Direction::RIGHT)
#else
    : quit(false)
    , initialized(false)
    , lastDirection(Direction::RIGHT)
#endif
{
}

GUIRenderer::~GUIRenderer() {
#ifdef ENABLE_GUI
    if (window.isOpen()) {
        window.close();
    }
#endif
}

bool GUIRenderer::initialize() {
#ifdef ENABLE_GUI
    // Create window - handle both SFML 2.x and 3.x
#if SFML_VERSION_MAJOR >= 3
    window.create(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Snake Game");
#else
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
#endif
    window.setFramerateLimit(60);
    
    // Load font - try to use a default system font (handle both SFML 2.x and 3.x)
#if SFML_VERSION_MAJOR >= 3
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.openFromFile("/System/Library/Fonts/Arial.ttf")) {
            if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                // Create a minimal font if no system font is found
                std::cerr << "Warning: Could not load system font, using default font\n";
                // SFML will use default font
            }
        }
    }
#else
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.loadFromFile("/System/Library/Fonts/Arial.ttf")) {
            if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                // Create a minimal font if no system font is found
                std::cerr << "Warning: Could not load system font, using default font\n";
                // SFML will use default font
            }
        }
    }
#endif
    
    // Setup text objects
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10, 10));
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50));
    
    // Setup shapes
    snakeSegment.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    snakeSegment.setFillColor(sf::Color::Green);
    
    foodShape.setRadius(CELL_SIZE / 2 - 1);
    foodShape.setFillColor(sf::Color::Red);
    
    initialized = true;
    return true;
#else
    std::cerr << "GUI mode not available - SFML not found during compilation\n";
    return false;
#endif
}

void GUIRenderer::render(const SnakeGame& game) {
#ifdef ENABLE_GUI
    if (!initialized || !window.isOpen()) {
        return;
    }
    
    window.clear(sf::Color::Black);
    
    // Draw game elements
    drawSnake(game.getSnakeBody());
    drawFood(game.getFoodPosition());
    drawScore(game.getScore());
    
    window.display();
#endif
}

void GUIRenderer::clear() {
#ifdef ENABLE_GUI
    if (initialized && window.isOpen()) {
        window.clear(sf::Color::Black);
    }
#endif
}

void GUIRenderer::showGameOver(int score) {
#ifdef ENABLE_GUI
    if (!initialized || !window.isOpen()) {
        return;
    }
    
    std::ostringstream oss;
    oss << "Game Over! Score: " << score << "\nPress ESC to return to menu";
    gameOverText.setString(oss.str());
    
    window.clear(sf::Color::Black);
    window.draw(gameOverText);
    window.display();
#endif
}

bool GUIRenderer::isWindowOpen() const {
#ifdef ENABLE_GUI
    return initialized && window.isOpen();
#else
    return false;
#endif
}

void GUIRenderer::pollEvents() {
#ifdef ENABLE_GUI
    if (!initialized || !window.isOpen()) {
        return;
    }
    
#if SFML_VERSION_MAJOR >= 3
    // SFML 3.x event handling
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            quit = true;
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    lastDirection = Direction::UP;
                    break;
                case sf::Keyboard::Key::Down:
                    lastDirection = Direction::DOWN;
                    break;
                case sf::Keyboard::Key::Left:
                    lastDirection = Direction::LEFT;
                    break;
                case sf::Keyboard::Key::Right:
                    lastDirection = Direction::RIGHT;
                    break;
                case sf::Keyboard::Key::Escape:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }
#else
    // SFML 2.x event handling
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            quit = true;
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    lastDirection = Direction::UP;
                    break;
                case sf::Keyboard::Down:
                    lastDirection = Direction::DOWN;
                    break;
                case sf::Keyboard::Left:
                    lastDirection = Direction::LEFT;
                    break;
                case sf::Keyboard::Right:
                    lastDirection = Direction::RIGHT;
                    break;
                case sf::Keyboard::Escape:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }
#endif
#endif
}

void GUIRenderer::drawSnake(const std::vector<Position>& snake) {
#ifdef ENABLE_GUI
    if (!initialized) return;
    
    for (const auto& segment : snake) {
        snakeSegment.setPosition(sf::Vector2f(
            segment.x * CELL_SIZE + (WINDOW_WIDTH - SnakeGame::BOARD_WIDTH * CELL_SIZE) / 2,
            segment.y * CELL_SIZE + (WINDOW_HEIGHT - SnakeGame::BOARD_HEIGHT * CELL_SIZE) / 2
        ));
        window.draw(snakeSegment);
    }
#endif
}

void GUIRenderer::drawFood(const Position& food) {
#ifdef ENABLE_GUI
    if (!initialized) return;
    
    foodShape.setPosition(sf::Vector2f(
        food.x * CELL_SIZE + (WINDOW_WIDTH - SnakeGame::BOARD_WIDTH * CELL_SIZE) / 2,
        food.y * CELL_SIZE + (WINDOW_HEIGHT - SnakeGame::BOARD_HEIGHT * CELL_SIZE) / 2
    ));
    window.draw(foodShape);
#endif
}

void GUIRenderer::drawScore(int score) {
#ifdef ENABLE_GUI
    if (!initialized) return;
    
    std::ostringstream oss;
    oss << "Score: " << score;
    scoreText.setString(oss.str());
    window.draw(scoreText);
#endif
}