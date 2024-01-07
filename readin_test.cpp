#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <unordered_map>

// g++ -o main readin_test.cpp; ./main

struct init {
    /**
     * =====================================
     *      Save Output to file
     * =====================================
     *      Enable:     1   ||  true
     * -------------------------------------
     *      Disable:    0   ||  false
     * =====================================
     * */

    /**
     * =====================================
     *      Save Output to file
     * =====================================
     *      Enable:     1   ||  true
     * -------------------------------------
     *      Disable:    0   ||  false
     * =====================================
     * */


    /**
	 * =====================================
	 *      Subset Option: Cost
	 * =====================================
	 *      Enable:     1   ||  true
	 * -------------------------------------
	 *      Disable:    0   ||  false
	 * =====================================
	 * */
    bool costOne = 1;
    bool costTwo = 1;
    bool costThree = 1;
    bool costFour = 1;
    bool costFive = 0;
    std::vector<bool> filter = {costOne, costTwo, costThree, costFour, costFive};

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
    int teamSize = 5;
    int minAlliances;
    bool perfAlliances; // Enable: 1 (true) || Disable: 0 (false)
};

class Trait {
private:
    // Attributes
    std::string Name;
    std::vector<int> MinUnits;

public:
    // Constructor
    Trait(std::string name, std::vector<int> min_units)
    {
        Name = name;
        for (auto i : min_units)
        {
            MinUnits.push_back(i);
        }
    }

    // All minimum units needed to reach trait threshold.
    std::vector<int> getMinUnits() { return MinUnits; }
};

// Class representing a single Unit.
class Unit {
private:
    std::string Name;
    int Tier;
    int Cost;
    std::vector<std::string> Traits;

public:
    // Creates a Unit.
    // Parameters:
    //      Name: The name of the unit.
    //      Tier: The tier of the unit.
    //      Cost: The cost of the unit.
    //      Traits: The associated traits for a unit.
    Unit(std::string name, int tier, std::vector<std::string> traits) {
        Name = name;
        Tier = tier;
        Cost = tier;
        for (auto i : traits) {
            Traits.push_back(i);
        }
    }

    // Returns the `Name` of the unit.
    std::string getName() { return Name; }

    // Returns the `Tier` of the unit.
    int getTier() { return Tier; }

    // Returns the `Cost` of the unit.
    int getCost() { return Cost; }

    // Returns all `Traits` of the unit.
    std::vector<std::string> getTraits() { return Traits; }

