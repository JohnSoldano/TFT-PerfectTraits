#include "CombController.h"

CombController::CombController(int n, int k) {
    _n = n;
    _k = k;

    CombController::nChooseK(n, k);
}

CombController::~CombController() {

}

std::vector<Team> CombController::FindTeams(std::vector<Unit *> units, TraitController::TraitStruct traits, init in) {
    int count = 0;
    const clock_t begin_time = clock();
    std::vector<Team> final_teams;
    std::vector<int> combination(_k);

    // Initialize the first combination to be 0, 1, 2, ..., k-1
    for (int i = 0; i < _k; ++i) {
        combination[i] = i;
    }

    // After first combination, iterate through remaining combinations
    while (true) {
        // Team stuff here
        std::vector<Unit *> tmp_units;

        // Iterate combination adding team
        for (const auto & it : combination) {
            tmp_units.push_back(units.at(it));
        }

        // Scopre team 
        Team * tmp_team = new Team(tmp_units);
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

        // Generate the next combination
        int i;
        for (i = _k - 1; i >= 0 && combination[i] == i + _n - _k; --i);
        if (i < 0) break; // All combinations generated

        combination[i]++;
        for (int j = i + 1; j < _k; ++j) {
            combination[j] = combination[j - 1] + 1;
        }

        count++;
        if (count % 100000 == 0) {
            std::cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
            std::cout << ": Thinking..." << std::endl;
        }

    }
    
    return final_teams;
}