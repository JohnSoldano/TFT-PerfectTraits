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
            int unit_index = 0;
            int tier_index = 1;
            int trait_index = 2;

            // Ignore column headers
            for (int i = 1; i < x.size() - 1; i++) { 

                // Temporary row containing info
                auto U = x[i];
                int row_len = U.size();

                // Create vector of traits
                std::vector<std::string> traits;
                for (int k = trait_index; k < row_len; k++) {
                    traits.push_back(U.at(k));
                }

                // Create Unit obj
                Unit * myUnit = new Unit(U.at(unit_index), std::stoi(U.at(tier_index)),  traits);
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
                int cost = all_units.at(i) -> getCost();

                // For the given filter, TRUE or FALSE at the index (?) <- reword this
                filterValues = filter.at(cost - 1);

                // Condition to filter from total units
                if (filterValues == 0 || filterValues == false) {
                    all_units.erase(all_units.begin() + i);
                }
            }
}
    
    public:
        UnitController(std::string path_to_data, std::vector<bool> filter);
        ~UnitController();

        std::vector<Unit *> GetAllUnits() { return all_units; }

};

#endif // UNITCONTROLLER_H