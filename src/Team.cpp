// Team.cpp
#include "Team.h"

// Count the no. times a trait appears in a team.
std::unordered_map<std::string, int> Team::countTraits(std::vector<Unit *> t) {
    std::vector<std::string> raw_traits;

    // Iterate Units within Team
    for (auto & x : team) {
        
        // Return Trait for each Unit within Team
        std::vector<std::string> tmp_traits = x -> getTraits();

        // Add to vector for counting.
        for (auto &y : tmp_traits) {
            raw_traits.push_back(y);
        }
    }

    // Count the occurrences of each string
    std::unordered_map<std::string, int> counts;

    // I don't understand why this works.
    for (const auto & elem : raw_traits) {
        ++counts[elem];
    }

    return counts;
}

// Constructor
Team::Team(std::vector<Unit *> units) {
    // Store Traits
    for (auto x : units) {
        team.push_back(x);
    }

    // Count Traits
    trait_count = Team::countTraits(units);
}

// Destructor
Team::~Team() {

}

// Display Team
void Team::displayTeam() {
    for (auto & it : team) {
        it -> displayInfo();
    }
}

// Show formatted trait count
void Team::displayCounts() {
    // Display the counts
    for (const auto &pair : trait_count) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }
}

// Display Final Team Data.
void Team::finalTeamDisplay() {
        int num_units = team.size();
        int totalTotal = team_total_score["Total"];
        int totalPartial = team_total_score["Partial"];

        // Display Size, Traits, etcs
        std::cout << std::endl;
        Team::dumbTableThing();
        std::cout << "\t\tTeam ID: " << team_number << std::endl;
        Team::dumbTableThing();
        std::cout << "Team Size: " << num_units << std::endl;
        std::cout << "Total Traits: " << totalTotal << std::endl;
        std::cout << "Partial Traits: " << totalPartial << std::endl;
        std::cout << "Avg Cost: " << Team::getAvgCost() << std::endl;
        std::cout << std::endl;

        // Display Units...
        for (auto & t : team) {
            std::cout << t -> getName() << " (" << t -> getCost() << ")" << std::endl;
        }
        std::cout << std::endl;

        // Display Totals..
        for (auto & x : team_totals) {
            std::cout << x.first << ": " << x.second["Trait"] << "/" << x.second["Threshold"] << std::endl;
        }
        Team::dumbTableThing();
        std::cout << std::endl;
    }

// Calculates team avg cost. This should only be called for
// teams satisfying pass conditions.
double Team::getAvgCost() {
    size_t num_units = team.size();

    // For all units within a team, store their cost into a vector.
    std::vector<int> team_cost;
    for (auto it : team) {
        team_cost.push_back(it -> getCost());
    }

    int team_cost_total = std::accumulate(team_cost.begin(), team_cost.end(), 0);
    double team_avg = static_cast<double>(team_cost_total) / num_units;
    
    return team_avg;
}