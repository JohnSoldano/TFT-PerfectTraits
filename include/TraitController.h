// TraitController.h

#ifndef TRAITCONTROLLER_H
#define TRAITCONTROLLER_H

#include <unordered_map>
#include "Trait.h"

class TraitController {
    private:
        std::vector<Trait *> all_traits;
        

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

    public:
        struct TraitStruct {
            std::unordered_map<std::string, Trait *> myMap;

            TraitStruct() { }

            // Destructor to clean up dynamically allocated objects
            ~TraitStruct() {
                for (auto & pair : myMap) {
                    delete pair.second;
                }
                myMap.clear();
            }

            
            void add(const std::string & key, Trait * value) {
                // Remove existing entry if present
                auto it = myMap.find(key);
                if (it != myMap.end()) {
                    delete it -> second;
                }
                myMap[key] = value;
            }

            Trait * get(const std::string & key) const {
                auto it = myMap.find(key);
                if (it != myMap.end()) {
                    return it -> second;
                }
                return nullptr;
            }

            void parse(std::vector<Trait *> trait) {
                for (auto it : trait) {
                    add(it -> getTraitID(), it);
                }
            }
        };
        
        TraitStruct trait_struct;
        TraitController(std::vector<std::vector<std::string>> traits) {
            assignTraits(traits);

            TraitStruct trait_st;        
            trait_st.parse(all_traits);
            trait_struct = trait_st;
        }

};

#endif // TRAITCONTROLLER_H