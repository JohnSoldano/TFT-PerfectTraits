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
#include <init.h>
#include <ParseCSV.h>
#include <global.h>
#include <ctime>
#include <algorithm>
#include "CombController.h"

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
    
    // Find final teams.
    CombController * combCtrl = new CombController(Units.size(), in.teamSize);

    // Remove this later
    std::cout << combCtrl -> Get_nCk_size() << std::endl; // Reminder...

    // Output to console
    in.displayConfig();

    // Return Passing teams in a vector
    std::vector<Team> final_teams = combCtrl -> FindTeams(Units, traitStruct, in);

    // Save output
    OutputTXT("results/TEST_A.txt", final_teams);
    OutputCSV("results/TEST_A.csv", final_teams);

    return 0;
}