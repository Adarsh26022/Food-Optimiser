#include "Food.h"
#include "Meal.h"
#include "User.h"
#include "Nutrition.h"
#include "Recommendation.h"
#include "Optimizer.h"
#include "History.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Read an integer and reject invalid input.
bool readInteger(const string& message, int& number)
{
    while (true)
    {
        cout << message;

        if (cin >> number)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }

        if (cin.eof())
            return false;

        cout << "Please enter a valid whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a positive number, such as a serving quantity or daily target.
bool readPositiveNumber(const string& message, double& number)
{
    while (true)
    {
        cout << message;

        if (cin >> number)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (number > 0)
                return true;

            cout << "Please enter a number greater than zero.\n";
        }
        else
        {
            if (cin.eof())
                return false;

            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Food lookup is handled by findFood() declared in Food.h and defined in Food.cpp.

// Return the meal selected by the user.
Meal* chooseMeal(int choice, Meal& breakfast, Meal& lunch, Meal& dinner)
{
    if (choice == 1) return &breakfast;
    if (choice == 2) return &lunch;
    if (choice == 3) return &dinner;

    return nullptr;
}

void showMealChoices()
{
    cout << "\n1. Breakfast\n2. Lunch\n3. Dinner\n";
}

// Search for a food and add the required number of servings to a meal.
void addFoodToMeal(const vector<Food>& foods,
                   Meal& breakfast, Meal& lunch, Meal& dinner)
{
    if (foods.empty())
    {
        cout << "Food database is empty. Add a food first.\n";
        return;
    }

    showMealChoices();

    int choice;
    if (!readInteger("Choose a meal: ", choice))
        return;

    Meal* meal = chooseMeal(choice, breakfast, lunch, dinner);

    if (meal == nullptr)
    {
        cout << "Invalid meal choice.\n";
        return;
    }

    string name;
    cout << "Enter food name: ";
    getline(cin, name);

    const Food* food = findFood(foods, name);

    if (food == nullptr)
    {
        cout << "Food not found.\n";
        return;
    }

    double quantity;
    if (!readPositiveNumber("Enter quantity in servings: ", quantity))
        return;

    meal->addFood(*food, quantity);
    cout << food->getName() << " added to " << meal->getName() << ".\n";
}

// Display the items and totals for one selected meal.
void viewMeal(Meal& breakfast, Meal& lunch, Meal& dinner)
{
    showMealChoices();

    int choice;
    if (!readInteger("Choose a meal: ", choice))
        return;

    Meal* meal = chooseMeal(choice, breakfast, lunch, dinner);

    if (meal == nullptr)
    {
        cout << "Invalid meal choice.\n";
        return;
    }

    meal->display();
}

// Add the nutrition totals from breakfast, lunch, and dinner.
NutritionTotals dailyTotals(const Meal& breakfast,
                            const Meal& lunch,
                            const Meal& dinner)
{
    NutritionTotals total;
    NutritionTotals b = breakfast.calculateTotals();
    NutritionTotals l = lunch.calculateTotals();
    NutritionTotals d = dinner.calculateTotals();

    total.protein = b.protein + l.protein + d.protein;
    total.iron = b.iron + l.iron + d.iron;
    total.calcium = b.calcium + l.calcium + d.calcium;
    total.fiber = b.fiber + l.fiber + d.fiber;
    total.cost = b.cost + l.cost + d.cost;

    return total;
}

// Create a nutrition report using the daily totals and the user's targets.
NutritionReport getReport(const User& user,
                          const NutritionAnalyzer& analyzer,
                          const Meal& breakfast,
                          const Meal& lunch,
                          const Meal& dinner)
{
    return analyzer.analyze(
        dailyTotals(breakfast, lunch, dinner),
        user.getNutritionTargets());
}

// Let the user change the four daily nutrition targets.
void changeTargets(User& user)
{
    double protein, iron, calcium, fiber;

    cout << "\nEnter daily nutrition targets.\n";

    if (!readPositiveNumber("Protein (g): ", protein)) return;
    if (!readPositiveNumber("Iron (mg): ", iron)) return;
    if (!readPositiveNumber("Calcium (mg): ", calcium)) return;
    if (!readPositiveNumber("Fiber (g): ", fiber)) return;

    user.setNutritionTargets(protein, iron, calcium, fiber);
    cout << "Nutrition targets updated.\n";
}

int main()
{
    const string foodFile = "foods.txt";
    const string historyFile = "meal_history.txt";
    vector<Food> foods;

    // Load the saved database. If this is the first run, use default foods.
    if (!loadFoods(foods, foodFile))
    {
        foods = {
            Food("Rice", 2.7, 0.2, 10, 0.4, 20),
            Food("Dal", 9, 3.3, 35, 7.9, 30),
            Food("Milk", 3.3, 0.03, 125, 0, 25),
            Food("Egg", 13, 1.2, 56, 0, 10),
            Food("Spinach", 2.9, 2.7, 99, 2.2, 15)
        };

        if (!saveFoods(foods, foodFile))
            cout << "Warning: Could not create foods.txt.\n";
    }

    Meal breakfast("Breakfast");
    Meal lunch("Lunch");
    Meal dinner("Dinner");

    User user;
    NutritionAnalyzer analyzer;
    RecommendationEngine recommendationEngine;
    CombinationOptimizer optimizer;

    while (true)
    {
        cout << "\n===== FOOD COMBINATION OPTIMIZER =====\n";
        cout << "1. Display Food Database\n";
        cout << "2. Add Food to Database\n";
        cout << "3. Search Food\n";
        cout << "4. Record a Meal\n";
        cout << "5. View a Meal\n";
        cout << "6. View Daily Nutrition\n";
        cout << "7. Change Nutrition Targets\n";
        cout << "8. Analyze Nutrition\n";
        cout << "9. Get Food Recommendations\n";
        cout << "10. Optimize Food Combinations\n";
        cout << "11. Save Today's Nutrition History\n";
        cout << "12. View Nutrition History\n";
        cout << "0. Exit\n";

        int choice;
        if (!readInteger("Enter your choice: ", choice))
            break;

        if (choice == 1)
        {
            displayFoods(foods);
        }
        else if (choice == 2)
        {
            addFood(foods);
            if (!saveFoods(foods, foodFile))
                cout << "Warning: Could not save the food database.\n";
            else
                cout << "Food database saved.\n";
        }
        else if (choice == 3)
        {
            string name;
            cout << "Enter food name to search: ";
            getline(cin, name);
            searchFood(foods, name);
        }
        else if (choice == 4)
        {
            addFoodToMeal(foods, breakfast, lunch, dinner);
        }
        else if (choice == 5)
        {
            viewMeal(breakfast, lunch, dinner);
        }
        else if (choice == 6)
        {
            displayNutritionTotals(dailyTotals(breakfast, lunch, dinner));
        }
        else if (choice == 7)
        {
            changeTargets(user);
        }
        else if (choice == 8)
        {
            NutritionReport report = getReport(
                user, analyzer, breakfast, lunch, dinner);
            analyzer.displayReport(report);
        }
        else if (choice == 9)
        {
            NutritionReport report = getReport(
                user, analyzer, breakfast, lunch, dinner);

            vector<FoodRecommendation> choices =
                recommendationEngine.recommend(foods, report);

            recommendationEngine.displayRecommendations(choices);
        }
        else if (choice == 10)
        {
            double budget;
            if (readPositiveNumber("Enter your additional budget: ", budget))
            {
                vector<FoodCombination> combinations = optimizer.optimize(
                    foods,
                    dailyTotals(breakfast, lunch, dinner),
                    user.getNutritionTargets(),
                    budget);

                optimizer.displayCombinations(combinations);
            }
        }
        else if (choice == 11)
        {
            NutritionTotals totals = dailyTotals(breakfast, lunch, dinner);
            NutritionTargets targets = user.getNutritionTargets();
            NutritionReport report = analyzer.analyze(totals, targets);

            if (saveTodayHistory(totals, targets, report.score, historyFile))
                cout << "Today's nutrition summary saved successfully.\n";
            else
                cout << "Could not save nutrition history.\n";
        }
        else if (choice == 12)
        {
            displayNutritionHistory(historyFile);
        }
        else if (choice == 0)
        {
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

