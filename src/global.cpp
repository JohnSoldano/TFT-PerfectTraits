#include "global.h"


// Output data to csv format.
void OutputCSV(std::string path, std::vector<Team> final_teams) {
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
        std::vector<Unit *> team_units = final_teams.at(i).getTeam();

        // Iterate Units belonging to team.
        for (size_t j = 0; j < team_units.size(); j++) {
            file << final_teams.at(i).GetTeamNumber() << ", "; // Team Number
            file << team_units.at(j) -> getName() << ", ";  // Unit Name
            file << team_units.at(j) -> getTier() << ", ";  // Unit Tier
            file << final_teams.at(i).GetTeamPartialScore() << ", "; // Team Partial Score
            file << final_teams.at(i).GetTeamTotalScore() << ", "; // Team Total Score

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

// Output data as txt format.
void OutputTXT(std::string path, std::vector<Team> final_teams) {
    // Open a file in write mode
    std::ofstream file(path);

    // Save the original buffer of std::cout
    std::streambuf* orig_cout_streambuf = std::cout.rdbuf();

    // Redirect std::cout's buffer to the file
    std::cout.rdbuf(file.rdbuf());

    // Call the function that writes to the console
    for (auto & x : final_teams) {
        x.finalTeamDisplay();
    }

    // Restore the original buffer of std::cout
    std::cout.rdbuf(orig_cout_streambuf);

    // Close the file
    file.close();
}
