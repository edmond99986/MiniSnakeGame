#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
: grid_width(grid_width),
grid_height(grid_height),
screen_width(screen_width),
screen_height(screen_height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, RoadBlockNode *root)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Rendering of the food block
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xE7, 0x7A, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// TO-DO: Render the snake body
	// Please insert your code here.
    for(SnakeBodySegment*ptr =snake.head;ptr!= nullptr;ptr=ptr->next){
        block.x = ptr->point.x * block.w;
        block.y = ptr->point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    RenderBlock(root, &block);

    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::RenderBlock(RoadBlockNode *root, SDL_Rect *block)
{
    if (root == nullptr || root->count == 0)
        return;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1)
    {
        block->x = root->left * block->w;
        block->y = root->floor * block->h;

        SDL_SetRenderDrawColor(sdl_renderer, 0x2C, 0x5F, 0x2D, 0xFF);
        SDL_RenderFillRect(sdl_renderer, block);
        return;
    }

    RenderBlock(root->lower_left, block);
    RenderBlock(root->lower_right, block);
    RenderBlock(root->upper_left, block);
    RenderBlock(root->upper_right, block);
}
