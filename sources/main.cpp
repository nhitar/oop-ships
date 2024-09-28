#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"

int main() {
    Field game = Field(10, 10);
    ShipManager* ships = new ShipManager;
    game.initField(ships);
    game.attack({0, 0});
    game.attack({0, 0});
    game.attack({1, 1});
    game.attack({1, 1});
    game.printField();
    return 0;
}