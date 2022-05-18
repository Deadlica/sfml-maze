#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "maze.h"

class Game {
public:
    Game(const unsigned int width = 800, const unsigned int height = 600);

    bool is_running() const;
    void update();
    void render();


private:
    void poll_events();
    sf::RenderWindow window;
    Maze maze;

    int width, height;

};

#endif