#include "../include/AbilityManager.hpp"

AbilityManager::AbilityManager(){
    std::random_device rd;
    std::mt19937 gen(rd());
    this->abilityCount = 0;

    this->addAbility();

    std::shuffle(this->abilities.begin(), this->abilities.end(), gen);
}

std::deque<Ability*>* AbilityManager::getDeque() {
    return &(this->abilities);
}

int AbilityManager::getAbilityCount() const {
    return this->abilityCount;
}
void AbilityManager::setAbilityCount(int count) {
    this->abilityCount = count;
}

void AbilityManager::addAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    int randomNum = dis(gen);
    switch (randomNum) {
        case 0:
            this->abilities.push_back(new DoubleDamage(new Field(0, 0), {0, 0}));
            break;
        case 1:
            this->abilities.push_back(new Scanner(new Field(0, 0), {0, 0}));
            break;
        case 2:
            this->abilities.push_back(new Gunblaze(new Field(0, 0)));
            break;
        default:
            break;
    }
    this->abilityCount++;
    std::shuffle(this->abilities.begin(), this->abilities.end(), gen);
}