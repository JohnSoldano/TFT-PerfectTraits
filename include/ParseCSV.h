// parseCSV.h
#ifndef PARSECSV_H
#define PARSECSV_H

#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <fstream>

class ParseCSV {
    private:
        std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream &str);
    public:
        ParseCSV();
        ~ParseCSV();
        std::vector<std::vector<std::string>> parseData(std::string p);
};
#endif // PARSECSV_H