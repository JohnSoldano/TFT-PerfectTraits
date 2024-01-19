// TeamController.h

/*
    This class will calculate combinations passing teams...
*/
#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include "TraitController.h"
#include "Team.h"

class TeamController {
    private:
        int total_team_counter;
        std::vector<Team> final_teams;
        int min_partial_traits;
    public:
        TeamController(int minimum_partial_traits) : total_team_counter(1), final_teams(), min_partial_traits(minimum_partial_traits) { }

        ~TeamController() {}

        // Add team, assign no., increment counter.
        void addTeam(Team * team) {
            Team tmp_team = * team;
            tmp_team.setTeamNumber(total_team_counter); // Set 
            total_team_counter++; // Increment counter
            final_teams.push_back(tmp_team); // Add final team
            // tmp_team.finalTeamDisplay(); // Display passing team
        }

        // Verify team passing conditions for saving..
        void scoreTeam(Team * team) {
            auto team_partial_traits = team -> getTraitCount();

            // Add more conditions here for valid teams.
            if (team_partial_traits["Partial"] <= min_partial_traits) {
                addTeam(team);
            }
        }
        // Returns all teams
        std::vector<Team> GetAllTeams() { return final_teams; }
};

#endif // TEAMCONTROLLER_H