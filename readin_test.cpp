#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

// g++ -o main readin_test.cpp; ./main

class Trait {
    private:
        // Attributes
        std::string Name;
        std::vector<int> MinUnits;
    
    public:
        // Constructor
        Trait(std::string name, std::vector<int> min_units) {
            Name = name;
            for (auto i : min_units) {
                MinUnits.push_back(i);
            }
        }

        // Getters
        std::vector<int> getMinUnits() { return MinUnits; }
};

// Finish this class.
class Unit {
    private:
        // Attributes
        std::string Name;
        int Tier;
        std::vector<std::string> Traits;

    public:
        // Constructor
        Unit(std::string name, int tier, std::vector<std::string> traits) {
            Name = name;
            Tier = tier;
            for (auto i : traits) {
                Traits.push_back(i);
            }
        }

        // Getters
        // Name
        // Tier/Cost
        // Traits

        std::string getName() { return Name; }
        int getTier() { return Tier; }
        std::vector<std::string> getTraits() { return Traits; }

        void displayInfo() {
            std::cout << "\nName: " << Name << std::endl;
            std::cout << "Tier: " << Tier << std::endl;
            std::cout << "Traits: ";
            for (size_t k = 0; k < Traits.size(); k++) {
                std::cout << Traits.at(k);
                if (k < Traits.size() - 1) std::cout << ", ";
                else std::cout << std::endl;
            }
        std::cout << std::endl;
        }
};


class Team {
    private:
        // Attibutes
        std::vector<Unit *> team;
        std::unordered_map<std::string, int> trait_count;

        //CountTraits
        void countTraits() {
            std::vector<std::string> rawTraits;

            for (auto & x : team) {
                std::vector<std::string> tmpTraits = x -> getTraits();

                for (auto & y : tmpTraits) {
                    rawTraits.push_back(y);
                }
            }

            std::unordered_map<std::string, int> counts;
            // Count the occurrences of each string
            for (const auto & elem : rawTraits) {
                ++counts[elem];
            }

            trait_count = counts;
        }
    
    public:
        // Constructor
        Team(std::vector<Unit *> units) {
            // Store Traits
            for (auto i : units) {
                team.push_back(i);
            }

            // Automatically Count Traits
            countTraits();
        }

        // #### Getters ####

        // Return counts of traits.
        std::unordered_map<std::string, int> getTraitCount() { return trait_count; }

        // Return Team Object
        std::vector<Unit *> getTeam() { return team; }
        
        // Display Team
        void displayTeam() {
            for (auto & it : team) {
                it ->  displayInfo();
            }
        }

        // Show formatted trait count
        void displayCounts() {
            
            // Display the counts
            for (const auto & pair : trait_count) {
                std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
            }
        }
};

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str) {
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str, line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while (std::getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }
    if (!lineStream && cell.empty()) {
        result.push_back("");
    }
    return result;
}
std::vector<std::vector<std::string>> parseCSV(std::string path) {
    std::ifstream file(path);
    /*
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    */

    std::vector<std::vector<std::string>> row;
    while (file) {
        std::vector<std::string> column;

        std::vector<std::string> lineData = getNextLineAndSplitIntoTokens(file);
        for (const auto& token : lineData) {
            column.push_back(token);
            //std::cout << token << " ";
        }
        row.push_back(column);
        //std::cout << std::endl;
    }

    return(row);
}

//      Place all units into a Class
std::vector<Unit *> assignUnits(std::vector<std::vector<std::string>> units) {
    std::vector<Unit *> allUnits;
    for (int i = 1; i < units.size() - 1; i++) { // Why must I subtract 1?
        // Temporary row containing info
        std::vector<std::string> U = units[i];
        int row_len = U.size();
        int tier = std::stoi(U.at(1));
        // create traits vec
        std::vector<std::string> traits;
        for (int k = 2; k < row_len; k++) {
            traits.push_back(U.at(k));
        }

        Unit * myUnit = new Unit(U.at(0), tier, traits);
        allUnits.push_back(myUnit);
    }

    return allUnits;
}

//      Using data from parsed `Traits.csv`, mapping between `Trait` and `Trait` object.
//      This function has removed `unique` traits.
//      
//          Note: When this confuses you in the future, think of this as a named list returning a vector.
std::map<std::string, Trait *> assignTraits(std::vector<std::vector<std::string>> traits) {
    std::map<std::string, Trait *> traitMap;
    std::vector<Trait *> allTraits;

    for (int i = 1; i < traits.size() - 1; i++) {
        std::vector<std::string> T = traits[i];
        int row_len = T.size();
        std::vector<int> tmp_traits;
        for (int k = 1; k < row_len; k++) {
            tmp_traits.push_back(stoi(T.at(k)));
        }

        // Condition preventing unique trait from existing in mapping.
        if (tmp_traits.size() > 1) {
            Trait * myTrait = new Trait(T.at(0), tmp_traits);
            traitMap[T.at(0)] = myTrait;
        }        
    }

    return traitMap;
}