    // Display the attributes of a Unit.
    void displayInfo()
    {
        std::cout << "\nName: " << Name << std::endl;
        std::cout << "Tier: " << Tier << std::endl;
        std::cout << "Traits: ";
        for (size_t k = 0; k < Traits.size(); k++)
        {
            std::cout << Traits.at(k);
            if (k < Traits.size() - 1)
                std::cout << ", ";
            else
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

// This class is a collection of `Unit`'s (a team).It's primary purpose
// is to count the traits within the team.
class Team {
private:
    // Attibutes
    std::vector<Unit *> team;
    std::unordered_map<std::string, int> trait_count;
    std::map<std::string, std::map<std::string, int>> teamTotals;
    std::map<std::string, int> teamTotalScore;

    // CountTraits
    void countTraits()
    {
        std::vector<std::string> rawTraits;

        for (auto &x : team)
        {
            std::vector<std::string> tmpTraits = x->getTraits();

            for (auto &y : tmpTraits)
            {
                rawTraits.push_back(y);
            }
        }

        std::unordered_map<std::string, int> counts;
        // Count the occurrences of each string
        for (const auto &elem : rawTraits)
        {
            ++counts[elem];
        }

        trait_count = counts;
    }

public:
    // Constructor
    Team(std::vector<Unit *> units)
    {
        // Store Traits
        for (auto i : units)
        {
            team.push_back(i);
        }

        // Automatically Count Traits
        countTraits();
    }

    // Set the teamTotals Data
    void setTeamTotal(std::map<std::string, std::map<std::string, int>> x) {
        teamTotals = x;
    }

    void setTeamTotalScore(std::map<std::string, int> x) {
        teamTotalScore = x;
    }
    // #### Getters ####

    // Return counts of traits.
    std::unordered_map<std::string, int> getTraitCount() { return trait_count; }

    // Return Team Object
    std::vector<Unit *> getTeam() { return team; }

    // Display Team
    void displayTeam()
    {
        for (auto &it : team)
        {
            it->displayInfo();
        }
    }

    // Show formatted trait count
    void displayCounts()
    {

        // Display the counts
        for (const auto &pair : trait_count)
        {
            std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
        }
    }

    // Display Final Team Data.
    void finalTeamDisplay() {
        int num_units = team.size();
        int totalTotal = teamTotalScore["Total"];
        int totalPartial = teamTotalScore["Partial"];

        // Display Size, Traits, etcs
        std::cout << std::endl;
        std::cout << "Team Size: " << num_units << std::endl;
        std::cout << "Total Traits: " << totalTotal << std::endl;
        std::cout << "Partial Traits: " << totalPartial << std::endl;
        std::cout << std::endl;

        // Display Units...
        for (auto & t : team) {
            std::cout << t -> getName() << " (" << t -> getCost() << ")" << std::endl;
        }
        std::cout << std::endl;

        // Display Totals..
        for (auto & x : teamTotals) {
            std::cout << x.first << ": " << x.second["Trait"] << "/" << x.second["Threshold"] << std::endl;
        }
        std::cout << std::endl;
    }
};

// Remove Units from the pool via filtering config.
void filterUnits(std::vector<Unit *> & X, init in) {
    int unitCost;
    int filterValues;

    // Must go in reverse for iterative removal.
    for (int i = X.size() - 1; i >= 0; i--) {
        std::string name = X.at(i) -> getName();
        int cost = X.at(i) -> getCost();
        filterValues = in.filter.at(cost - 1);

        if (filterValues == 0 || filterValues == false) {
            X.erase(X.begin() + i);
        }
    }
}

// For 
bool isPerfectTrait(std::vector<int> min_units, int total) {
    bool isPerfect = false;
    int i = 0;
    while (!isPerfect && i < min_units.size() - 1) {
        if (min_units.at(i) == total) isPerfect = true;
        i++;
    }
    return isPerfect;
}

//
int countPartialTotal(std::vector<int> traitThreshold, int teamTraitTotal) {
    std::cout << "Current Total: " << teamTraitTotal << std::endl;

    for (int i = 0; i < traitThreshold.size(); i++) {
        int current_threshold = traitThreshold.at(i);

        if (current_threshold == teamTraitTotal) {
            std::cout << "Perfect" << std::endl;
            return i;
        }

        if (teamTraitTotal > current_threshold) {
            std::cout << "Partial" << std::endl;
        }
    }

    std::cout << "Partial 2" << std::endl;
    return 99;
}

// For a vector of `traitThreshold` and the current `teamTraitTotal`,
// return the appropriate trait threshold and its associated index.
std::tuple<int, int> findTraitThreshold(std::vector<int> traitThreshold, int teamTraitTotal) {
    for (int i = 0; i < traitThreshold.size(); i++) {
        // Condition Two: Perfect
        if (teamTraitTotal == traitThreshold.at(i)) {
            return std::make_tuple(traitThreshold.at(i), i);
        }

        // Condition Three: Partial
        if ((i > 0) && (teamTraitTotal > traitThreshold.at(i-1)) && (teamTraitTotal < traitThreshold.at(i))) {
            return std::make_tuple(traitThreshold.at(i), i - 1);
        }
    }

    // Condition One: No Traits
    return std::make_tuple(traitThreshold.at(0), -1);
}

// For a given trait, calculates the partial and total score.
std::map<std::string, int> calculateTraitThreshold(std::tuple<int, int> tuple, int total) {
    int traitThreshold = std::get<0>(tuple);
    int traitIndex = std::get<1>(tuple);
    int traitTotal;
    int traitPartial;

    // Condition One: Perfect
    if (total == traitThreshold) {
        traitTotal = traitIndex + 1;
        traitPartial = 0;

    // Condition Three: None
    } else if (traitIndex == -1) {
        traitTotal = 0;
        traitPartial = total;

    // Condition Two: Partial
    } else {
        traitTotal = traitIndex + 1;
        traitPartial = traitThreshold - total;
    }

    std::map<std::string, int> traitResults;
    traitResults["Trait"] =  total;
    traitResults["Threshold"] = traitThreshold;
    traitResults["Total"] = traitTotal;
    traitResults["Partial"] = traitPartial;
    
    return traitResults;
}

// The purpose of this class is to perform calculations for "Team Traits".
// This will calculate `partialTraits`, `perfectTraits`, `totalTraits`, `teamCostAvg`,
// etc,...
// The class will be initialized with `currentTeamTraits` and the `subsetTraitMap`
std::map<std::string, std::map<std::string, int>> calculateTeamTotals(std::unordered_map<std::string, int> currentTeamTraits, std::map<std::string, Trait *> traitMapSubset) {
    // A mapping between `totalTraits`, `partialTraits`, `perfectTraits` and `teamAvgCost`.
    std::map<std::string, std::map<std::string, int>> teamTotals;

    // Iterate `traitMapSubset`
    for (auto & it : traitMapSubset) {
        // The current trait.
        std::string currentTrait = it.first;
        
        // Trait thresholds for a given trait.
        std::vector<int> traitThresholds = it.second -> getMinUnits();

        // Trait total for the given team.
        int currentTraitTotal = currentTeamTraits[it.first];

        // Trait Total and relative min_unit index.
        std::tuple<int, int> myTuple = findTraitThreshold(traitThresholds, currentTraitTotal);
        std::map<std::string, int> scoreTeamTraits = calculateTraitThreshold(myTuple, currentTraitTotal);
        teamTotals[it.first] = scoreTeamTraits;
    }

    return teamTotals;
}

std::map<std::string, int> scoreTeamTotals(std::map<std::string, std::map<std::string, int>> teamTotals) {
    int partialTotal = 0;
    int totalTotal = 0;
    std::map<std::string, int> finalTeamTotal;

    // Iterate `Traits`
    for (auto & trait : teamTotals) {
        partialTotal += trait.second["Partial"];
        totalTotal += trait.second["Total"];

    }

    finalTeamTotal["Total"] = totalTotal;
    finalTeamTotal["Partial"] = partialTotal;

    return finalTeamTotal;
}

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream &str)
{
    std::vector<std::string> result;
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ','))
    {
        result.push_back(cell);
    }
    if (!lineStream && cell.empty())
    {
        result.push_back("");
    }
    return result;
}
std::vector<std::vector<std::string>> parseCSV(std::string path)
{
    std::ifstream file(path);
    std::vector<std::vector<std::string>> row;
    while (file)
    {
        std::vector<std::string> column;

        std::vector<std::string> lineData = getNextLineAndSplitIntoTokens(file);
        for (const auto &token : lineData)
        {
            column.push_back(token);
        }
        row.push_back(column);
    }

    return (row);
}

