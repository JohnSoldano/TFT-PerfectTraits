// CombController.h
#ifndef COMBCONTROLLER_H
#define COMBCONTROLLER_H

#include "Unit.h"
#include "Team.h"
#include "Trait.h"
#include "init.h"
#include "global.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include "TraitController.h"
#include "ParseCSV.h"

class CombController {
    private:
        int _n;
        int _k;
        int nCk_size;

        void nChooseK(int n, int k) {
            if (k > n) nCk_size = 0;
            if (k == 0 || k == n) nCk_size = 1;
            if (k > n - k) k = n - k;  // Take advantage of symmetry, C(n, k) == C(n, n-k)

            int result = 1;
            for (int i = 0; i < k; ++i) {
                result *= (n - i);
                result /= (i + 1);
            }

            nCk_size = result;
        }
        // Display progress as a percentage and no. when calculating combinations.
        // Different thresholds for each number.
        void displayProgress() {

            // (0, 100,000]
            if (nCk_size <= 10^5) {

            }
            // (100,000, 1,000,000]
            if (nCk_size > 10^5 && nCk_size <= 10^6) {

            }

            // (1,000,000, 1,000,000,000]
            if (nCk_size > 10^6 && nCk_size <= 10^9) {

            }

            // (1,000,000,000, Inf)
            if (nCk_size > 10^9) {

            }
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
        std::map<std::string, std::map<std::string, int>> calculateTeamTotals(std::unordered_map<std::string, int> currentTeamTraits, ParseCSV::TraitStruct trait_data) {
            // A mapping between `totalTraits`, `partialTraits`, `perfectTraits` and `teamAvgCost`.
            std::map<std::string, std::map<std::string, int>> teamTotals;

            // Itreate `currentTeamTraits`
            for (auto it : currentTeamTraits) {
                // `it.first` is the current trait.
                // `currentTeamTraits[it.first]` is the team total for the given trait.
                // `tmp_trait` is the object containing Trait thresholds.
                auto tmp_trait = trait_data.get(it.first);

                // Trait Total and relative min_unit index.
                std::tuple<int, int> find_trait_threshold = CombController::findTraitThreshold(tmp_trait -> getTraitThreshold(), currentTeamTraits[it.first]);
                std::map<std::string, int> team_trait_score = CombController::calculateTraitThreshold(find_trait_threshold, currentTeamTraits[it.first]);
                teamTotals[it.first] = team_trait_score;

            }
            
            return teamTotals;
        }

        //
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

    public:
        CombController(int n, int k);
        ~CombController();

        int Get_nCk_size() { return nCk_size; }
        std::vector<Team> FindTeams(std::vector<Unit *> units, ParseCSV::TraitStruct traits, init in);
};
#endif // COMBCONTROLLER_H