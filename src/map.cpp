#include "map.h"

#include <iostream>

map::map(int x, int y) {
    srand(time(0));
    mappa.resize(x, std::vector<int>(y));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            mappa[i][j] = (rand() % 5)+1;
        }
    }
    for (int i = 0; i < x*0.4; i++) {
        for (int j = 0; j < y*0.4; j++) {
            int a=rand()%x;
            int b=rand()%y;
            mappa[a][b] = 999;
        }
    }

    width = x;
    height = y;
};

void map::drawmap(sf::RenderWindow &window,pxcount* pxcount, int x, int y) {
    float squareWidth=pxcount->getPxWidth();
    float squareHeight=pxcount->getPxHeight();
    sf::RectangleShape square({squareWidth,squareHeight});
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(4.f);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (mappa[i][j]==1) {square.setFillColor({200, 250, 200});}
            if (mappa[i][j]==2){square.setFillColor({150, 230, 150});}
            if (mappa[i][j]==3){square.setFillColor({100, 210, 100});}
            if (mappa[i][j]==4){square.setFillColor({60, 170, 60});}
            if (mappa[i][j]==5){square.setFillColor({30, 130, 30});}
            if (mappa[i][j]==999){square.setFillColor(sf::Color::Black);}
            square.setPosition({i * squareWidth, j * squareHeight});
            window.draw(square);
        }
    }
}

int map::getValue(int x, int y) {
    if (x<width && y<height && x>=0 && y>=0) {
        return mappa[x][y];
    }
    else {
        return 999;
    }
}
