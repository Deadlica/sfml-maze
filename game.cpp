#include "game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Maze"), maze(window.getSize(), 67, 37) {

}

bool Game::is_running() const {
    return window.isOpen();
}

void Game::update() {
    poll_events();
    maze.update();
}

void Game::poll_events() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::W:
                    //Move up
                    maze.move_player(sf::Keyboard::W);
                    break;
                case sf::Keyboard::A:
                    //Move left
                    maze.move_player(sf::Keyboard::A);
                    break;
                case sf::Keyboard::S:
                    //Move down
                    maze.move_player(sf::Keyboard::S);
                    break;
                case sf::Keyboard::D:
                    //Move right
                    maze.move_player(sf::Keyboard::D);
                    break;
            }
        }
    }
}

void Game::render() {
    maze.draw(window);
    window.display();
}