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
class Player {
private:
    GameField field;

public:
    Player(int fieldSize = 5);

    GameField& getField();
    const GameField& getField() const;

    int attack(Player& enemy, Position position);
    bool hasLost() const;
};

class Game {
private:
    Player players[2];
    int currentPlayer;

public:
    Game(int fieldSize = 5);

    Player& getPlayer(int index);
    int getCurrentPlayer() const;

    int shoot(Position position);
    bool isFinished() const;

    int getWinner() const;
};

#endif