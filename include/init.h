// init.h
#ifndef INIT_H
#define INIT_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

struct init {
    std::string path_to_units = "Data/Set10/Units_v02.csv";
    std::string path_to_traits = "Data/Set10/Traits_v02.csv";
/**
     * =====================================
     *      Save Output to file
     * =====================================
     *      Enable:     1   ||  true
     * -------------------------------------
     *      Disable:    0   ||  false
     * =====================================
     * */
	// bool saveOutput = 1;
	// std::string fileName = "L5_cringe";
	/**
     * =====================================
     *      Save Output to file
     * =====================================
     *      Enable:     1   ||  true
     * -------------------------------------
     *      Disable:    0   ||  false
     * =====================================
     * */
	// bool createData = 1;
	// std::string CsvFileName = "L5.csv";

	/**
	 * =====================================
	 *      Subset Option: Cost
	 * =====================================
	 *      Enable:     1   ||  true
	 * -------------------------------------
	 *      Disable:    0   ||  false
	 * =====================================
	 * */
	bool oneCost = 1;
    bool twoCost = 1;
    bool threeCost = 1;
    bool fourCost = 0;
    bool fiveCost = 0;
    std::vector<bool> filter = {oneCost, twoCost, threeCost, fourCost, fiveCost};


	/**
	 * =======================================================================
	 *      Filter Option: Team Size & Minimum Alliance
	 * =======================================================================
	 *      teamSize        =   Number of units 
	 * -----------------------------------------------------------------------
	 *      minAlliances    =   Ignores teams below minimum set alliance
	 * -----------------------------------------------------------------------
	 *      perfAlliances   =   Ignores teams that have ANY partial alliances
	 * =======================================================================
	 * */
    int teamSize = 4;

    int minAlliances = 1;    // Minimum Partial alliances
    // bool perfAlliances = 1; // Enable: 1 || true // Disable: 0 || false

    void displayConfig() {
        std::cout << "<><> Team Info <><>" << std::endl;
        std::cout << "Team Size: " << teamSize << std::endl;
        std::cout << "Min. Partial Trait: " << minAlliances << std::endl;
        std::cout << std::endl;

        std::vector<std::string> tiers = {"one", "two", "three", "four", "five"};
        std::cout << "<><> Unit Tier <><>" << std::endl;
        for (size_t i = 0; i < filter.size(); i++) {
            std::cout << tiers.at(i) << "\t" << filter.at(i) << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif // INIT_H