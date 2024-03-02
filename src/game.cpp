#include "game.h"
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int init_num_blocks)
: engine(dev()),
  snake(grid_width, grid_height),
  random_w(0, static_cast<int>(grid_width - 1)),
  random_h(0, static_cast<int>(grid_height - 1))
{
    road_blocks = new RoadBlockNode(grid_width, grid_height);
    for (int i = 0; i < init_num_blocks; i++)
        PlaceBlock();

    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;
    bool undone = false;

    while (running)
    {
        frame_start = SDL_GetTicks();

        if (!snake.alive)
        {
            controller.Undo(running, undone, states, snake);
            if (snake.alive)
            {
                for (SnakeBodySegment* ptr = snake.head; ptr != nullptr; ptr = ptr->next)
                    DeleteBlock(road_blocks, ptr->point.x, ptr->point.y);

                for (int i = 0; i < 5; i++)
                    PlaceBlock();

            PlaceFood();
            }
            renderer.Render(snake, food, road_blocks);
        } else {
            controller.HandleInput(running, snake);
            Update();
            renderer.Render(snake, food, road_blocks);
        }

        int head_x = static_cast<int>(snake.head_x);
        int head_y = static_cast<int>(snake.head_y);

        if (DetectCollision(road_blocks, head_x, head_y))
        {
            snake.alive = false;
            DeleteBlock(road_blocks, head_x, head_y);
        }

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= 1000)
        {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        if (frame_duration < target_frame_duration)
            SDL_Delay(target_frame_duration - frame_duration);
    }
}

void Game::PlaceFood()
{
    int x, y;
    for (;;)
    {
        x = random_w(engine);
        y = random_h(engine);

        if (!snake.SnakeCell(x, y) && !DetectCollision(road_blocks, x, y))
        {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::PlaceBlock() {
    int x, y;
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);

        int snake_head_x = static_cast<int>(snake.head_x);
        int snake_head_y = static_cast<int>(snake.head_y);
        if (!snake.SnakeCell(x, y) && !DetectCollision(road_blocks, x, y)
        && abs(x - snake_head_x) > 2 && abs(y - snake_head_y) > 2)
        {
            InsertBlock(road_blocks, x, y);
            return;
        }
    }
}

void Game::Update()
{
    if (!snake.alive) return;
    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    score = snake.size;
    if (food.x == new_x && food.y == new_y)
    {
        PlaceFood();
        snake.GrowBody();
        snake.speed += acceleration;

        auto tmp = snake;
		// TO-DO: Push the snake copy into the stack
		// Please insert your code here.
        tmp.alive= false;
        states.push(tmp);
    }
}


void Game::InsertBlock(RoadBlockNode* root, int x, int y)
{
    if (root == nullptr)
        return;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1)
    {
        root->count = 1;
        return;
    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
    {
        if (root->upper_left == nullptr)
            root->upper_left = new RoadBlockNode(root->left, mid_x, root->floor, mid_y);
        InsertBlock(root->upper_left, x, y);
    }

    if (x < mid_x && y >= mid_y)
    {
        if (root->lower_left == nullptr)
            root->lower_left = new RoadBlockNode(root->left, mid_x, mid_y, root->ceiling);
        InsertBlock(root->lower_left, x, y);
    }

    if (x >= mid_x && y < mid_y)
    {
        if (root->upper_right == nullptr)
            root->upper_right = new RoadBlockNode(mid_x, root->right, root->floor, mid_y);
        InsertBlock(root->upper_right, x, y);
    }

    if (x >= mid_x && y >= mid_y)
    {
        if (root->lower_right == nullptr)
            root->lower_right = new RoadBlockNode(mid_x, root->right, mid_y, root->ceiling);
        InsertBlock(root->lower_right, x, y);
    }

    root->UpdateCount();
}


void Game::DeleteBlock(RoadBlockNode* root, int x, int y)
{
    if (root == nullptr || root->count == 0)
        return;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1) {
        root->count =0;
        return;
    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
        DeleteBlock(root->upper_left, x, y);

    if (x < mid_x && y >= mid_y)
        DeleteBlock(root->lower_left, x, y);

    if (x >= mid_x && y < mid_y)
        DeleteBlock(root->upper_right, x, y);

    if (x >= mid_x && y >= mid_y)
        DeleteBlock(root->lower_right, x, y);

    root->UpdateCount();
}


bool Game::DetectCollision(RoadBlockNode* root, int x, int y)
{
	// TO-DO: Collision Detection
	// Please insert your code here.
    if (root == nullptr|| root->count == 0 )
        return false;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1)
    {

        return true;

    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
        return DetectCollision(root->upper_left, x, y);

    if (x < mid_x && y >= mid_y)
        return DetectCollision(root->lower_left, x, y);

    if (x >= mid_x && y < mid_y)
       return DetectCollision(root->upper_right, x, y);

    if (x >= mid_x && y >= mid_y)
       return DetectCollision(root->lower_right, x, y);




    return false;
}


int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }