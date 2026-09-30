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


TEST(ShipTest, HorizontalShip) {
    Ship ship(Position(0, 0), 2, true);

    EXPECT_TRUE(ship.contains(Position(0, 0)));
    EXPECT_TRUE(ship.contains(Position(1, 0)));
    EXPECT_FALSE(ship.contains(Position(0, 1)));
}

TEST(ShipTest, VerticalShip) {
    Ship ship(Position(0, 0), 2, false);

    EXPECT_TRUE(ship.contains(Position(0, 0)));
    EXPECT_TRUE(ship.contains(Position(0, 1)));
    EXPECT_FALSE(ship.contains(Position(1, 0)));
}

TEST(ShipTest, ShootAndSink) {
    Ship ship(Position(0, 0), 2, true);

    EXPECT_FALSE(ship.isSunk());

    EXPECT_TRUE(ship.shoot(Position(0, 0)));
    EXPECT_FALSE(ship.isSunk());

    EXPECT_TRUE(ship.shoot(Position(1, 0)));
    EXPECT_TRUE(ship.isSunk());
}

TEST(ShipTest, Miss) {
    Ship ship(Position(0, 0), 1, true);

    EXPECT_FALSE(ship.shoot(Position(3, 3)));
    EXPECT_FALSE(ship.isSunk());
}