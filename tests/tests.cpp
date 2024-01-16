#include "tests.h"

#include <algorithm>
#include <string>
#include <vector>

// Utility function to print a combination
void printCombination(const std::vector<int>& combination) {
    for (int i : combination) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

// Recursive function to generate all combinations of size k
void generateCombinations(std::vector<int>& result, int n, int k, int index, int i) {
    if (index == k) {
        // printCombination(result);
        return;
    }

    if (i <= n) {
        result[index] = i;
        generateCombinations(result, n, k, index + 1, i + 1);
        generateCombinations(result, n, k, index, i + 1);
    }
}

void printCombinationIterative(const std::vector<int>& combination) {
    for (int i : combination) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void generateCombinationsIterative(int n, int k) {
    std::vector<int> combination(k);

    // Initialize the first combination to be 0, 1, 2, ..., k-1
    for (int i = 0; i < k; ++i) {
        combination[i] = i;
    }

    // After first combination, iterate through remaining combinations
    while (true) {
        for (const auto & it : combination) {
            std::cout << it << " ";
        }
        std::cout << std::endl;

        // Generate the next combination
        int i;
        for (i = k - 1; i >= 0 && combination[i] == i + n - k; --i);
        if (i < 0) break; // All combinations generated

        combination[i]++;
        for (int j = i + 1; j < k; ++j) {
            combination[j] = combination[j - 1] + 1;
        }

        // printCombinationIterative(combination);
    }
}

int main() {
    FunTimer fun_timer;
    FunTimer it_timer;

    int n = 5; // Size of the vector
    int k = 3;  // Size of the combinations

    it_timer.TimeBegin();
    generateCombinationsIterative(n, k);
    it_timer.TimeEnd();
    

    std::cout << "Iteration ";
    it_timer.DisplayTimeTaken();

    return 0;

}
