// Trait.h
#ifndef TRAIT_H
#define TRAIT_H

#include <string>
#include <vector>

class Trait {
    private:
        std::string trait_id;
        std::vector<int> threshold;
    public:
        Trait(std::string t, std::vector<int> thresh);
        ~Trait();

        std::string getTraitID() { return trait_id; }
        std::vector<int> getTraitThreshold() { return threshold; }
};

#endif // TRAIT_H