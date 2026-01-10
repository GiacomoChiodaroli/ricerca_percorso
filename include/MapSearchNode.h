#ifndef MAPSEARCHNODE_H
#define MAPSEARCHNODE_H
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "stlastar.h"
#include "map.h"
#include "pxcount.h"

class MapSearchNode {
public:
    static map* worldMap;
    int x;  // the (x,y) positions of the node
    int y;

    MapSearchNode() {
        x = y = 0;
    }
    MapSearchNode(int px, int py) {
        x = px;
        y = py;
    }


    bool Search(MapSearchNode nodeStart, MapSearchNode nodeEnd, std::vector<sf::Vector2i>& path, map mappa);
    float GoalDistanceEstimate(MapSearchNode& nodeGoal);
    bool IsGoal(MapSearchNode& nodeGoal);
    bool GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node,map mappa);
    float GetCost(MapSearchNode& successor);
    bool IsSameState(MapSearchNode& rhs);
    size_t Hash();
    void drawPath(std::vector<sf::Vector2i>& path,sf::RenderWindow &window, pxcount px);

    void PrintNodeInfo();
};

#endif //MAPSEARCHNODE_H
