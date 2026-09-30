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

TEST(GameFieldTest, SizeAndBorders) {
    GameField field(5);

    EXPECT_EQ(field.getSize(), 5);
    EXPECT_TRUE(field.isInside(Position(0, 0)));
    EXPECT_TRUE(field.isInside(Position(4, 4)));
    EXPECT_FALSE(field.isInside(Position(5, 0)));
    EXPECT_FALSE(field.isInside(Position(-1, 0)));
}

TEST(GameFieldTest, AddShip) {
    GameField field(5);

    EXPECT_TRUE(field.addShip(Ship(Position(0, 0), 2, true)));
    EXPECT_FALSE(field.addShip(Ship(Position(0, 0), 1, true)));
    EXPECT_FALSE(field.addShip(Ship(Position(4, 4), 2, true)));
}

TEST(GameFieldTest, Shoot) {
    GameField field(5);
    ASSERT_TRUE(field.addShip(Ship(Position(0, 0), 2, true)));

    EXPECT_EQ(field.shoot(Position(4, 4)), 0);
    EXPECT_EQ(field.shoot(Position(0, 0)), 1);
    EXPECT_EQ(field.shoot(Position(1, 0)), 2);

    EXPECT_TRUE(field.allShipsSunk());
}

TEST(GameFieldTest, RepeatedShot) {
    GameField field(5);

    EXPECT_EQ(field.shoot(Position(2, 2)), 0);
    EXPECT_EQ(field.shoot(Position(2, 2)), -1);
}

TEST(PlayerTest, Attack) {
    Player first(5);
    Player second(5);

    ASSERT_TRUE(second.getField().addShip(Ship(Position(0, 0), 1, true)));

    EXPECT_FALSE(second.hasLost());
    EXPECT_EQ(first.attack(second, Position(0, 0)), 2);
    EXPECT_TRUE(second.hasLost());
}

TEST(GameTest, ChangeTurnAfterMiss) {
    Game game(5);

    ASSERT_TRUE(game.getPlayer(0).getField().addShip(
        Ship(Position(0, 0), 1, true)));

    ASSERT_TRUE(game.getPlayer(1).getField().addShip(
        Ship(Position(2, 2), 1, true)));

    EXPECT_EQ(game.getCurrentPlayer(), 0);
    EXPECT_EQ(game.shoot(Position(4, 4)), 0);
    EXPECT_EQ(game.getCurrentPlayer(), 1);
}

TEST(GameTest, Victory) {
    Game game(5);

    ASSERT_TRUE(game.getPlayer(0).getField().addShip(
        Ship(Position(0, 0), 1, true)));

    ASSERT_TRUE(game.getPlayer(1).getField().addShip(
        Ship(Position(2, 2), 1, true)));

    EXPECT_FALSE(game.isFinished());
    EXPECT_EQ(game.getWinner(), -1);

    EXPECT_EQ(game.shoot(Position(2, 2)), 2);

    EXPECT_TRUE(game.isFinished());
    EXPECT_EQ(game.getWinner(), 0);
}
