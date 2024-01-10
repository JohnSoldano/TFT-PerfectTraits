#include "CombController.h"

CombController::CombController(int n, int k) {
    _n = n;
    _k = k;

    CombController::nChooseK(n, k);
}

CombController::~CombController() {

}

std::vector<Team> CombController::FindTeams(std::vector<Unit *> units, const TraitStruct & traits, init in) {
    // begin timer
    const clock_t begin_time = clock();

    int count = 0;
    std::string bitmask(_k, 1); // K leading 1's
    bitmask.resize(_n, 0); // N - K trailing 0's

    std::vector<Team> final_teams;

    do {
        // temporary vector containing units
        std::vector<Unit *> tmp_units;

        // create combination of unit indexes
        for (int i = 0; i < _n; i++) { // [0..N-1] integers
            if (bitmask[i]) {
                tmp_units.push_back(units.at(i));
            }
        }

        // Create a tmp team..
        Team * tmp_team = new Team(tmp_units);
        
        // Get Team Trait Total...
        std::map<std::string, std::map<std::string, int>> team_totals = CombController::calculateTeamTotals(tmp_team -> getTraitCount(), traits);
        std::map<std::string, int> team_score = CombController::scoreTeamTotals(team_totals);

        tmp_team -> setTeamTotal(team_totals);
        tmp_team -> setTeamTotalScore(team_score);

        // Add more conditions here for valid teams.
        if (team_score["Partial"] <= in.minAlliances) {
            tmp_team -> SetTeamNumber(final_teams.size() + 1);
            tmp_team -> finalTeamDisplay();

            // Convert pointer to object for returning..
            Team tmp_team2 = * tmp_team;
            final_teams.push_back(tmp_team2);
        }

        // display waiting message for long computation time
        count++;
        if (count % 100000 == 0) {
            std::cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
            std::cout << ": Thinking..." << std::endl;
        }

        delete tmp_team;

    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return final_teams;
}