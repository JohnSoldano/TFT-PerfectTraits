// main.cpp
/*
    +===========+
    +   To Do   +
    +===========+
        *   2024/01/08 - A memory error occurs when iterating unit permutations. This error does not occur when calling `delete obj` after each iteration. 
                `delete obj` has the unintend effect of removing reference to the object satisfying the conditions needed for storing.
                A possible (unconfirmed) solution is to replace std::vector<Obj *> myVector with std::vector<std::unique_ptr<Obj> myVector.

        *   2024/01/08 - Create a global(?) function to perform unit permutation calculation. This large section of code must be removed from main().
                The function will be of type std::vector<std::unique_ptr<Team>> containing team permutations satisfying strict conditions. 
                This can then be passed to `OutputTXT` and `OutputCSV`.

        *   2024/01/08 - Calculate how many possibile team compositions. At a fixed interval (TBD), display number of combinations remaining, percentage complete and 
                current processing time. Update time from seconds to days, hours, minutes, seconds. This will replace the output `Thinking` which is displayed 
                every 100,000 iterations and displays the number of seconds past. 

        *   2024/01/08 - Automatically create <B><U>meaningful<\U><\B> names for output data. The naming convention (TBD) will be returned from `init.h`.

        *   2024/01/08 - Generate config (is this the correct word?) to update `init.h` with preset conditions. Once completed, 
                this program will only need to run once at the beginning of each set.
                i.e., config001 max units 4, cost 1 2 3, no partial traits.
                config025 max units 7, cost 1 2 3 4, no partial traits.
                config026 max units 9, cost 1 2 3 4 5, no partial traits (> 24 hrs).

        *   2024/01/08 - Replace global.h and global.cpp with better (unknown) data structure.

        *   2024/01/08 - Solve problems installing `googletest` and `Boost` for unit testing (cmake).
                Note: `googletest` unable to compile due to missing header file(s).
                Note: `Boost` unable to install, this had something to do with installing using CL Microsoft compiler. MS Visual Studio has since been installed,
                status of CL unconfirmed.

        *   2024/01/08 - Analyze memory allocation: consider `gperftools` and `Visual Studio Diagnostic Tools`. (??)
*/ 
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
    
    // Filter Units by config
    filterUnits(Units, in);

    // Save passing teams.
    std::vector<Team *> final_teams;
    
    // Display stuffo
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
        std::vector<Unit *> tmp_units;

        // create combination of champions
        for (int i = 0; i < N; i++) { // [0..N-1] integers
            if (bitmask[i]) {
                tmp_units.push_back(Units.at(i));
            }
        }

        // Create a tmp team..
        Team * tmp_team = new Team(tmp_units);
        
        // Get Team Trait Total...
        std::map<std::string, std::map<std::string, int>> team_totals = calculateTeamTotals(tmp_team -> getTraitCount(), traitStruct);
        std::map<std::string, int> team_score = scoreTeamTotals(team_totals);

        tmp_team -> setTeamTotal(team_totals);
        tmp_team -> setTeamTotalScore(team_score);

        // Add more conditions here for valid teams.
        if (team_score["Partial"] <= in.minAlliances) {
            tmp_team -> finalTeamDisplay();
            tmp_team -> SetTeamNumber(final_teams.size() + 1);
        }

        // display waiting message for long computation time
        count++;
        if (count % 100000 == 0) {
            std::cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
            std::cout << ": Thinking..." << std::endl;
        }

        delete tmp_team;

    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    // OutputTXT("results/TEST_A.txt", final_teams);
    // OutputCSV("results/TEST_A.csv", final_teams);

    return 0;
}