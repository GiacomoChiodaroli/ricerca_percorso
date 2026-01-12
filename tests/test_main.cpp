#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "MapSearchNode.h"
#include "pg.h"
#include "pxcount.h"

TEST(pgTest, PosizioneIniziale) {
    pxcount px(2,2,100,100);
    pg g(px,0,0);
    EXPECT_FLOAT_EQ(g.character.getPosition().x, g.getOffsetX());
    EXPECT_FLOAT_EQ(g.character.getPosition().y, g.getOffsetY());
}
TEST(pgTest, Movimento) {
    pxcount px(2,2,100,100);
    pg g(px,0,0);
    for (int i=0;i<60;i++) {
        g.move(px,1,0);
    }
    EXPECT_FLOAT_EQ(g.character.getPosition().x,50+ g.getOffsetX());
    EXPECT_FLOAT_EQ(g.character.getPosition().y, g.getOffsetY());
    for (int i=0;i<60;i++) {
        g.move(px,1,1);
    }
    EXPECT_FLOAT_EQ(g.character.getPosition().y,50+ g.getOffsetY());
    EXPECT_FLOAT_EQ(g.character.getPosition().x,50+ g.getOffsetX());
}
TEST(findpathTest, RicercaPercorso) {
    map mappa(2,2);
    MapSearchNode::worldMap = &mappa;
    std::vector<sf::Vector2i> path;
    MapSearchNode nodeStart;
    nodeStart.x=0;
    nodeStart.y=0;
    MapSearchNode nodeEnd;
    nodeEnd.x=1;
    nodeEnd.y=1;
    EXPECT_TRUE(MapSearchNode::Search(nodeStart, nodeEnd, path));
    nodeEnd.x=1;
    nodeEnd.y=0;
    EXPECT_FALSE(MapSearchNode::Search(nodeStart, nodeEnd, path));
    EXPECT_TRUE(path.empty())<<"path non è vuoto";
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
