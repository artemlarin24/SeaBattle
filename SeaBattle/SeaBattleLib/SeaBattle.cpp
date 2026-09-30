#include "SeaBattle.h"
#include <stdexcept>

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

Ship::Ship(Position start, int size, bool horizontal) {
    if (size <= 0) {
        throw std::invalid_argument("Ship size must be positive");
    }

    for (int i = 0; i < size; i++) {
        if (horizontal) {
            positions.push_back(Position(start.x + i, start.y));
        }
        else {
            positions.push_back(Position(start.x, start.y + i));
        }

        hits.push_back(false);
    }
}

const std::vector<Position>& Ship::getPositions() const {
    return positions;
}

bool Ship::contains(Position position) const {
    for (const Position& cell : positions) {
        if (cell == position) {
            return true;
        }
    }

    return false;
}

bool Ship::shoot(Position position) {
    for (int i = 0; i < static_cast<int>(positions.size()); i++) {
        if (positions[i] == position) {
            if (hits[i]) {
                return false;
            }

            hits[i] = true;
            return true;
        }
    }

    return false;
}

bool Ship::isSunk() const {
    for (bool hit : hits) {
        if (!hit) {
            return false;
        }
    }

    return true;
}


GameField::GameField(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Field size must be positive");
    }

    this->size = size;
}

int GameField::getSize() const {
    return size;
}

bool GameField::isInside(Position position) const {
    return position.x >= 0 && position.x < size &&
        position.y >= 0 && position.y < size;
}

bool GameField::addShip(const Ship& ship) {
    for (const Position& cell : ship.getPositions()) {
        if (!isInside(cell)) {
            return false;
        }

        for (const Ship& existingShip : ships) {
            for (const Position& existingCell : existingShip.getPositions()) {
                int dx = cell.x - existingCell.x;
                int dy = cell.y - existingCell.y;

       
                if (dx >= -1 && dx <= 1 &&
                    dy >= -1 && dy <= 1) {
                    return false;
                }
            }
        }
    }

  
    if (!shots.empty()) {
        return false;
    }

    ships.push_back(ship);
    return true;
}

bool GameField::wasShot(Position position) const {
    for (const Position& shot : shots) {
        if (shot == position) {
            return true;
        }
    }

    return false;
}

int GameField::shoot(Position position) {
    if (!isInside(position) || wasShot(position)) {
        return -1;
    }

    shots.push_back(position);

    for (Ship& ship : ships) {
        if (ship.shoot(position)) {
            if (ship.isSunk()) {
                return 2;
            }

            return 1;
        }
    }

    return 0;
}

bool GameField::allShipsSunk() const {
    if (ships.empty()) {
        return false;
    }

    for (const Ship& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }

    return true;
}

char GameField::getCell(Position position, ShowShip showShips) const {
    if (!isInside(position)) {
        return '?';
    }

    bool hasShip = false;

    for (const Ship& ship : ships) {
        if (ship.contains(position)) {
            hasShip = true;
            break;
        }
    }

    if (wasShot(position)) {
        if (hasShip) {
            return 'X';
        }

        return 'o';
    }

    if (showShips == ShowShip::Yes && hasShip) {
        return 'S';
    }

    return '.';
}

Player::Player(int fieldSize) : field(fieldSize) {
}

GameField& Player::getField() {
    return field;
}

const GameField& Player::getField() const {
    return field;
}

int Player::attack(Player& enemy, Position position) {
    return enemy.field.shoot(position);
}

bool Player::hasLost() const {
    return field.allShipsSunk();
}

Game::Game(int fieldSize)
    : players{ Player(fieldSize), Player(fieldSize) } {
    currentPlayer = 0;
}

Player& Game::getPlayer(int index) {
    if (index < 0 || index > 1) {
        throw std::out_of_range("Invalid player index");
    }

    return players[index];
}

int Game::getCurrentPlayer() const {
    return currentPlayer;
}

int Game::shoot(Position position) {
    if (isFinished()) {
        return -1;
    }

    int enemy = 1 - currentPlayer;
    int result = players[currentPlayer].attack(players[enemy], position);

    if (result == 0) {
        currentPlayer = enemy;
    }

    return result;
}

bool Game::isFinished() const {
    return players[0].hasLost() || players[1].hasLost();
}

int Game::getWinner() const {
    if (players[0].hasLost()) {
        return 1;
    }

    if (players[1].hasLost()) {
        return 0;
    }

    return -1;
}

