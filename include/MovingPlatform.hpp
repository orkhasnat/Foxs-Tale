#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "Platform.hpp"

class MovingPlatform : public Platform
{
private:
    bool lr; // Direction of movement- 0 for left and 1 for right
    inline void change_direction()
    {
        lr = !lr;
    }

public:
    MovingPlatform(int, const ItemType);
    void move();
};

#endif