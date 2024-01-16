// parseCSV.cpp
#include "parseCSV.h"

std::vector<std::string> ParseCSV::getNextLineAndSplitIntoTokens(std::istream &str) {
    std::vector<std::string> result;
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }
    if (!lineStream && cell.empty()) {
        result.push_back("");
    }
    return result;
}


std::vector<std::vector<std::string>> ParseCSV::parseData(std::string p) {
    std::ifstream file(p);
    std::vector<std::vector<std::string>> row;
    while (file) {
        std::vector<std::string> column;

        std::vector<std::string> lineData = ParseCSV::getNextLineAndSplitIntoTokens(file);
        for (const auto &token : lineData) {
            column.push_back(token);
        }
        row.push_back(column);
    }

    return (row);
}

void ParseCSV::assignUnits(std::vector<std::vector<std::string>> x) {
            // create traits vec
            // 0th column = character_id
            // 1st column = tier
            // 2nd to Inf = traits
            int unit_index = 0;
            int tier_index = 1;
            int trait_index = 2;

            // Ignore column headers
            for (int i = 1; i < x.size() - 1; i++) { 

                // Temporary row containing info
                auto U = x[i];
                int row_len = U.size();

                // Create vector of traits
                std::vector<std::string> traits;
                for (int k = trait_index; k < row_len; k++) {
                    traits.push_back(U.at(k));
                }

                // Create Unit obj
                Unit * myUnit = new Unit(U.at(unit_index), std::stoi(U.at(tier_index)),  traits);
                all_units.push_back(myUnit); // Save 
            }
        }

void ParseCSV::assignTraits(std::vector<std::vector<std::string>> x) {
    int traitID_index = 0;
    int trait_index = 1;
    //  Iterate Rows
    // Ignore Headers
    for (size_t i = 1; i < x.size() - 1; i++) {
        std::string trait_id = x.at(i).at(traitID_index);
        std::vector<int> trait_threshold;

        // Iterate Columns
        for (int j = trait_index; j < x.at(i).size(); j++) {
            trait_threshold.push_back(std::stoi(x.at(i).at(j)));
        }

        Trait * tmp_trait = new Trait(trait_id, trait_threshold);
        all_traits.push_back(tmp_trait);
    }
}

ParseCSV::ParseCSV() {
}

ParseCSV::ParseCSV(std::vector<std::string> x) {

}

ParseCSV::ParseCSV(std::string x) {
    std::ifstream jsonInputStream(x);
    nlohmann::json json;
    jsonInputStream >> json;

    // parse unit data
    assignUnits(parseData(json["path_to_units"][0]));
    assignTraits(parseData(json["path_to_traits"][0]));

}

ParseCSV::~ParseCSV() {

}
