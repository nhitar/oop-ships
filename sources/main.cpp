#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"

int main() {
    Field game = Field(10, 10);
    ShipManager* ships = new ShipManager;
    game.initField(ships->getShips());
    game.printField();
    while (true) {
        int x, y;
        std::cin >> x >> y;
        if (x == -1 && y == -1) {
            break;
        }
        game.attack({x - 1, y - 1});
        game.printField();
    }
    return 0;
}