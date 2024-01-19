// TraitController.h

#ifndef TRAITCONTROLLER_H
#define TRAITCONTROLLER_H

#include <unordered_map>
#include <map>
#include "Trait.h"
#include "ParseCSV.h"

class TraitController {
    private:
        // std::string _path_to_data;
        std::unordered_map<std::string, Trait *> trait_map;
        std::vector<Trait *> all_traits;

        // Convert CSV data into usable obj
        void assignTraits(std::vector<std::vector<std::string>> traits) {
            std::vector<Trait *> all_tr;

            //  Iterate Rows
            // `trait.size()` has been subtracted by 1 due to fix poor parsing code.
            for (size_t i = 1; i < traits.size() - 1; i++) {
                std::string trait_id = traits.at(i).at(0);
                std::vector<int> trait_threshold;

                // Iterate Columns
                for (size_t j = 1; j < traits.at(i).size(); j++) {
                    trait_threshold.push_back(std::stoi(traits.at(i).at(j)));
                }

                Trait * tmp_trait = new Trait(trait_id, trait_threshold);
                all_tr.push_back(tmp_trait);
            }

            all_traits = all_tr;
        }
        void createTraitMap() {
            // variable to be overwritten (used cleaner code?)[is this good practice?]
            std::string traitKey;

            // Iterate vectoring containing all traits
            for (const auto & trait : all_traits) {
                // Update key to be saved in map.
                traitKey = trait -> getTraitID();

                // Add mapping from TraitID to Trait *
                trait_map[traitKey] = trait;
            }

        }

    public:
        // TraitStruct trait_struct;
        TraitController(std::string path_to_data) : trait_map(), all_traits() {
            // Initialize class for parsing csv
            ParseCSV parse_csv;

            // Parse csv
            auto parsed_data = parse_csv.parseData(path_to_data);

            // Converts parsed csv data into usable data structure
            assignTraits(parsed_data);

            // Creates a mapping between 
            createTraitMap();

        }

        std::vector<Trait *> GetAllTraits() { return all_traits; }
        std::unordered_map<std::string, Trait *> GetTraitMap() { return trait_map; }
};

#endif // TRAITCONTROLLER_H