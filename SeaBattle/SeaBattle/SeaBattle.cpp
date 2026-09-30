#include <iostream>

#include "SeaBattle.h"

void printField(const GameField& field) {
    std::cout << "  ";

    for (int x = 0; x < field.getSize(); x++) {
        std::cout << x + 1 << " ";
    }

    std::cout << "\n";

    for (int y = 0; y < field.getSize(); y++) {
        std::cout << y + 1 << " ";

        for (int x = 0; x < field.getSize(); x++) {
            std::cout << field.getCell(Position(x, y), ShowShip::No) << " ";
        }

        std::cout << "\n";
    }
}

int main() {
    Game game(5);

    game.getPlayer(0).getField().addShip(Ship(Position(0, 0), 2, true));
    game.getPlayer(0).getField().addShip(Ship(Position(4, 4), 1, true));

    game.getPlayer(1).getField().addShip(Ship(Position(3, 0), 2, false));
    game.getPlayer(1).getField().addShip(Ship(Position(0, 4), 1, true));

    std::cout << "Морской бой\n";
    std::cout << "Координаты: столбец и строка от 1 до 5.\n";
    std::cout << "X — попадание, o — промах, . — неизвестная клетка.\n";

    while (!game.isFinished()) {
        int player = game.getCurrentPlayer();
        int enemy = 1 - player;

        std::cout << "\nХод игрока " << player + 1 << "\n";
        printField(game.getPlayer(enemy).getField());

        int x;
        int y;

        std::cout << "Введите координаты выстрела: ";

        if (!(std::cin >> x >> y)) {
            std::cout << "Игра завершена.\n";
            return 0;
        }

        ShotResult result = game.shoot(Position(x - 1, y - 1));

        if (result == ShotResult::Invalid) {
            std::cout << "Неверные координаты или повторный выстрел.\n";
        }
        else if (result == ShotResult::Miss) {
            std::cout << "Промах!\n";
        }
        else if (result == ShotResult::Hit) {
            std::cout << "Попадание!\n";
        }
        else if (result == ShotResult::Sunk) {
            std::cout << "Корабль потоплен!\n";
        }
    }

    std::cout << "\nПобедил игрок " << game.getWinner() + 1 << "!\n";

    return 0;
}