#include "Optimizer.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

// Better score comes first. If scores are equal, the cheaper combination comes first.
bool compareCombinations(const FoodCombination& a, const FoodCombination& b)
{
    if (a.nutritionScore == b.nutritionScore)
        return a.totalCost < b.totalCost;

    return a.nutritionScore > b.nutritionScore;
}

vector<FoodCombination> CombinationOptimizer::optimize(
    const vector<Food>& foods,
    const NutritionTotals& currentTotals,
    const NutritionTargets& targets,
    double budget,
    int maxResults) const
{
    vector<FoodCombination> combinations;

    if (foods.empty() || foods.size() > MAX_FOODS || budget < 0 || maxResults <= 0)
        return combinations;

    NutritionAnalyzer analyzer;

    // Each number from 1 to 2^n - 1 represents one non-empty food combination.
    unsigned int totalMasks = 1U << foods.size();

    for (unsigned int mask = 1; mask < totalMasks; mask++)
    {
        FoodCombination combination;
        NutritionTotals totals = currentTotals;

        for (size_t i = 0; i < foods.size(); i++)
        {
            // If bit i is 1, include food i in this combination.
            if ((mask & (1U << i)) == 0)
                continue;

            const Food& food = foods[i];
            combination.foodNames.push_back(food.getName());
            combination.totalCost += food.getCost();

            // Add one serving of the selected food to the current daily totals.
            totals.protein += food.getProtein();
            totals.iron += food.getIron();
            totals.calcium += food.getCalcium();
            totals.fiber += food.getFiber();
            totals.cost += food.getCost();
        }

        // Keep only combinations that stay within the additional budget.
        if (combination.totalCost <= budget)
        {
            NutritionReport report = analyzer.analyze(totals, targets);
            combination.nutritionScore = report.score;
            combinations.push_back(combination);
        }
    }

    sort(combinations.begin(), combinations.end(), compareCombinations);

    if (combinations.size() > static_cast<size_t>(maxResults))
        combinations.resize(maxResults);

    return combinations;
}

void CombinationOptimizer::displayCombinations(
    const vector<FoodCombination>& combinations) const
{
    cout << "\n===== BEST FOOD COMBINATIONS =====\n";

    if (combinations.empty())
    {
        cout << "No combinations fit within the budget.\n";
        return;
    }

    cout << fixed << setprecision(2);

    for (size_t i = 0; i < combinations.size(); i++)
    {
        cout << "\nRank " << i + 1 << ": ";

        for (size_t j = 0; j < combinations[i].foodNames.size(); j++)
        {
            if (j > 0)
                cout << " + ";

            cout << combinations[i].foodNames[j];
        }

        cout << "\nAdditional cost: Rs. " << combinations[i].totalCost
             << "\nProjected daily nutrition score: "
             << combinations[i].nutritionScore << " / 100\n";
    }
}

