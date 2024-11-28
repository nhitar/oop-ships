#include "../include/AbilityManager.hpp"

AbilityManager::AbilityManager() {
    std::vector<AbilityCreator*> vec = {new DoubleDamageAbilityCreator(), new ScannerAbilityCreator(), new GunblazeAbilityCreator()};
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(vec.begin(), vec.end(), gen);
    this->abilities.push(vec[0]);
}

int AbilityManager::getAbilityCount() const {
    return this->abilities.size();
}

AbilityCreator& AbilityManager::getCreator() {
    checkIfEmpty();
    return *this->abilities.front();
}

void AbilityManager::checkIfEmpty() {
    if (abilities.empty()) {
        throw NoAbilitiesAvailableException();
    }
}

void AbilityManager::addAbility(AbilityCreator* creator) {
   this->abilities.push(creator);
}

void AbilityManager::giveRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomNumber = gen() % 3;   
    switch (randomNumber) {
        case 0: {
            this->addAbility(new DoubleDamageAbilityCreator());
            break;
        }
        case 1: {
            this->addAbility(new ScannerAbilityCreator());
            break;
        }
        case 2: {
            this->addAbility(new GunblazeAbilityCreator());
            break;
        }
        default:
            break;
    }
}

void AbilityManager::useAbility(AbilityParameters& ap) {
    this->checkIfEmpty();
    AbilityCreator* ability = this->abilities.front();
    ability->createAbility(ap)->implementAbility();
    delete(ability);
    this->abilities.pop();
}

void AbilityManager::popAbility() {
    this->abilities.pop();
}