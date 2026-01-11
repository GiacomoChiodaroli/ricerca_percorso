#ifndef PG_H
#define PG_H
#include <SFML/Graphics.hpp>
#include "pxcount.h"
#include <iostream>
#include <math.h>
class pg {
private:
    float offsetX;
    float offsetY;
    float r;
    int x,y;
public:
    sf::CircleShape character;
    pg(pxcount px, int posx, int posy);
    ~pg()=default;
    void setOffsetRad(pxcount px);
    void move(pxcount px, int targetx, int targety);
    float getOffsetX();
    float getOffsetY();
    void setPosition(pxcount px, int posx, int posy);
    void setPixel(pxcount px);

};



#endif //PG_H
