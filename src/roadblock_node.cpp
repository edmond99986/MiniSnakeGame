#include "roadblock_node.h"


RoadBlockNode::RoadBlockNode(int grid_width, int grid_height)
{
    left = floor = 0;
    right = grid_width;
    ceiling = grid_height;
}

void RoadBlockNode::UpdateCount()
{
    count = 0;
    if (upper_left != nullptr)
        count += upper_left->count;
    if (lower_left != nullptr)
        count += lower_left->count;
    if (upper_right != nullptr)
        count += upper_right->count;
    if (lower_right != nullptr)
        count += lower_right->count;
}