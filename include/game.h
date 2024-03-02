#ifndef GAME_H
#define GAME_H

#include <random>
#include <stack>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "roadblock_node.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height, int init_num_blocks);

    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);

    int GetScore() const;

    int GetSize() const;

private:
    Snake snake;
    SDL_Point food;
    float acceleration{0.012};

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    std::stack<Snake> states;

    int score{0};

    void PlaceFood();

    void PlaceBlock();

    void Update();

    void InsertBlock(RoadBlockNode *, int, int);

    void DeleteBlock(RoadBlockNode *, int, int);

    bool DetectCollision(RoadBlockNode *, int, int);

    RoadBlockNode *road_blocks;
};

#endif