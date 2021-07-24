#include "MovingPlatform.hpp"

MovingPlatform::MovingPlatform(int x, const ItemType _itemtype) : Platform(x, _itemtype), lr(rand() & 1)
{
    platformtype = moving;
}

void MovingPlatform::move()
{
    if (lr && sprite.getPosition().x + width + 10 > 1180)
        change_direction();
    else if (!lr && sprite.getPosition().x - 10 < 820)
        change_direction();

    sprite.move(20 * lr - 10, -20);
    if (item)
        item->sprite.move(20 * lr - 10, -20);
}