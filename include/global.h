// global.h

#ifndef GLOBAL_H
#define GLOBAL_H


#include "Team.h"
#include "Trait.h"
#include "init.h"
#include <fstream>
#include <streambuf>
#include <memory>

// Place all units into a Class
// std::vector<Unit *> assignUnits(std::vector<std::vector<std::string>> units);

// Remove Units from the pool via filtering config.
void filterUnits(std::vector<Unit *> & units, init in);


// Using data from parsed `Traits.csv`, mapping between `Trait` and `Trait` object.
// std::vector<Trait *> assignTraits(std::vector<std::vector<std::string>> traits);

// More elegant Trait data structure?
struct TraitStruct {
    std::unordered_map<std::string, Trait *> myMap;

    // Destructor to clean up dynamically allocated objects
    ~TraitStruct() {
        for (auto & pair : myMap) {
            delete pair.second;
        }
        myMap.clear();
    }

    
    void add(const std::string & key, Trait * value) {
        // Remove existing entry if present
        auto it = myMap.find(key);
        if (it != myMap.end()) {
            delete it -> second;
        }
        myMap[key] = value;
    }

    Trait * get(const std::string & key) const {
        auto it = myMap.find(key);
        if (it != myMap.end()) {
            return it -> second;
        }
        return nullptr;
    }

    void parse(std::vector<Trait *> trait) {
        for (auto it : trait) {
            add(it -> getTraitID(), it);
        }
    }
};


// For a given trait, calculates the partial and total score.
// std::tuple<int, int> findTraitThreshold(std::vector<int> traitThreshold, int teamTraitTotal);

// // For a given trait, calculates the partial and total score.
// std::map<std::string, int> calculateTraitThreshold(std::tuple<int, int> tuple, int total);

// // The purpose of this class is to perform calculations for "Team Traits".
// // This will calculate `partialTraits`, `perfectTraits`, `totalTraits`, `teamCostAvg`,
// // etc,...
// // The class will be initialized with `currentTeamTraits` and the `subsetTraitMap`
// std::map<std::string, std::map<std::string, int>> calculateTeamTotals(std::unordered_map<std::string, int> currentTeamTraits, const TraitStruct & trait_data);

// std::map<std::string, int> scoreTeamTotals(std::map<std::string, std::map<std::string, int>> teamTotals);

// Output data to csv format.
void OutputCSV(std::string path, std::vector<Team> final_teams);

// Output data as txt format.
void OutputTXT(std::string path, std::vector<Team> final_teams);

#endif // GLOBAL_H