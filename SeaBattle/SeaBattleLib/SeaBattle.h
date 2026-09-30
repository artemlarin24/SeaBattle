#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>

class Position {
public:
    int x;
    int y;

    Position(int x = 0, int y = 0);

    bool operator==(const Position& other) const;
};

class Ship {
private:
    std::vector<Position> positions;
    std::vector<bool> hits;

public:
    Ship(Position start, int size, bool horizontal);

    const std::vector<Position>& getPositions() const;

    bool contains(Position position) const;
    bool shoot(Position position);
    bool isSunk() const;
};

class GameField {
private:
    int size;
    std::vector<Ship> ships;
    std::vector<Position> shots;

public:
    GameField(int size = 5);

    int getSize() const;
    bool isInside(Position position) const;
    bool addShip(const Ship& ship);
    bool wasShot(Position position) const;

  
    int shoot(Position position);

    bool allShipsSunk() const;
    char getCell(Position position, bool showShips) const;
};

#endif