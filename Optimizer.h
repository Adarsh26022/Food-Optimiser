#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Food.h"
#include "Nutrition.h"
#include <string>
#include <vector>

struct FoodCombination
{
    std::vector<std::string> foodNames;
    double totalCost = 0;
    double nutritionScore = 0;
};

class CombinationOptimizer
{
public:
    static constexpr int MAX_FOODS = 15;

    std::vector<FoodCombination> optimize(
        const std::vector<Food>& foods,
        const NutritionTotals& currentTotals,
        const NutritionTargets& targets,
        double budget,
        int maxResults = 5) const;

    void displayCombinations(
        const std::vector<FoodCombination>& combinations) const;
};

#endif
