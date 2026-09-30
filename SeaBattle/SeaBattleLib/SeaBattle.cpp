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
