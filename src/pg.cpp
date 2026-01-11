#include "pg.h"

pg::pg( pxcount px, int posx, int posy) {
    character.setFillColor({0, 0, 100});
    if (px.getPxHeight()<px.getPxWidth()) {
        r=px.getPxHeight()*0.375;
    }else {
        r=px.getPxWidth()*0.375;
    }
    offsetX=px.getPxWidth()/2-r-2;  // il -2 serve alltrimenti non è perfettamente centrato sul mio monitor, fare prove
    offsetY=px.getPxHeight()/2-r-2; // per vedere se viene centratro con altri valori
    character.setRadius(r);
    x=posx;
    y=posy;
    float pxX = posx*px.getPxWidth()+offsetX;
    float pxY = posy*px.getPxHeight()+offsetY;
    character.setPosition({pxX, pxY});
}

void pg::setOffsetRad(pxcount px) {
    if (px.getPxHeight()<px.getPxWidth()) {
        r=px.getPxHeight()*0.375;
    }else {
        r=px.getPxWidth()*0.375;
    }
    offsetX=px.getPxWidth()/2-r-2;
    offsetY=px.getPxHeight()/2-r-2;
    character.setRadius(r);
    float pxX = character.getPosition().x*px.getPxWidth()+offsetX;
    float pxY = character.getPosition().y*px.getPxHeight()+offsetY;
    character.setPosition({pxX, pxY});
}

void pg::move(pxcount px, int targetx, int targety) {
    float charx = floor(character.getPosition().x);
    float chary = floor(character.getPosition().y);
    targetx=floor(targetx*px.getPxWidth()+offsetX);
    targety=floor(targety*px.getPxHeight()+offsetY);
    float moveX = 0;
    float moveY = 0;
    moveX = (charx < targetx) ? 1 : (charx > targetx) ? -1 : 0;
    if (moveX==0) {
        moveY = (chary < targety) ? 1 : (chary > targety) ? -1 : 0;
    }
    character.move({moveX, moveY});
}
float pg::getOffsetX() {
    return offsetX;
}
float pg::getOffsetY() {
    return offsetY;
}
void pg::setPosition(pxcount px, int posx, int posy) {
    x=posx;
    y=posy;
}
void pg::setPixel(pxcount px) {
    float pxX = x*px.getPxWidth()+offsetX;
    float pxY = y*px.getPxHeight()+offsetY;
    character.setPosition({pxX, pxY});
}