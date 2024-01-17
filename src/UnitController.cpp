// UnitController.cpp
#include "UnitController.h"



// Default Constructor
UnitController::UnitController(std::string path_to_data, std::vector<bool> filter) : all_units() {
    // Initialize class for parsing csv
    ParseCSV parse_csv;

    // Parse csv
    auto parsed_data = parse_csv.parseData(path_to_data);

    // Converts parsed csv data into usable data structure
    assignUnits(parsed_data);

    // Filter data
    FilterUnits(filter);

}


// Default Destructor
UnitController::~UnitController() {

}