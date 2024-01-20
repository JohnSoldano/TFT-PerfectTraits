// global.h

#ifndef GLOBAL_H
#define GLOBAL_H


#include "Team.h"
#include "Trait.h"
#include "init.h"
#include <fstream>
#include <streambuf>
#include <memory>

// Place all units into a Class
// Output data to csv format.
void OutputCSV(std::string path, std::vector<Team> final_teams);

// Output data as txt format.
void OutputTXT(std::string path, std::vector<Team> final_teams);

#endif // GLOBAL_H