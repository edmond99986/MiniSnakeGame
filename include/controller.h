#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stack>
#include "snake.h"

class Controller {
public:
    void HandleInput(bool &running, Snake &snake) const;
    void Undo(bool &running, bool& undone, std::stack<Snake>&, Snake& snake) const;

private:
    void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif