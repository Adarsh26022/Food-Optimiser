#include "Meal.h"

#include <iomanip>
#include <iostream>

using namespace std;

Meal::Meal(const string& name) : name(name)
{
}

string Meal::getName() const
{
    return name;
}

void Meal::addFood(const Food& food, double quantity)
{
    // Store the food and how many servings were eaten.
    items.push_back({food, quantity});
}

NutritionTotals Meal::calculateTotals() const
{
    NutritionTotals totals;

    for (const MealItem& item : items)
    {
        totals.protein += item.food.getProtein() * item.quantity;
        totals.iron += item.food.getIron() * item.quantity;
        totals.calcium += item.food.getCalcium() * item.quantity;
        totals.fiber += item.food.getFiber() * item.quantity;
        totals.cost += item.food.getCost() * item.quantity;
    }

    return totals;
}

void Meal::display() const
{
    if (items.empty())
    {
        cout << name << " is empty.\n";
        return;
    }

    cout << "\n" << name << " (quantity is in servings)\n";
    cout << left << setw(18) << "Food"
         << right << setw(10) << "Quantity"
         << setw(10) << "Protein"
         << setw(10) << "Iron"
         << setw(12) << "Calcium"
         << setw(10) << "Fiber"
         << setw(12) << "Cost (Rs.)" << '\n';
    cout << string(82, '-') << '\n';

    for (const MealItem& item : items)
    {
        cout << left << setw(18) << item.food.getName()
             << right << fixed << setprecision(2)
             << setw(10) << item.quantity
             << setw(10) << item.food.getProtein() * item.quantity
             << setw(10) << item.food.getIron() * item.quantity
             << setw(12) << item.food.getCalcium() * item.quantity
             << setw(10) << item.food.getFiber() * item.quantity
             << setw(12) << item.food.getCost() * item.quantity << '\n';
    }

    cout << "\nMeal totals:\n";
    displayNutritionTotals(calculateTotals());
}

void displayNutritionTotals(const NutritionTotals& totals)
{
    cout << fixed << setprecision(2)
         << "Protein: " << totals.protein << " g\n"
         << "Iron:    " << totals.iron << " mg\n"
         << "Calcium: " << totals.calcium << " mg\n"
         << "Fiber:   " << totals.fiber << " g\n"
         << "Cost: Rs. " << totals.cost << '\n';
}

