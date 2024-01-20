// UnitController.h
#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "Unit.h"
#include "ParseCSV.h"

class UnitController {
    private:
        std::vector<Unit *> all_units;

        // Converts parsed csv data into usable data structure
        void assignUnits(std::vector<std::vector<std::string>> x) {
            // create traits vec
            // 0th column = character_id
            // 1st column = tier
            // 2nd to Inf = traits
            size_t unit_index = 0;
            size_t tier_index = 1;
            size_t trait_index = 2;

            // Ignore column headers
            for (size_t i = 1; i < x.size() - 1; i++) { 

                // Temporary row containing info
                auto U = x[i];
                size_t row_len = U.size();

                // Create vector of traits
                std::vector<std::string> traits;
                for (size_t k = trait_index; k < row_len; k++) {
                    traits.push_back(U.at(k));
                }

                // Create Unit obj
                Unit * myUnit = new Unit(U.at(unit_index), std::stoi(U.at(tier_index)),  traits);
                // Unit * myUnit = new Unit(U.at(unit_index), std::stoi(U.at(static_cast<std::size_t>(tier_index))),  traits);
                all_units.push_back(myUnit); // Save 
            }
    }
        void FilterUnits(std::vector<bool> filter) {
            int unitCost;
            int filterValues;

            // Must go in reverse for iterative removal.
            for (int i = all_units.size() - 1; i >= 0; i--) {

                // Name of Unit
                std::string name = all_units.at(i) -> getName();

                // Cost of unit
                unitCost = all_units.at(i) -> getCost();

                // For the given filter, TRUE or FALSE at the index (?) <- reword this
                filterValues = filter.at(static_cast<std::size_t>(unitCost - 1)); // implicit conversion from `int` to `std::vector<bool>::size_type

                // Condition to filter from total units
                if (filterValues == 0) {
                    all_units.erase(all_units.begin() + static_cast<int>(i));
                }
            }
}
    
    public:
        UnitController(std::string path_to_data, std::vector<bool> filter);
        ~UnitController();

        std::vector<Unit *> GetAllUnits() { return all_units; }

};

#endif // UNITCONTROLLER_H