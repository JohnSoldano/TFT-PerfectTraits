// TeamController.h

/*
    This class will calculate combinations passing teams...
*/
#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include "TraitController.h"
#include "Team.h"

class TeamController {
    private:
        std::unordered_map<std::string, Trait *> trait_map;
        // Team team;
    public:
        TeamController(std::unordered_map<std::string, Trait *> trait_mappings) : trait_map(trait_mappings) {

        }
        ~TeamController() {}

        // void SetTeam(Team t) { team = t; }
};

#endif // TEAMCONTROLLER_H