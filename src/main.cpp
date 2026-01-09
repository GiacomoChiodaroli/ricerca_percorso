#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include "pg.h"
#include "map.h"
#include "pxcount.h"

int numcellsX=20,numcellsY=20;                  //dimensioni mappa, possono essere cambiate senza problemi

int main() {
    srand(time(0));

    bool canmove=false;                         //verrà usato per decidere se muovere o meno il personaggio

    map mappa(numcellsX,numcellsY);
    int randX=rand() % 32, randY=rand() % 18;  //verrà usato per decidere dove spawna il personaggio

    auto window = sf::RenderWindow( sf::VideoMode::getDesktopMode(),"mytab");
    window.setFramerateLimit(144);

    pxcount px(numcellsX,numcellsY,window.getSize().x,window.getSize().y);

    while (window.isOpen()) {
        px.setPx(numcellsX,numcellsY,window.getSize().x,window.getSize().y);
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect areaVisibile({0.f, 0.f}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                window.setView(sf::View(areaVisibile));             //resize della finestra
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    int mouseX=floor(mouseButtonPressed->position.x/px.getPxWidth());
                    int mouseY=floor(mouseButtonPressed->position.y/px.getPxHeight());
                    std::cout << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
        }
        window.clear();
        mappa.drawmap(window,&px,numcellsX,numcellsY);
        window.display();
    }
}
