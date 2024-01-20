// Team.h
// 1) std::map<std::string, std::map<std::string, int>> team_totals = CombController::calculateTeamTotals(tmp_team -> getTraitCount(), traits);
//  2) std::map<std::string, int> team_score = CombController::scoreTeamTotals(team_totals);
//  3) tmp_team -> setTeamTotal(team_totals);
//  4) tmp_team -> setTeamTotalScore(team_score);
//  5) tmp_team -> SetTeamNumber(final_teams.size() + 1); // Increment automatically
/*
    +===========+
    +   To Do   +
    +===========+
        *   2024/01/08 - Calculate team average. (Completed: 2024/01/08)

        *   <>
*/ 
#ifndef TEAM_H
#define TEAM_H

#include "Unit.h"
#include "Trait.h"
#include "TraitController.h"
#include <unordered_map>
#include <map>
#include <numeric>
#include <tuple>

/*
    This class is a collection of `Unit`'s (a team).
    For a given team, calculate total partial traits etc.
*/
class Team {
    private:
        std::vector<Unit *> team;
        std::unordered_map<std::string, Trait *> & trait_mapping;

        std::unordered_map<std::string, int> trait_count;
        std::map<std::string, std::map<std::string, int>> team_totals;
        std::map<std::string, int> team_total_score;
        std::map<std::string, std::tuple<int, int>> team_trait_threshold;
        std::tuple<int, int> trait_threshold;
        int team_number;

        void dumbTableThing() {
            std::cout << "++================================++" << std::endl;
        }

        // Count the no. times a trait appears in a team.
        std::unordered_map<std::string, int> countTraits(std::vector<Unit *> t);

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

        // Final score?
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

        void calculateTeamTotals(std::unordered_map<std::string, int> team_traits) {
            //A mapping between `totalTraits`, `partialTraits`, `perfectTraits` and `teamAvgCost`.
            std::map<std::string, std::map<std::string, int>> team_trait_totals;
            std::map<std::string, std::tuple<int, int>> team_trait_threshold;

            // Itreate `currentTeamTraits`
            for (auto it : team_traits) {
                // `it.first` is the current trait.
                // `currentTeamTraits[it.first]` is the team total for the given trait.
                // `tmp_trait` is the object containing Trait thresholds.
                auto current_trait = trait_mapping.at(it.first);

                // Find the trait threshold for the current team
                auto current_trait_threshold = findTraitThreshold(current_trait -> getTraitThreshold(), team_traits[it.first]);
                
                // Create score?
                auto current_team_score = calculateTraitThreshold(current_trait_threshold, team_traits[it.first]);

                // Save trait result for the team
                team_trait_totals[it.first] = current_team_score;
                team_trait_threshold[it.first] = current_trait_threshold;

            }       

            // Mapping for partial traits and full traits
            auto team_totals =  scoreTeamTotals(team_trait_totals);
            setTeamTotalScore(team_totals);
            setTeamTotal(team_trait_totals);
            setTeamThreshold(team_trait_threshold);
        }

        // Calculates team avg cost. This should only be called for
        // teams satisfying pass conditions.
        double getAvgCost();
    public:
        // A team is created from a vector containing Unit.
        // Team total traits are counted on creation.
        Team(std::vector<Unit *> units, std::unordered_map<std::string, Trait *> & trait_map);
        ~Team();

        // Return counts of traits.
        std::unordered_map<std::string, int> getTraitCount() { return trait_count; }
        
        // Return Team Object
        std::vector<Unit *> getTeam() { return team; }

        // Set the teamTotals Data
        void setTeamTotal(std::map<std::string, std::map<std::string, int>> x) { team_totals = x; }
        
        void setTeamTotalScore(std::map<std::string, int> x) { team_total_score = x; }

        void setTeamNumber(int x) { team_number = x; }

        void setTeamThreshold(std::map<std::string, std::tuple<int, int>> x) { team_trait_threshold = x; }

        // Display Team
        void displayTeam();

        // Show formatted trait count
        void displayCounts();

        // Display Team Thresholds for a given team..
        void displayTeamThresholds() {
            std::string trait_id;

            for (const auto & it : team_trait_threshold) {
                trait_id = it.first;


                // Trait Name
                std::cout << trait_id << ": ";

                // Sum of traits from team
                std::cout << trait_count[trait_id] << "/";

                // Trait value for the threshold
                std::cout << std::get<0>(it.second) << std::endl;
            }
        }

        // Display Final Team Data.
        void finalTeamDisplay();

        // Return Partial score for the team
        int GetTeamPartialScore() { return team_total_score["Partial"]; }

        // Returns total score for team.
        int GetTeamTotalScore() { return team_total_score["Total"]; }

        // Display Second formatted team
        void displayTeamTwo();

        // Returns assigned no. of teamID
        int GetTeamNumber() { return team_number; }

        std::map<std::string, std::tuple<int, int>> GetTraitThresholds() { return team_trait_threshold; }
};

#endif // TEAM_H