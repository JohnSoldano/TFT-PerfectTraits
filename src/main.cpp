// main.cpp
/*
    +===========+
    +   To Do   +
    +===========+
        *   [2024/01/08] - Calculate how many possibile team compositions. At a fixed interval (TBD), display number of combinations remaining, percentage complete and 
                current processing time. Update time from seconds to days, hours, minutes, seconds. This will replace the output `Thinking` which is displayed 
                every 100,000 iterations and displays the number of seconds past. 

        *   [2024/01/08] - Automatically create <B><U>meaningful<\U><\B> names for output data. The naming convention (TBD) will be returned from `init.h`.

        *   [2024/01/08] - Generate config (is this the correct word?) to update `init.h` with preset conditions. Once completed, 
                this program will only need to run once at the beginning of each set.
                i.e., config001 max units 4, cost 1 2 3, no partial traits.
                config025 max units 7, cost 1 2 3 4, no partial traits.
                config026 max units 9, cost 1 2 3 4 5, no partial traits (> 24 hrs).

        *   [2024/01/08] - Replace global.h and global.cpp with better (unknown) data structure.

        *   [2024/01/08] - Solve problems installing `googletest` and `Boost` for unit testing (cmake).
                Note: `googletest` unable to compile due to missing header file(s).
                Note: `Boost` unable to install, this had something to do with installing using CL Microsoft compiler. MS Visual Studio has since been installed,
                status of CL unconfirmed.

        *   [2024/01/08] - Analyze memory allocation: consider `gperftools` and `Visual Studio Diagnostic Tools`. (??)
    
    +===========+
    + Completed +
    +===========+
        *   [2024/01/08] - A memory error occurs when iterating unit permutations. This error does not occur when calling `delete obj` after each iteration. 
            `delete obj` has the unintend effect of removing reference to the object satisfying the conditions needed for storing.
            A possible (unconfirmed) solution is to replace std::vector<Obj *> myVector with std::vector<std::unique_ptr<Obj> myVector.

            [2024/01/10] - The implemented solution creates a copy of the object pointer to an object. This allows for the deleting of each iteration and 
            saving/returning the object.
                Obj * myObjPtr = new Obj();
                Obj myObj = * myObjPtr
    


        *   [2024/01/08] - Create a global(?) function to perform unit permutation calculation. This large section of code must be removed from main().
            The function will be of type std::vector<std::unique_ptr<Team>> containing team permutations satisfying strict conditions. 
            This can then be passed to `OutputTXT` and `OutputCSV`.
            
            [2024/01/10] - Functions from main and global that calculate scores for teams were placed into newly created class `CombController`.

*/ 


#include "init.h"

#include "UnitController.h"
#include "TraitController.h"
#include "Team.h"
#include "TeamController.h"


// #include <global.h>
// #include <ctime>
// #include <algorithm>
// #include "CombController.h"
// #include "TraitController.h"

void generateCombinationsIterative(
    int n, int k,
    std::vector<Unit *> & units,
    std::unordered_map<std::string, Trait *> & trait_controller,
    TeamController * team_controller) {
        std::vector<int> combination(k);

        // Initialize the first combination to be 0, 1, 2, ..., k-1
        for (int i = 0; i < k; ++i) {
            combination[i] = i;
        }

        

        // After first combination, iterate through remaining combinations
        while (true) {

            // Temp unit vector
            std::vector<Unit *> tmp_units;

            // Iterate through unit combinations add to temp vector
            for (const auto & it : combination) {
                tmp_units.push_back(units.at(it));
            }

            // Temporary team
            Team * tmp_team = new Team(tmp_units, trait_controller);
            
            // Score team
            team_controller -> scoreTeam(tmp_team);
    

            // Generate the next combination
            int i;
            for (i = k - 1; i >= 0 && combination[i] == i + n - k; --i);
            if (i < 0) break; // All combinations generated

            combination[i]++;
            for (int j = i + 1; j < k; ++j) {
                combination[j] = combination[j - 1] + 1;
            }

            // printCombinationIterative(combination);
        }
}

int main() {
    init in;

    // For a given path to data and filter initialize class for creating units.
    UnitController * unit_controller = new UnitController(in.path_to_units, in.filter);

    // For a given path to data and filter initialize class for creating traits.
    TraitController * trait_controller = new TraitController(in.path_to_traits);

    // Records final teams
    TeamController * team_controller = new TeamController(in.minAlliances);

    // Get Final Units
    auto Units = unit_controller -> GetAllUnits();

    // Get Final Trait Map
    auto TraitMap = trait_controller -> GetTraitMap();

    // Test team
    // std::vector<Unit *> tmp_units = {Units.at(0), Units.at(3), Units.at(36), Units.at(57)};
    // Team * tmp_team = new Team(tmp_units, TraitMap);
    // tmp_team -> finalTeamDisplay();



    generateCombinationsIterative(10, 4, Units, TraitMap, team_controller);
    auto all_teams = team_controller -> GetAllTeams();
    for (auto & it : all_teams) {
        it.finalTeamDisplay();
    }

    /*
   
    
    // Score Test Team
    team_controller -> addTeam(tmp_team);

    auto all_teams = team_controller -> GetAllTeams();

    for (auto & it : all_teams) {
        it.finalTeamDisplay();
    }
    */
    





    // Find final teams.
    // CombController * combCtrl = new CombController(Units.size(), in.teamSize);

    // Remove this later
    // std::cout << combCtrl -> Get_nCk_size() << std::endl; // Reminder...

    // Output to console
    // in.displayConfig();

    // FindTeams is broken..
    // for (const auto & it : Traits.myMap) {
    //     std::cout << it.first << ": ";
    //     for (const auto & jt : it.second -> getTraitThreshold()) {
    //         std::cout << jt << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Create final teams  
    // Return Passing teams in a vector
    // std::vector<Team> final_teams = combCtrl -> FindTeams(Units, Traits, in);

    // Save output
    // OutputTXT("results/P0_L8_12345.txt", final_teams);
    // OutputCSV("results/P0_L8_12345", final_teams);

    return 0;
}