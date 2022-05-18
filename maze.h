#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <stack>
#include <stdlib.h>

class Maze {
public:
    Maze(sf::Vector2u window_size, const unsigned int columns = 11, const unsigned int rows = 11);
    void draw(sf::RenderWindow &window);
    void update();
    void move_player(sf::Keyboard::Key key);


private:

    void generate_paths();
    std::vector<std::pair<int, int>> get_neighbours(std::pair<int, int> cell);
    void open_path(std::pair<int, int> current_cell, std::pair<int, int> neighbour_cell);
    std::pair<int, int> start_cell();

    struct cell {
        cell();
        bool visited;
        sf::Sprite graphic;
        double x, y;
    };
    
    sf::Texture wall, path, sans;
    sf::Sprite player;
    int max_width, max_height;

    std::vector<std::vector<cell>> maze;
};

#endif