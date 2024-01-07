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
        for (const auto &token : lineData)
        {
            column.push_back(token);
        }
        row.push_back(column);
    }

    return (row);
}

ParseCSV::ParseCSV() {
}

ParseCSV::~ParseCSV() {

}