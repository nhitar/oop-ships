#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"

int main() {
    Field game = Field(10, 10);
    ShipManager* ships = new ShipManager;
    // Ship* ship = new Ship(3);
    game.initField(ships);
    for (int i = 0; i < 10; i++) {
        game.attack({i, 4});
        game.attack({i, 7});
    }
    game.printField();
    return 0;
}