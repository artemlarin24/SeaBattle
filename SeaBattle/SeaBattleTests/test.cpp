#include "pch.h"


#include "SeaBattle.h"

TEST(PositionTest, DefaultCoordinates) {
    Position position;

    EXPECT_EQ(position.x, 0);
    EXPECT_EQ(position.y, 0);
}

TEST(PositionTest, Coordinates) {
    Position position(2, 3);

    EXPECT_EQ(position.x, 2);
    EXPECT_EQ(position.y, 3);
}

TEST(PositionTest, Equality) {
    EXPECT_TRUE(Position(1, 2) == Position(1, 2));
    EXPECT_FALSE(Position(1, 2) == Position(2, 1));
}
