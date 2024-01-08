// Team.h

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
#include "unordered_map"
#include "map"
#include "numeric"

// This class is a collection of `Unit`'s (a team).
class Team {
    private:
        std::vector<Unit *> team;
        std::unordered_map<std::string, int> trait_count;
        std::map<std::string, std::map<std::string, int>> team_totals;
        std::map<std::string, int> team_total_score;
        int team_number;

        void dumbTableThing() {
            std::cout << "++================================++" << std::endl;
        }

        // Count the no. times a trait appears in a team.
        std::unordered_map<std::string, int> countTraits(std::vector<Unit *> t);

        // Calculates team avg cost. This should only be called for
        // teams satisfying pass conditions.
        double getAvgCost();
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

        // Assigns a number to the team.
        void SetTeamNumber(int x) { team_number = x; }

        // Returns team number
        int GetTeamNumber() { return team_number; }

        // Return Partial score for the team
        int GetTeamPartialScore() { return team_total_score["Partial"]; }

        // Returns total score for team.
        int GetTeamTotalScore() { return team_total_score["Total"]; }
};
#endif // TEAM_H