// Create a mapping between Units and Class
std::map<std::string, Unit *> mapUnits(std::vector<Unit *> allUnits) {
      std::map<std::string, Unit *> unitMap;

    for (Unit * unit : allUnits) {
        unitMap[unit -> getName()] = unit;
    }

    return unitMap;

}

// Find the index for a row...
int findIndex(const std::vector<std::string>& vec, const std::string& target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec.at(i) == target) {
            return i;  // Return the index of the found element
        }
    }
    return -1;  // Return -1 if the element is not found
}

// For a given string vector, return the team from a mapping
Team * createTeam(std::vector<std::string> unit_id, std::map<std::string, Unit *> unit_map) {
    std::vector<Unit *> tmpTeam;

    // Create vector of units
    for (auto & it : unit_id) {
        tmpTeam.push_back(unit_map[it]);
    }

    // Assign Vector of units to team.
    Team * newTeam = new Team(tmpTeam);
    return newTeam;
}

bool isPerfectTrait(std::vector<int> min_units, int total) {
    bool isPerfect = false;
    int i = 0;
    while (!isPerfect && i < min_units.size() - 1) {
        if (min_units.at(i) == total) isPerfect = true;
        i++;
    }
    return isPerfect;
}

// Combine assignUnits and mapUnits
int main() {
    // Parse data into csv
    std::vector<std::vector<std::string>> Units = parseCSV("D:/MyProjects/TFT/Set10/Units_v02.csv");
    std::vector<std::vector<std::string>> Traits = parseCSV("D:/MyProjects/TFT/Set10/Traits_v02.csv");

    // Create Class for Units
    std::vector<Unit *> allUnits = assignUnits(Units);

    // Assign Mapping to Units
    std::map<std::string, Unit *> unitMap = mapUnits(allUnits);

    // Mapping between trait and the minimum units.
    //          string: Name of trait
    //          Trait*: Object 
    std::map<std::string, Trait *> traitMap = assignTraits(Traits);

    // for (auto & it : traitMap) {
    //     std::cout << it.first << ": ";
    //     for (auto & jt : it.second -> getMinUnits()) {
    //         std::cout << jt << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // <---------------><----------------> HERE
    // for (auto & it : traitMap) {
    //     Trait * tmpTrait = it.second;

    //     std::cout << it.first << ": ";
    //     for (auto & jt : tmpTrait -> getMinUnits()) {
    //         std::cout << jt << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // <---------------><----------------> HERE


    // Simulate adding a team to class
    std::vector<std::string> x = {"Jhin", "Kaisa"};
    Team * testTeam = createTeam(x, unitMap);
    // testTeam -> displayTeam();
    // testTeam -> displayCounts();

    // For a given Team, simulate comparing `trait_count` against `traitMap`.
    // Select a subset of traitMap by the names of `trait_count`.
    std::map<std::string, Trait *> traitMapSubset;
    std::unordered_map<std::string, int> currentTeamTraits = testTeam -> getTraitCount();

    // for (auto & it : currentTeamTraits) {
    //     std::cout << it.first << ": " << it.second << std::endl;
    // }


    // Select the traits from the current team and subset the mapping.
    for (auto & it : currentTeamTraits) {
        traitMapSubset[it.first] = traitMap[it.first];
        traitMap[it.first] ->  getMinUnits();
    }

    // for (auto & it : traitMapSubset) {
    //     std::cout << it.first << std::endl;
    //     for (auto & jt : it.second ->  getMinUnits()) {
    //         std::cout << jt << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (auto & it : traitMap)

    for (auto & it : traitMapSubset) {
        bool perfect = isPerfectTrait(it.second -> getMinUnits(), currentTeamTraits[it.first]);
        std::cout << "\nTrait: " << it.first << std::endl;
        std::cout << "Total: " << currentTeamTraits[it.first] << std::endl;
        std::cout << "Valid: " << perfect << std::endl;
    }

    // // Display totals
    // std::cout << "\ncurrentTeamTraits" << std::endl;
    // for (auto & it : currentTeamTraits) {
    //     std::cout << it.first << ": " << it.second << std::endl;
    // }

    // for (auto & it : traitMapSubset) {
    //     std::cout << it.first << ": ";

    //     std::vector<int> blah = it.second -> getMinUnits();
    //     for (auto & jt : blah) {
    //         std::cout << jt << " ";
    //     }
    //     std::cout << std::endl;
    // }




    //testTeam -> countTraits();

    // Team operations such as:
    //      Count completed traits?
    //      Summary of units and cost?

    //Team * myTeam = new Team();

    /*
        for (auto & it : traitMap) {
        std::cout << it.first << ") " << std::endl;

        std::vector<int> blah = it.second -> getMinUnits();
        for (auto & jt : blah) {
            std::cout << jt << " ";
        }
        std::cout << std::endl;
    }
    
    */
    return 0;
}