//      Place all units into a Class
std::vector<Unit *> assignUnits(std::vector<std::vector<std::string>> units)
{
    std::vector<Unit *> allUnits;
    for (int i = 1; i < units.size() - 1; i++)
    { // Why must I subtract 1?
        // Temporary row containing info
        std::vector<std::string> U = units[i];
        int row_len = U.size();
        int tier = std::stoi(U.at(1));
        // create traits vec
        std::vector<std::string> traits;
        for (int k = 2; k < row_len; k++)
        {
            traits.push_back(U.at(k));
        }

        Unit *myUnit = new Unit(U.at(0), tier, traits);
        allUnits.push_back(myUnit);
    }

    return allUnits;
}

//      Using data from parsed `Traits.csv`, mapping between `Trait` and `Trait` object.
//      This function has removed `unique` traits.
//
//          Note: When this confuses you in the future, think of this as a named list returning a vector.
std::map<std::string, Trait *> assignTraits(std::vector<std::vector<std::string>> traits)
{
    std::map<std::string, Trait *> traitMap;
    std::vector<Trait *> allTraits;

    for (int i = 1; i < traits.size() - 1; i++)
    {
        std::vector<std::string> T = traits[i];
        int row_len = T.size();
        std::vector<int> tmp_traits;
        for (int k = 1; k < row_len; k++)
        {
            tmp_traits.push_back(stoi(T.at(k)));
        }

        // Condition preventing unique trait from existing in mapping.
        if (tmp_traits.size() > 1)
        {
            Trait *myTrait = new Trait(T.at(0), tmp_traits);
            traitMap[T.at(0)] = myTrait;
        }
    }

    return traitMap;
}

