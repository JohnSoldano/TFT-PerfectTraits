// Trait.cpp
#include "Trait.h"

Trait::Trait(std::string t, std::vector<int> thresh) : trait_id() , threshold() {
    // Save ID
    trait_id = t;

    // Save Trait Tresholds
    for (auto & x : thresh) {
        threshold.push_back(x);
    }

}

Trait::~Trait() {
    
}