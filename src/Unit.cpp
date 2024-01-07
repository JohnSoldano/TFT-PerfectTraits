// Unit.cpp
#include "Unit.h"

Unit::Unit(std::string n, int c, std::vector<std::string> t) {
    name = n;
    cost = c;
    tier = c;
    for (auto i : t) {
        traits.push_back(i);
    }
}

Unit::~Unit() {

}

void Unit::displayInfo() {
    std::cout << "\nName: " << name << std::endl;
    std::cout << "Tier: " << tier << std::endl;
    std::cout << "Traits: ";
    for (size_t k = 0; k < traits.size(); k++) {
        std::cout << traits.at(k);
        if (k < traits.size() - 1) std::cout << ", ";
        else std::cout << std::endl;
    }
    std::cout << std::endl;
}
