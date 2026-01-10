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
    float pxX = x*px.getPxWidth()+offsetX;
    float pxY = y*px.getPxHeight()+offsetY;
    character.setPosition({pxX, pxY});
}

void pg::move(pxcount px, int targetx, int targety) {
    int charx = character.getPosition().x;
    int chary = character.getPosition().y;
    targetx=targetx*px.getPxWidth()+offsetX;
    targety=targety*px.getPxHeight()+offsetY;
    float moveX = 0;
    float moveY = 0;
    moveX = (charx < targetx) ? 1 : (charx > targetx) ? -1 : 0;
    if (moveX==0) {
        moveY = (chary < targety) ? 1 : (chary > targety) ? -1 : 0;
    }
    character.move({moveX, moveY});
    std::cout<<"x char: "<<character.getPosition().x<< ", y char: "<< character.getPosition().y<<std::endl;
}
void pg::setPosition(pxcount px, float newx, float newy) {
    x=newx/px.getPxWidth();
    y=newy/px.getPxHeight();
}

