#include "global.h"

// Place all units into a Class
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

        Unit *myUnit = new Unit(U.at(0), tier, traits);
        allUnits.push_back(myUnit);
    }

    return allUnits;
}

// Remove Units from the pool via filtering config.
void filterUnits(std::vector<Unit *> & units, init in) {
    int unitCost;
    int filterValues;

    // Must go in reverse for iterative removal.
    for (int i = units.size() - 1; i >= 0; i--) {
        std::string name = units.at(i) -> getName();
        int cost = units.at(i) -> getCost();
        filterValues = in.filter.at(cost - 1);

        if (filterValues == 0 || filterValues == false) {
            units.erase(units.begin() + i);
        }
    }
}

std::vector<Trait *> assignTraits(std::vector<std::vector<std::string>> traits) {
    std::vector<Trait *> all_traits;

    //  Iterate Rows
    // `trait.size()` has been subtracted by 1 due to fix poor parsing code.
    for (size_t i = 1; i < traits.size() - 1; i++) {
        std::string trait_id = traits.at(i).at(0);
        std::vector<int> trait_threshold;

        // Iterate Columns
        for (size_t j = 1; j < traits.at(i).size(); j++) {
            trait_threshold.push_back(std::stoi(traits.at(i).at(j)));
        }

        Trait * tmp_trait = new Trait(trait_id, trait_threshold);
        all_traits.push_back(tmp_trait);
    }
    return all_traits;
}

// For a given trait, calculates the partial and total score.
std::tuple<int, int> findTraitThreshold(std::vector<int> traitThreshold, int teamTraitTotal) {
    for (int i = 0; i < traitThreshold.size(); i++) {
        // Condition Two: Perfect
        if (teamTraitTotal == traitThreshold.at(i)) {
            return std::make_tuple(traitThreshold.at(i), i);
        }

        // Condition Three: Partial
        if ((i > 0) && (teamTraitTotal > traitThreshold.at(i-1)) && (teamTraitTotal < traitThreshold.at(i))) {
            return std::make_tuple(traitThreshold.at(i), i - 1);
        }
    }

    // Condition One: No Traits
    return std::make_tuple(traitThreshold.at(0), -1);
    // return std::make_tuple(traitThreshold.at(0), traitThreshold.at(0) - teamTraitTotal);
}

// For a given trait, calculates the partial and total score.
std::map<std::string, int> calculateTraitThreshold(std::tuple<int, int> tuple, int total) {
    int traitThreshold = std::get<0>(tuple);
    int traitIndex = std::get<1>(tuple);
    int traitTotal;
    int traitPartial;

    // Condition One: Perfect
    if (total == traitThreshold) {
        traitTotal = traitIndex + 1;
        traitPartial = 0;

    // Condition Three: None
    } else if (traitIndex == -1) {
        traitTotal = 0;
        traitPartial = total;

    // Condition Two: Partial
    } else {
        traitTotal = traitIndex + 1;
        traitPartial = traitThreshold - total;
    }

    std::map<std::string, int> traitResults;
    traitResults["Trait"] =  total;
    traitResults["Threshold"] = traitThreshold;
    traitResults["Total"] = traitTotal;
    traitResults["Partial"] = traitPartial;
    
    return traitResults;
}

// The purpose of this class is to perform calculations for "Team Traits".
// This will calculate `partialTraits`, `perfectTraits`, `totalTraits`, `teamCostAvg`,
// etc,...
// The class will be initialized with `currentTeamTraits` and the `subsetTraitMap`
std::map<std::string, std::map<std::string, int>> calculateTeamTotals(std::unordered_map<std::string, int> currentTeamTraits, const TraitStruct & trait_data) {
    // A mapping between `totalTraits`, `partialTraits`, `perfectTraits` and `teamAvgCost`.
    std::map<std::string, std::map<std::string, int>> teamTotals;

    // Itreate `currentTeamTraits`
    for (auto it : currentTeamTraits) {
        // `it.first` is the current trait.
        // `currentTeamTraits[it.first]` is the team total for the given trait.
        // `tmp_trait` is the object containing Trait thresholds.
        Trait * tmp_trait = trait_data.get(it.first);

        // Trait Total and relative min_unit index.
        std::tuple<int, int> find_trait_threshold = findTraitThreshold(tmp_trait -> getTraitThreshold(), currentTeamTraits[it.first]);
        std::map<std::string, int> team_trait_score = calculateTraitThreshold(find_trait_threshold, currentTeamTraits[it.first]);
        teamTotals[it.first] = team_trait_score;

    }
    
    return teamTotals;
}

std::map<std::string, int> scoreTeamTotals(std::map<std::string, std::map<std::string, int>> teamTotals) {
    int partialTotal = 0;
    int totalTotal = 0;
    std::map<std::string, int> finalTeamTotal;

    // Iterate `Traits`
    for (auto & trait : teamTotals) {
        partialTotal += trait.second["Partial"];
        totalTotal += trait.second["Total"];

    }

    finalTeamTotal["Total"] = totalTotal;
    finalTeamTotal["Partial"] = partialTotal;

    return finalTeamTotal;
}

// Output data to csv format.
void OutputCSV(std::string path, std::vector<Team *> final_teams) {
    // Column Names
    std::vector<std::string> col_names = {"TeamID", "Unit", "Tier", "Partial_Traits", "Total_Traits", "Traits"};

    // Open CSV
    std::ofstream file(path);

    // Create Column Headers
    for (size_t i = 0; i < col_names.size(); i++) {
        file << col_names.at(i);
        if (i < col_names.size() - 1) file << ", ";
    }
    file << "\n";

    // Iterate data from saved teams.
    for (size_t i = 0; i < final_teams.size(); i++) {
        // Save Units to vector
        std::vector<Unit *> team_units = final_teams.at(i) -> getTeam();

        // Iterate Units belonging to team.
        for (size_t j = 0; j < team_units.size(); j++) {
            file << final_teams.at(i) -> GetTeamNumber() << ", "; // Team Number
            file << team_units.at(j) -> getName() << ", ";  // Unit Name
            file << team_units.at(j) -> getTier() << ", ";  // Unit Tier
            file << final_teams.at(i) -> GetTeamPartialScore() << ", "; // Team Partial Score
            file << final_teams.at(i) -> GetTeamTotalScore() << ", "; // Team Total Score

            // Combine Unit traits into string.
            std::vector<std::string> unit_traits = team_units.at(j) -> getTraits();
            std::string concat_traits = unit_traits.at(0);
            for (size_t k = 1; k < unit_traits.size(); k++) {
                concat_traits += "_";
                concat_traits += unit_traits.at(k);
            }

            file << concat_traits << "\n"; // Concatenated Traits
        }
    }
}

// Output data as txt format.
void OutputTXT(std::string path, std::vector<Team *> final_teams) {
    // Open a file in write mode
    std::ofstream file(path);

    // Save the original buffer of std::cout
    std::streambuf* orig_cout_streambuf = std::cout.rdbuf();

    // Redirect std::cout's buffer to the file
    std::cout.rdbuf(file.rdbuf());

    // Call the function that writes to the console
    for (auto & x : final_teams) {
        x -> finalTeamDisplay();
    }

    // Restore the original buffer of std::cout
    std::cout.rdbuf(orig_cout_streambuf);

    // Close the file
    file.close();
}
