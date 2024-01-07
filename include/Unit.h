// Units.h
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <iostream>

// Class representing a single Unit.
class Unit {
    private:
        std::string name;
        int tier;
        int cost;
        std::vector<std::string> traits;
    public:
    // Creates a Unit.
    // Parameters:
    //      Name: The name of the unit.
    //      Tier: The tier of the unit.
    //      Cost: The cost of the unit.
    //      Traits: The associated traits for a unit.
        Unit(std::string n, int c, std::vector<std::string> t);
        ~Unit();

        // Returns the `name` of the unit.
        std::string getName() { return name; }

        // Returns the `tier` of the unit.
        int getTier() { return tier; }

        // Returns the `cost` of the unit.
        int getCost() { return cost; }

        // Returns all `traits` of the unit.
        std::vector<std::string> getTraits() { return traits; }

        // Display the attributes of a Unit.
        void displayInfo();
};
#endif // UNITS_H