#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include "Food.h"
#include "Nutrition.h"
#include <string>
#include <vector>

struct FoodRecommendation
{
    std::string name;
    double cost;
    double score;
};

class RecommendationEngine
{
public:
    std::vector<FoodRecommendation> recommend(
        const std::vector<Food>& foods, const NutritionReport& report,
        int maxResults = 5) const;

    void displayRecommendations(
        const std::vector<FoodRecommendation>& choices) const;
};

#endif
