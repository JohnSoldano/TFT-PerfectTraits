// main.cpp
#include <init.h>
#include <ParseCSV.h>
#include <global.h>
#include <ctime>
#include <algorithm>

int main() {
    // Load User Data
    init in;

    // Parse Data
    ParseCSV * csv = new ParseCSV(); 
    std::vector<std::vector<std::string>> UnitData = csv -> parseData(in.path_to_units);
    std::vector<std::vector<std::string>> TraitData = csv -> parseData(in.path_to_traits);
    delete csv;

    // Create Unit Objects
    std::vector<Unit *> Units = assignUnits(UnitData);

    // Create Trait Object and assign to data structure
    std::vector<Trait *> Traits = assignTraits(TraitData);
    TraitStruct traitStruct;
    traitStruct.parse(Traits);
    // Trait * obj = traitStruct.get("Deadeye");

    // Filter Units by config
    filterUnits(Units, in);

    in.displayConfig();

    // begin timer
    const clock_t begin_time = clock();

    // count number of combinations
    int count = 0;
    int K = in.teamSize;
    int N = Units.size();
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N - K trailing 0's

    do {
        // temporary vector containing champion indexes
        // std::vector<int> y;
        std::vector<Unit *> tmp_units;

        // create combination of champions
        for (int i = 0; i < N; i++) { // [0..N-1] integers
            if (bitmask[i]) {
                tmp_units.push_back(Units.at(i));
                // y.push_back(i);
            }
        }

        // Create a tmp team..
        Team * tmp_team = new Team(tmp_units);
        
        // Get Team Trait Total...
        std::map<std::string, std::map<std::string, int>> team_totals = calculateTeamTotals(tmp_team -> getTraitCount(), traitStruct);
        std::map<std::string, int> team_score = scoreTeamTotals(team_totals);

        tmp_team -> setTeamTotal(team_totals);
        tmp_team -> setTeamTotalScore(team_score);
        // tmp_team -> finalTeamDisplay();

        if (team_score["Partial"] <= in.minAlliances) {
            // std::vector<Team *> Z = 
            tmp_team -> finalTeamDisplay();
        }
        // display waiting message for long computation time
        count++;
        if (count % 100000 == 0) {
            std::cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
            std::cout << ": Thinking..." << std::endl;
        }

        // Delete the dynamically allocated objects
        // for (Unit * obj : tmp_units) {
        //     delete obj;
        // }

        delete tmp_team;

    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return 0;
}