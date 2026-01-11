#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include "pg.h"
#include "map.h"
#include "pxcount.h"
#include "MapSearchNode.h"

int numcellsX=32,numcellsY=18;                  //dimensioni mappa, possono essere cambiate senza problemi



int main() {
    srand(time(0));

    bool canmove=false;                         //verrà usato per decidere se muovere o meno il personaggio
    MapSearchNode nodeStart;
    MapSearchNode nodeEnd;

    auto window = sf::RenderWindow( sf::VideoMode::getDesktopMode(),"mytab");
    window.setFramerateLimit(144);

    pxcount px(numcellsX,numcellsY,window.getSize().x,window.getSize().y);

    map mappa(numcellsX,numcellsY);
    MapSearchNode::worldMap = &mappa;
   // int randX=rand() % numcellsX, randY=rand() % numcellsY;//verrà usato per decidere dove spawna il personaggio

    pg player(px,0,0);
    int mouseY=0,mouseX=0;
    std::vector<sf::Vector2i> path;
    sf::Vector2i pos;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect areaVisibile({0.f, 0.f}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                window.setView(sf::View(areaVisibile));             //resize della finestra
                px.setPx(numcellsX,numcellsY,window.getSize().x,window.getSize().y);
                player.setOffsetRad(px);
                player.setPixel(px);
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    mouseX=floor(mouseButtonPressed->position.x/px.getPxWidth());
                    mouseY=floor(mouseButtonPressed->position.y/px.getPxHeight());
                    nodeEnd.x = mouseX;
                    nodeEnd.y = mouseY;
                    nodeStart.x=player.character.getPosition().x/px.getPxWidth();
                    nodeStart.y=player.character.getPosition().y/px.getPxHeight();
                    canmove = MapSearchNode::Search(nodeStart, nodeEnd, path);
                }
            }
        }
        window.clear();
        mappa.drawmap(window,&px,numcellsX,numcellsY);

        if (canmove) {
            sf::Vector2i target = path.front();
            player.move(px,target.x, target.y);
            bool targetXreached=floor(target.x*px.getPxWidth()+player.getOffsetX())==floor(player.character.getPosition().x);
            bool targetYreached=floor(target.y*px.getPxHeight()+player.getOffsetY())==floor(player.character.getPosition().y);
            if (targetXreached && targetYreached) {
                path.erase(path.begin());
                player.setPosition(px,target.x,target.y);
                if (path.empty()) {
                    canmove = false;
                }
            }
        }
        window.draw(player.character);
        MapSearchNode::drawPath(path,window,px);
        window.display();
    }
}
