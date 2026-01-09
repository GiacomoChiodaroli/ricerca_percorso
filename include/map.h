#ifndef MAP_H
#define MAP_H
#include "pxcount.h"
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <SFML/Graphics.hpp>

class map {
    private:
    std::vector<std::vector<int>> mappa;
    public:
    map(int x, int y);
    void drawmap(sf::RenderWindow &window,pxcount* pxcount, int x, int y);
    int getValue(int x, int y);
    ~map() = default;
};



#endif //MAP_H
