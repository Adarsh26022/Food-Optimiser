#ifndef MEAL_H
#define MEAL_H

#include "Food.h"
#include <string>
#include <vector>

struct NutritionTotals
{
    double protein = 0;
    double iron = 0;
    double calcium = 0;
    double fiber = 0;
    double cost = 0;

};

struct MealItem
{
    Food food;
    double quantity;
};

class Meal
{
private:
    std::string name;
    std::vector<MealItem> items;

public:
    Meal(const std::string& name);

    std::string getName() const;
    void addFood(const Food& food, double quantity);
    NutritionTotals calculateTotals() const;
    void display() const;
};

void displayNutritionTotals(const NutritionTotals& totals);

#endif
