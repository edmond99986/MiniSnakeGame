#ifndef ROAD_BLOCK_NODE_H
#define ROAD_BLOCK_NODE_H

class RoadBlockNode {
public:
    int count{0};
    int left, right;
    int floor, ceiling;

    RoadBlockNode* upper_left{nullptr};
    RoadBlockNode* upper_right{nullptr};
    RoadBlockNode* lower_left{nullptr};
    RoadBlockNode* lower_right{nullptr};

    void UpdateCount();

    RoadBlockNode(int grid_width, int grid_height);

    RoadBlockNode(int left, int right, int floor, int ceiling):
            left(left),
            right(right),
            floor(floor),
            ceiling(ceiling) {}
};

#endif