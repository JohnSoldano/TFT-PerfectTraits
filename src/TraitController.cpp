// TraitController.cpp
#include "TraitController.h"

// This will calculate `partialTraits`, `perfectTraits`, `totalTraits`, `teamCostAvg`,
// etc,...
// The class will be initialized with `currentTeamTraits` and the `subsetTraitMap`
std::map<std::string, int> TraitController::calculateTeamTotals(std::unordered_map<std::string, int> team_traits) {
    //A mapping between `totalTraits`, `partialTraits`, `perfectTraits` and `teamAvgCost`.
    std::map<std::string, std::map<std::string, int>> team_trait_totals;

    // Itreate `currentTeamTraits`
    for (auto it : team_traits) {
        // `it.first` is the current trait.
        // `currentTeamTraits[it.first]` is the team total for the given trait.
        // `tmp_trait` is the object containing Trait thresholds.
        auto current_trait = trait_map.at(it.first);

        // Find the trait threshold for the current team
        auto current_trait_threshold = findTraitThreshold(current_trait -> getTraitThreshold(), team_traits[it.first]);
        
        // Create score?
        auto current_team_score = calculateTraitThreshold(current_trait_threshold, team_traits[it.first]);

        // Save trait result for the team
        team_trait_totals[it.first] = current_team_score;

    }

    // Mapping for partial traits and full traits
    auto team_totals =  scoreTeamTotals(team_trait_totals);
    
    return team_totals;
}

