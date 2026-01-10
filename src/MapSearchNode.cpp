#include "MapSearchNode.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "stlastar.h"
#include "map.h"
using namespace std;

map* MapSearchNode::worldMap = nullptr;

bool MapSearchNode::IsSameState(MapSearchNode& rhs) {
    // same state in a maze search is simply when (x,y) are the same
    if ((x == rhs.x) && (y == rhs.y)) {
        return true;
    } else {
        return false;
    }
}

size_t MapSearchNode::Hash() {
    size_t h1 = hash<float>{}(x);
    size_t h2 = hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

void MapSearchNode::PrintNodeInfo() {
    const int strSize = 100;
    char str[strSize];
    snprintf(str, strSize, "Node position : (%d,%d)\n", x, y);

    cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate(MapSearchNode& nodeGoal) {
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal(MapSearchNode& nodeGoal) {
    if ((x == nodeGoal.x) && (y == nodeGoal.y)) {
        return true;
    }

    return false;
}

bool MapSearchNode::GetSuccessors(
    AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node,map mappa) {
    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }

    MapSearchNode NewNode;

    // push each possible move except allowing the search to go backwards

    if ((mappa.getValue(x - 1, y) < 9) && !((parent_x == x - 1) && (parent_y == y))) {
        NewNode = MapSearchNode(x - 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((mappa.getValue(x, y - 1) < 9) && !((parent_x == x) && (parent_y == y - 1))) {
        NewNode = MapSearchNode(x, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((mappa.getValue(x + 1, y) < 9) && !((parent_x == x + 1) && (parent_y == y))) {
        NewNode = MapSearchNode(x + 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((mappa.getValue(x, y + 1) < 9) && !((parent_x == x) && (parent_y == y + 1))) {
        NewNode = MapSearchNode(x, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }

    return true;
}

float MapSearchNode::GetCost( MapSearchNode &successor ) {
    return (float)worldMap->getValue(successor.x, successor.y);
}


bool MapSearchNode::Search(MapSearchNode nodeStart, MapSearchNode nodeEnd, std::vector<sf::Vector2i>& path, map mappa){
path.clear();
    AStarSearch<MapSearchNode> astarsearch;
    bool succed=false;

    unsigned int SearchCount = 0;

    const unsigned int NumSearches = 1;

    while (SearchCount < NumSearches) {

        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do {
            SearchState = astarsearch.SearchStep();

            SearchSteps++;

#if DEBUG_LISTS

            cout << "Steps:" << SearchSteps << "\n";

            int len = 0;

            cout << "Open:\n";
            MapSearchNode* p = astarsearch.GetOpenListStart();
            while (p) {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                ((MapSearchNode*)p)->PrintNodeInfo();
#endif
                p = astarsearch.GetOpenListNext();
            }

            cout << "Open list has " << len << " nodes\n";

            len = 0;

            cout << "Closed:\n";
            p = astarsearch.GetClosedListStart();
            while (p) {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                p->PrintNodeInfo();
#endif
                p = astarsearch.GetClosedListNext();
            }

            cout << "Closed list has " << len << " nodes\n";
#endif

        } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

        if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
            cout << "Search found goal state\n";
            succed = true;
            MapSearchNode* node = astarsearch.GetSolutionStart();

#if DISPLAY_SOLUTION
            cout << "Displaying solution\n";
#endif
            int steps = 0;

            node->PrintNodeInfo();
            for (;;) {
                node = astarsearch.GetSolutionNext();
                if (!node) {
                    break;
                }
                path.push_back(sf::Vector2i(node->x, node->y));
                node->PrintNodeInfo();
                steps++;
            };

            cout << "Solution steps " << steps << endl;

            // Once you're done with the solution you can free the nodes up
            astarsearch.FreeSolutionNodes();

        } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
            cout << "Search terminated. Did not find goal state\n";
            succed = false;
        }

        // Display the number of loops the search went through
        cout << "SearchSteps : " << SearchSteps << "\n";

        SearchCount++;

        astarsearch.EnsureMemoryFreed();
    }

    return succed;
};

void MapSearchNode:: drawPath(std::vector<sf::Vector2i>& path,sf::RenderWindow &window, pxcount px) {
    float r;
    if (px.getPxHeight()<px.getPxWidth()) {
        r=px.getPxHeight()*0.375;
    }else {
        r=px.getPxWidth()*0.375;
    }
    float offsetX=px.getPxWidth()/2-2;  // il -2 serve alltrimenti non è perfettamente centrato sul mio monitor, fare prove
    float offsetY=px.getPxHeight()/2-2; // per vedere se viene centratro con altri valori
    sf::CircleShape square(r, 4);
    square.setFillColor({200,200,200});
    square.setRotation(sf::degrees(45));
    square.setOutlineColor(sf::Color::Black);
    square.setOutlineThickness(4.f);
    for (int i = 0; i < path.size(); i++) {
        x=path[i].x;
        y=path[i].y;
        square.setPosition({x*px.getPxWidth()+offsetX, y*px.getPxHeight()+offsetY});
        window.draw(square);
    }
}