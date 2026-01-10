#ifndef PG_H
#define PG_H
#include <SFML/Graphics.hpp>
#include "pxcount.h"
#include <iostream>
class pg {
public:
    float offsetX;
    float offsetY;
    float r;
    int x;
    int y;
    sf::CircleShape character;
    pg(pxcount px, int posx, int posy);
    ~pg()=default;
    void setOffsetRad(pxcount px);
    void move(pxcount px, int targetx, int targety);
    void setPosition(pxcount px, float newx, float newy);


};



#endif //PG_H
