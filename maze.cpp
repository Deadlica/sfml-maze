#include "maze.h"
#include <SFML/Window/Keyboard.hpp>
#include <vector>

Maze::Maze(sf::Vector2u window_size, const unsigned int columns, const unsigned int rows):
maze(rows, std::vector<cell>(columns, cell())){
    wall.loadFromFile("textures/wall.jpg");
    path.loadFromFile("textures/path.jpg");
    sans.loadFromFile("textures/player.png");
    player.setTexture(sans);
    player.scale(0.06, 0.06);

    max_width = window_size.x / wall.getSize().x;
    max_height = window_size.y / wall.getSize().y;

    for(int y = 0; y < maze.size(); y++) {
        for(int x = 0; x < maze[y].size(); x++) {
            maze[y][x].graphic.setTexture(wall);
            maze[y][x].graphic.scale(0.25, 0.25);
            maze[y][x].x = wall.getSize().x * maze[y][x].graphic.getScale().x * x;
            maze[y][x].y = wall.getSize().y * maze[y][x].graphic.getScale().y * y;
        }
    }
    generate_paths();
    player.setPosition(maze[1][1].x, maze[1][1].y);
}

void Maze::draw(sf::RenderWindow &window) {
    for(auto &row : maze) {
        for(auto &cell : row) {
            window.draw(cell.graphic);
        }
    }
    window.draw(player);
}

void Maze::update() {
    for(auto &row : maze) {
        for(auto &cell : row) {
            cell.graphic.setPosition(cell.x, cell.y);
        }
    }
}

void Maze::move_player(sf::Keyboard::Key key) {
    auto width = wall.getSize().x * maze[1][1].graphic.getScale().x;
    auto height = wall.getSize().y * maze[1][1].graphic.getScale().y;
    switch(key) {
        case sf::Keyboard::W:
            player.setPosition(player.getPosition().x, player.getPosition().y - height);
            break;
        case sf::Keyboard::A:
            player.setPosition(player.getPosition().x - width, player.getPosition().y);
            break;
        case sf::Keyboard::S:
            player.setPosition(player.getPosition().x, player.getPosition().y + height);
            break;
        case sf::Keyboard::D:
            player.setPosition(player.getPosition().x + width, player.getPosition().y);
            break;
    }
}

void Maze::generate_paths() {
    std::stack<std::pair<int, int>> cells;
    std::vector<std::pair<int, int>> neighbours;
    auto cell = start_cell();
    maze[cell.second][cell.first].visited = true;
    maze[cell.second][cell.first].graphic.setTexture(path);
    cells.push(cell);
    while(!cells.empty()) {
        cell = cells.top();
        cells.pop();
        maze[cell.second][cell.first].visited = true;
        maze[cell.second][cell.first].graphic.setTexture(path);

        neighbours = get_neighbours(cell);

        if(!neighbours.empty()) {
            cells.push(cell);
            cell = neighbours[std::rand() % neighbours.size()];
            open_path(cells.top(), cell);
            cells.push(cell);
        }
    }
}

void Maze::open_path(std::pair<int, int> current_cell, std::pair<int, int> neighbour_cell) {
    if(current_cell.first < neighbour_cell.first) { //Right path
        maze[current_cell.second][current_cell.first + 1].visited = true;
        maze[current_cell.second][current_cell.first + 1].graphic.setTexture(path);
    }
    else if(current_cell.first > neighbour_cell.first) { //Left path
        maze[current_cell.second][current_cell.first - 1].visited = true;
        maze[current_cell.second][current_cell.first -1].graphic.setTexture(path);
    }
    else if(current_cell.second < neighbour_cell.second) { //Down path
        maze[current_cell.second + 1][current_cell.first].visited = true;
        maze[current_cell.second + 1][current_cell.first].graphic.setTexture(path);
    }
    else { //Up path
        maze[current_cell.second - 1][current_cell.first].visited = true;
        maze[current_cell.second - 1][current_cell.first].graphic.setTexture(path);
    }
}

std::vector<std::pair<int, int>> Maze::get_neighbours(std::pair<int, int> cell) {
    std::vector<std::pair<int, int>> neighbours;
    if(cell.first + 2 < maze[cell.second].size() - 1 && !maze[cell.second][cell.first + 2].visited) { //Right neighbour
        neighbours.push_back({cell.first + 2, cell.second});
    }
    if(cell.first - 2 > 0 && !maze[cell.second][cell.first - 2].visited) { //Left neighbour
        neighbours.push_back({cell.first - 2, cell.second});
    }
    if(cell.second + 2 < maze.size() - 1 && !maze[cell.second + 2][cell.first].visited) { //Down neighbour
        neighbours.push_back({cell.first, cell.second + 2});
    }
    if(cell.second - 2 > 0 && !maze[cell.second - 2][cell.first].visited) { //Up neighbour
        neighbours.push_back({cell.first, cell.second - 2});
    }

    return neighbours;
}

std::pair<int, int> Maze::start_cell() {
    int x_pos = std::rand() % (maze.size() - 2) + 1;
    int y_pos = std::rand() % (maze.size() - 2) + 1;
    if(x_pos % 2 == 0) x_pos += 1;
    if(y_pos % 2 == 0) y_pos += 1;

    return {x_pos, y_pos};
}

Maze::cell::cell():
visited(false), graphic(), x(0), y(0) {}