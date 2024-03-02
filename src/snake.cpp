#include "snake.h"
#include <cmath>

void Snake::Update()
{
    SDL_Point prev_cell{
            static_cast<int>(head_x),
            static_cast<int>(
                    head_y)};
    UpdateHead();
    SDL_Point current_cell{
            static_cast<int>(head_x),
            static_cast<int>(head_y)};

    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
        UpdateBody(current_cell, prev_cell);
}

void Snake::UpdateHead()
{
    switch (direction)
    {
        case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;

        case Direction::kLeft:
            head_x -= speed;
            break;

        case Direction::kRight:
            head_x += speed;
            break;
    }

    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
    // TO-DO: Insert new cells to the linked list
	// Please insert your code here.
    if (head==nullptr)
    {head=tail=new SnakeBodySegment(prev_head_cell);
    }
    else if (head!= nullptr&& tail!= nullptr)
    {
        tail->next=new SnakeBodySegment(prev_head_cell);
        tail=tail->next;
    }

    if (!growing)
    {
        SnakeBodySegment *tmp = head;
        if (tmp != nullptr)
        {
            if (head == tail)
                head = tail = head->next;
            else
                head = head->next;

            delete tmp;
        }
    } else {
        growing = false;
        size++;
    }

    for (SnakeBodySegment *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->point.x == current_head_cell.x && ptr->point.y == current_head_cell.y)
            alive = false;
    }
}

void Snake::GrowBody() { growing = true; }


bool Snake::SnakeCell(int x, int y)
{
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
        return true;

    for (SnakeBodySegment *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        if (x == ptr->point.x && y == ptr->point.y)
            return true;
    }
    return false;
}

Snake::Snake(const Snake &other)
{
    speed = other.speed;
    alive = other.alive;
    size = other.size;
    head_x = other.head_x;
    head_y = other.head_y;
    direction = other.direction;
    growing = other.growing;
    grid_width = other.grid_width;
    grid_height = other.grid_height;

    head = tail = nullptr;

    if (other.head == nullptr)
        return;

    head = tail = new SnakeBodySegment(other.head->point);
    for (SnakeBodySegment *ptr = other.head->next; ptr != nullptr; ptr = ptr->next)
    {
        tail->next = new SnakeBodySegment(ptr->point);
        tail = tail->next;
    }
}

Snake::~Snake()
{
    SnakeBodySegment *prev = nullptr;
    for (SnakeBodySegment *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        if (prev != nullptr)
            delete prev;

        prev = ptr;
    }
    if (prev != nullptr)
        delete prev;
}

Snake &Snake::operator = (const Snake &other)
{
    speed = other.speed;
    alive = other.alive;
    size = other.size;
    head_x = other.head_x;
    head_y = other.head_y;
    direction = other.direction;
    growing = other.growing;
    grid_width = other.grid_width;
    grid_height = other.grid_height;

    SnakeBodySegment *prev = nullptr;
    for (SnakeBodySegment *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        if (prev != nullptr)
            delete prev;

        prev = ptr;
    }

    if (prev != nullptr)
        delete prev;
    head = tail = nullptr;

    if (other.head == nullptr)
        return *this;

    head = tail = new SnakeBodySegment(other.head->point);
    for (SnakeBodySegment *ptr = other.head->next; ptr != nullptr; ptr = ptr->next)
    {
        tail->next = new SnakeBodySegment(ptr->point);
        tail = tail->next;
    }

    return *this;
}