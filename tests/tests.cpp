#include <tests.h>

// std::map<std::string, int> UnitID_to_index(Units * units) {

// }


Team * GetTestTeam() {
    // Load User Data
    struct init {
        std::string path_to_units = "Data/Set10/Units_v02.csv";
        std::string path_to_traits = "Data/Set10/Traits_v02.csv";
    };

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

    // Create a mapping between units and their index.
    std::map<std::string, int> UnitID_to_index;
    for (size_t i = 0; i < Units.size(); i++) {
        UnitID_to_index[Units.at(i) -> getName()] = i;
    }

    std::vector<std::string> tmp = {"Gragas", "Gnar", "Ekko", "Bard", "Lulu"};
    std::vector<Unit *> tmp_units;
    for (auto & it : tmp) {
        tmp_units.push_back(Units.at(UnitID_to_index[it]));
    }

    Team * tmp_team = new Team(tmp_units);
    std::map<std::string, std::map<std::string, int>> team_totals = calculateTeamTotals(tmp_team -> getTraitCount(), traitStruct);
    std::map<std::string, int> team_score = scoreTeamTotals(team_totals);
    tmp_team -> setTeamTotal(team_totals);
    tmp_team -> setTeamTotalScore(team_score);

    return tmp_team;
}

void testDisplay() {
    // // Load User Data
    // struct init {
    //     std::string path_to_units = "Data/Set10/Units_v02.csv";
    //     std::string path_to_traits = "Data/Set10/Traits_v02.csv";
    // };

    // init in;

    //  // Parse Data
    // ParseCSV * csv = new ParseCSV(); 
    // std::vector<std::vector<std::string>> UnitData = csv -> parseData(in.path_to_units);
    // std::vector<std::vector<std::string>> TraitData = csv -> parseData(in.path_to_traits);
    // delete csv;

    // // Create Unit Objects
    // std::vector<Unit *> Units = assignUnits(UnitData);

    // // Create Trait Object and assign to data structure
    // std::vector<Trait *> Traits = assignTraits(TraitData);
    // TraitStruct traitStruct;
    // traitStruct.parse(Traits);

    // // Create a mapping between units and their index.
    // std::map<std::string, int> UnitID_to_index;
    // for (size_t i = 0; i < Units.size(); i++) {
    //     UnitID_to_index[Units.at(i) -> getName()] = i;
    // }

    // std::vector<std::string> tmp = {"Gragas", "Gnar", "Ekko", "Bard", "Lulu"};
    // std::vector<Unit *> tmp_units;
    // for (auto & it : tmp) {
    //     tmp_units.push_back(Units.at(UnitID_to_index[it]));
    // }

    // Team * tmp_team = new Team(tmp_units);
    // std::map<std::string, std::map<std::string, int>> team_totals = calculateTeamTotals(tmp_team -> getTraitCount(), traitStruct);
    // std::map<std::string, int> team_score = scoreTeamTotals(team_totals);
    // tmp_team -> setTeamTotal(team_totals);
    // tmp_team -> setTeamTotalScore(team_score);
    // tmp_team -> finalTeamDisplay();
}

void testOutputCSV(std::string output) {
    std::vector<std::string> col_names = {"A", "B", "C"};
    std::vector<std::vector<int>> data = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        std::ofstream file(output);

        for (size_t i = 0; i < col_names.size(); i++) {
            file << col_names.at(i);
            if (i < col_names.size() - 1) file << ", ";
        }
        file << "\n";

        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << ", "; // Don't add a comma at the end of the line
            }
            file << "\n"; // End of row
        }

        file.close();
}

void OutputCSV_test(std::string path, std::vector<Team *> final_teams) {
    // Column Names
    std::vector<std::string> col_names = {"TeamID", "Unit", "Tier", "Partial_Traits", "Total_Traits", "Traits"};

    // Open CSV
    std::ofstream file(path);

    // Create Column Headers
    for (size_t i = 0; i < col_names.size(); i++) {
        file << col_names.at(i);
        if (i < col_names.size() - 1) file << ", ";
    }
    file << "\n";

    // Iterate data from saved teams.
    for (size_t i = 0; i < final_teams.size(); i++) {
        // Save Units to vector
        std::vector<Unit *> team_units = final_teams.at(i) -> getTeam();

        // Iterate Units belonging to team.
        for (size_t j = 0; j < team_units.size(); j++) {
            file << final_teams.at(i) -> GetTeamNumber() << ", "; // Team Number
            file << team_units.at(j) -> getName() << ", ";  // Unit Name
            file << team_units.at(j) -> getTier() << ", ";  // Unit Tier
            file << final_teams.at(i) -> GetTeamPartialScore() << ", "; // Team Partial Score
            file << final_teams.at(i) -> GetTeamTotalScore() << ", "; // Team Total Score

            // Combine Unit traits into string.
            std::vector<std::string> unit_traits = team_units.at(j) -> getTraits();
            std::string concat_traits = unit_traits.at(0);
            for (size_t k = 1; k < unit_traits.size(); k++) {
                concat_traits += "_";
                concat_traits += unit_traits.at(k);
            }

            file << concat_traits << "\n"; // Concatenated Traits
        }
    }
}

// #include <fstream>
// #include <streambuf>
void OutputTXT_test(std::string path, std::vector<Team *> final_teams) {
    // Open a file in write mode
    std::ofstream file(path);

    // Save the original buffer of std::cout
    std::streambuf* orig_cout_streambuf = std::cout.rdbuf();

    // Redirect std::cout's buffer to the file
    std::cout.rdbuf(file.rdbuf());

    // Call the function that writes to the console
    for (auto & x : final_teams) {
        x -> finalTeamDisplay();
    }

    // Restore the original buffer of std::cout
    std::cout.rdbuf(orig_cout_streambuf);

    // Close the file
    file.close();
}

int main() {
    Team * test_team = GetTestTeam();
    std::vector<Team *> test_final = {test_team, test_team};

    test_team -> SetTeamNumber(1);
    // test_team -> finalTeamDisplay();

    // OutputCSV_test("tests/out/test_data.csv", test_final);

    OutputTXT_test("tests/out/test_data.txt", test_final);


    // testDisplay();

    return 0;
}