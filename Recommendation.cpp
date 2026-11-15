#include "Recommendation.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

// Return one nutrient value from a food.
double getNutrient(const Food& food, const string& name)
{
    if (name == "Protein") return food.getProtein();
    if (name == "Iron") return food.getIron();
    if (name == "Calcium") return food.getCalcium();
    return food.getFiber();
}

// Higher scores come first. If scores tie, the cheaper food comes first.
struct CompareFood
{
    bool operator()(const FoodRecommendation& a,
                    const FoodRecommendation& b) const
    {
        if (a.score == b.score)
            return a.cost > b.cost;
        return a.score < b.score;
    }
};

vector<FoodRecommendation> RecommendationEngine::recommend(
    const vector<Food>& foods, const NutritionReport& report,
    int maxResults) const
{
    priority_queue<FoodRecommendation, vector<FoodRecommendation>, CompareFood> ranked;

    int totalGaps = 0;
    for (const NutrientResult& nutrient : report.nutrients)
    {
        if (nutrient.consumed < nutrient.target)
            totalGaps++;
    }

    if (totalGaps == 0 || maxResults <= 0)
        return {};

    // Give every food a score based on how much it can fill the nutrient gaps.
    for (const Food& food : foods)
    {
        double score = 0;

        for (const NutrientResult& nutrient : report.nutrients)
        {
            if (nutrient.consumed >= nutrient.target)
                continue;

            double remaining = nutrient.target - nutrient.consumed;
            double amount = getNutrient(food, nutrient.name);
            if (amount > 0)
                score += min(amount, remaining) / remaining;
        }

        if (score > 0)
        {
            FoodRecommendation item = {
                food.getName(),
                food.getCost(),
                score / totalGaps * 100
            };
            ranked.push(item);
        }
    }

    // Remove the highest-scoring foods from the priority queue first.
    vector<FoodRecommendation> result;
    while (!ranked.empty() && static_cast<int>(result.size()) < maxResults)
    {
        result.push_back(ranked.top());
        ranked.pop();
    }

    return result;
}

void RecommendationEngine::displayRecommendations(
    const vector<FoodRecommendation>& choices) const
{
    cout << "\n===== FOOD RECOMMENDATIONS =====\n";

    if (choices.empty())
    {
        cout << "No recommendations available.\n";
        return;
    }

    cout << left << setw(5) << "Rank" << setw(20) << "Food"
         << right << setw(13) << "Cost/serving"
         << setw(12) << "Score" << '\n';
    cout << string(50, '-') << '\n';

    for (int i = 0; i < static_cast<int>(choices.size()); i++)
    {
        cout << left << setw(5) << i + 1 << setw(20) << choices[i].name
             << right << fixed << setprecision(2)
             << setw(13) << choices[i].cost
             << setw(11) << choices[i].score << "%\n";
    }
}
