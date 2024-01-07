// Team.h
#ifndef TEAM_H
#define TEAM_H

#include "Unit.h"
#include "unordered_map"
#include "map"

// This class is a collection of `Unit`'s (a team).
class Team {
    private:
        std::vector<Unit *> team;
        std::unordered_map<std::string, int> trait_count;
        std::map<std::string, std::map<std::string, int>> team_totals;
        std::map<std::string, int> team_total_score;

        void dumbTableThing() {
            std::cout << "++================================++" << std::endl;
        }

        // Count the no. times a trait appears in a team.
        std::unordered_map<std::string, int> countTraits(std::vector<Unit *> t);
    public:
        Team(std::vector<Unit *> units);
        ~Team();

        // Return counts of traits.
        std::unordered_map<std::string, int> getTraitCount() { return trait_count; }
        
        // Return Team Object
        std::vector<Unit *> getTeam() { return team; }

        // Set the teamTotals Data
        void setTeamTotal(std::map<std::string, std::map<std::string, int>> x) { team_totals = x; }
        
        void setTeamTotalScore(std::map<std::string, int> x) { team_total_score = x; }

        // Display Team
        void displayTeam();

        // Show formatted trait count
        void displayCounts();

        // Display Final Team Data.
        void finalTeamDisplay();
};
#endif // TEAM_H