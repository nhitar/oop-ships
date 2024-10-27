#include "../include/AbilityManager.hpp"

AbilityManager::AbilityManager(Field& field) : field(field){
    std::vector<Abilities> vec = {Abilities::DoubleDamage, Abilities::Scanner, Abilities::Gunblaze};
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(vec.begin(), vec.end(), gen);
    this->abilities.push(vec[0]);
}

int AbilityManager::getAbilityCount() const {
    return this->abilities.size();
}

Abilities AbilityManager::front() const {
    return this->abilities.front();
}

void AbilityManager::addAbility(Abilities ability) {
   this->abilities.push(ability);
}

void AbilityManager::giveRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomNumber = gen() % 3;   
    switch (randomNumber) {
        case 0: {
            this->addAbility(Abilities::DoubleDamage);
            break;
        }
        case 1: {
            this->addAbility(Abilities::Scanner);
            break;
        }
        case 2: {
            this->addAbility(Abilities::Gunblaze);
            break;
        }
        default:
            break;
    }
}

void AbilityManager::useAbility(Coordinate coordinate) {
    Abilities ability = this->abilities.front();
    this->abilities.pop();
    if (coordinate.x == -1 && coordinate.y == -1) {
        (new GunblazeAbilityCreator(this->field))->createAbility()->implementAbility();
        return;
    }
    
    if (ability == Abilities::DoubleDamage) {
        (new DoubleDamageAbilityCreator(this->field, coordinate))->createAbility()->implementAbility();
        return;
    }
    
    if (ability == Abilities::Scanner) {
        (new ScannerAbilityCreator(this->field, coordinate))->createAbility()->implementAbility();
        return;
    }
    
}