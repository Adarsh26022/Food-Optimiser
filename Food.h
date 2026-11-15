#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <vector>

class Food
{
private:
    std::string name;
    double protein;
    double iron;
    double calcium;
    double fiber;
    double cost;

public:
    Food(std::string name, double protein, double iron,
         double calcium, double fiber, double cost);

    std::string getName() const;
    double getProtein() const;
    double getIron() const;
    double getCalcium() const;
    double getFiber() const;
    double getCost() const;

    void display() const;
};

void addFood(std::vector<Food>& foods);
void displayFoods(const std::vector<Food>& foods);
const Food* findFood(const std::vector<Food>& foods, const std::string& name);
void searchFood(const std::vector<Food>& foods, const std::string& name);

// Save the food database and load it when the program starts.
bool saveFoods(const std::vector<Food>& foods, const std::string& filename);
bool loadFoods(std::vector<Food>& foods, const std::string& filename);

#endif