// Create a mapping between Units and Class
std::map<std::string, Unit *> mapUnits(std::vector<Unit *> allUnits)
{
    std::map<std::string, Unit *> unitMap;

    for (Unit *unit : allUnits)
    {
        unitMap[unit->getName()] = unit;
    }

    return unitMap;
}

// Find the index for a row...
int findIndex(const std::vector<std::string> &vec, const std::string &target)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec.at(i) == target)
        {
            return i; // Return the index of the found element
        }
    }
    return -1; // Return -1 if the element is not found
}

// For a given string vector, return the team from a mapping
Team * createTeam(std::vector<std::string> unit_id, std::map<std::string, Unit *> unit_map)
{
    std::vector<Unit *> tmpTeam;

    // Create vector of units
    for (auto &it : unit_id)
    {
        tmpTeam.push_back(unit_map[it]);
    }

    // Assign Vector of units to team.
    Team *newTeam = new Team(tmpTeam);
    return newTeam;
}


// For a given `Team`, create subset of `traitMap`.
std::map<std::string, Trait *> subsetTraitMap(std::unordered_map<std::string, int> teamTraits, std::map<std::string, Trait *> traitMap) {
    std::map<std::string, Trait *> traitMapSubset;

    // Select the traits from the current team and subset the mapping.
    for (auto &it : teamTraits) {
        traitMapSubset[it.first] = traitMap[it.first];
        traitMap[it.first] -> getMinUnits();
    }

    return traitMapSubset;
}


// Combine assignUnits and mapUnits
int main() {
    // Config
    init in;

    // Parse data into csv
    std::vector<std::vector<std::string>> Units = parseCSV("Data/Set10/Units_v02.csv");
    std::vector<std::vector<std::string>> Traits = parseCSV("Data/Set10/Traits_v02.csv");

    // Create Class for Units
    std::vector<Unit *> allUnits = assignUnits(Units);

    // Filter Units here
    filterUnits(allUnits, in);

    // Assign Mapping to Units
    std::map<std::string, Unit *> unitMap = mapUnits(allUnits);

    // Mapping between trait and the minimum units.
    //          string: Name of trait
    //          Trait*: Object
    std::map<std::string, Trait *> traitMap = assignTraits(Traits);

    // // Save Teams meeting the conditions here.
    // std::vector<Team *> finalTeams;

    // begin timer
    const clock_t begin_time = clock();

    // count number of combinations
    int count = 0;
    int K = in.teamSize;
    int N = allUnits.size();
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N - K trailing 0's

    // initialise vector to save index of champions satisfying conditions
    // std::vector<Team *> Z;
    // std::vector<std::vector<int>> Z;
    do {
        // temporary vector containing champion indexes
        std::vector<int> y;

        // create combination of champions
        for (int i = 0; i < N; i++) { // [0..N-1] integers
            if (bitmask[i]) {
                y.push_back(i);
            }
        }

        // Create Temporary team and add vector
        std::vector<std::string> tmp_team_id;
        for (auto & i : y) {
            tmp_team_id.push_back(allUnits.at(i) -> getName());
        }
        Team *testTeam = createTeam(tmp_team_id, unitMap);

        // Named list for a `Trait` and the count within a team.
        std::unordered_map<std::string, int> currentTeamTraits = testTeam -> getTraitCount();

        // Select a subset of traitMap by the names of `trait_count`.
        std::map<std::string, Trait *> traitMapSubset = subsetTraitMap(currentTeamTraits, traitMap);

        // For the given team, calculate the Partial and Total traits.
        std::map<std::string, std::map<std::string, int>> teamTotals = calculateTeamTotals(currentTeamTraits, traitMapSubset);

        // For the calculated team totals, calculate overall score.
        std::map<std::string, int> test = scoreTeamTotals(teamTotals);

        // Save the mappings and data to the team.
        testTeam -> setTeamTotal(teamTotals);
        testTeam -> setTeamTotalScore(test);
        // testTeam -> finalTeamDisplay();

        // Final Condition to score pass or fail.
        if (test["Partial"] <= 1) {
            // std::vector<Team *> Z = 
            testTeam -> finalTeamDisplay();
            // finalTeams.push_back(testTeam);
        }
        // display waiting message for long computation time
        count++;
        if (count % 100000 == 0) {
            std::cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
            std::cout << ": Thinking..." << std::endl;
        }

    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
 
    return 0;
}