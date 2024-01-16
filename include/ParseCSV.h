// parseCSV.h
#ifndef PARSECSV_H
#define PARSECSV_H

#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

class ParseCSV {
    private:
        // std::vector<Unit *> all_units;
        // std::vector<Trait *> all_traits;
        std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream &str);
        

    public:
        // More elegant Trait data structure?
        // struct TraitStruct {
        //     std::unordered_map<std::string, Trait *> myMap;

        //     // Destructor to clean up dynamically allocated objects
        //     ~TraitStruct() {
        //         for (auto & pair : myMap) {
        //             delete pair.second;
        //         }
        //         myMap.clear();
        //     }

            
        //     void add(const std::string & key, Trait * value) {
        //         // Remove existing entry if present
        //         auto it = myMap.find(key);
        //         if (it != myMap.end()) {
        //             delete it -> second;
        //         }
        //         myMap[key] = value;
        //     }

        //     Trait * get(const std::string & key) const {
        //         auto it = myMap.find(key);
        //         if (it != myMap.end()) {
        //             return it -> second;
        //         }
        //         return nullptr;
        //     }

        //     void parse(std::vector<Trait *> trait) {
        //         for (auto it : trait) {
        //             add(it -> getTraitID(), it);
        //         }
        //     }
        // };

        ParseCSV();
        ParseCSV(std::string x);
        ParseCSV(std::vector<std::string> x);
        ~ParseCSV();
        std::vector<std::vector<std::string>> parseData(std::string p);
        // void assignUnits(std::vector<std::vector<std::string>> x);
        // void assignTraits(std::vector<std::vector<std::string>> x);

        // std::vector<Unit *> getUnits() { return all_units; }
        // std::vector<Trait *> getTraits() { return all_traits; }
        // TraitStruct getTraitStruct() {
        //     TraitStruct trait_struct;
        //     trait_struct.parse(all_traits);
        //     return trait_struct;
        // }
};
#endif // PARSECSV_H