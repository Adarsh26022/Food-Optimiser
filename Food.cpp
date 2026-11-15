#include "Food.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Convert a name to lowercase so searches are not case-sensitive.
string lowerCase(string text)
{
    for (char& ch : text)
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    return text;
}

string trim(string text)
{
    size_t first = text.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";

    size_t last = text.find_last_not_of(" \t\n\r");
    return text.substr(first, last - first + 1);
}

// Read a number that cannot be negative.
bool readNonNegativeNumber(const string& message, double& number)
{
    while (true)
    {
        cout << message;
        if (cin >> number)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (number >= 0)
                return true;

            cout << "Please enter a number that is 0 or greater.\n";
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

Food::Food(string name, double protein, double iron,
           double calcium, double fiber, double cost)
    : name(name), protein(protein), iron(iron),
      calcium(calcium), fiber(fiber), cost(cost)
{
}

string Food::getName() const { return name; }
double Food::getProtein() const { return protein; }
double Food::getIron() const { return iron; }
double Food::getCalcium() const { return calcium; }
double Food::getFiber() const { return fiber; }
double Food::getCost() const { return cost; }

void Food::display() const
{
    cout << left << setw(18) << name
         << right << fixed << setprecision(2)
         << setw(10) << protein
         << setw(10) << iron
         << setw(12) << calcium
         << setw(10) << fiber
         << setw(12) << cost << '\n';
}

void addFood(vector<Food>& foods)
{
    string name;
    cout << "Enter food name: ";
    getline(cin, name);

    name = trim(name);
    if (name.empty())
    {
        cout << "Food name cannot be empty.\n";
        return;
    }

    if (findFood(foods, name) != nullptr)
    {
        cout << "This food is already in the database.\n";
        return;
    }

    double protein, iron, calcium, fiber, cost;
    if (!readNonNegativeNumber("Protein (g per serving): ", protein) ||
        !readNonNegativeNumber("Iron (mg per serving): ", iron) ||
        !readNonNegativeNumber("Calcium (mg per serving): ", calcium) ||
        !readNonNegativeNumber("Fiber (g per serving): ", fiber) ||
        !readNonNegativeNumber("Cost (Rs. per serving): ", cost))
    {
        cout << "Food was not added because input ended.\n";
        return;
    }

    foods.push_back(Food(name, protein, iron, calcium, fiber, cost));
    cout << "Food added.\n";
}

void displayFoods(const vector<Food>& foods)
{
    if (foods.empty())
    {
        cout << "The food database is empty.\n";
        return;
    }

    cout << "\nNutritional values and cost are for one serving.\n";
    cout << left << setw(18) << "Food"
         << right << setw(10) << "Protein"
         << setw(10) << "Iron"
         << setw(12) << "Calcium"
         << setw(10) << "Fiber"
         << setw(12) << "Cost (Rs.)" << '\n';
    cout << string(72, '-') << '\n';

    for (const Food& food : foods)
        food.display();
}

const Food* findFood(const vector<Food>& foods, const string& name)
{
    for (const Food& food : foods)
    {
        if (lowerCase(food.getName()) == lowerCase(trim(name)))
            return &food;
    }
    return nullptr;
}

void searchFood(const vector<Food>& foods, const string& name)
{
    const Food* food = findFood(foods, name);

    if (food == nullptr)
    {
        cout << "Food not found.\n";
        return;
    }

    cout << "\nFood found (values per serving):\n";
    cout << left << setw(18) << "Food"
         << right << setw(10) << "Protein"
         << setw(10) << "Iron"
         << setw(12) << "Calcium"
         << setw(10) << "Fiber"
         << setw(12) << "Cost (Rs.)" << '\n';
    cout << string(72, '-') << '\n';
    food->display();
}


// Save each food on a separate line. std::quoted keeps names with spaces intact.
bool saveFoods(const vector<Food>& foods, const string& filename)
{
    ofstream file(filename);
    if (!file)
        return false;

    for (const Food& food : foods)
    {
        file << quoted(food.getName()) << ' '
             << food.getProtein() << ' '
             << food.getIron() << ' '
             << food.getCalcium() << ' '
             << food.getFiber() << ' '
             << food.getCost() << '\n';
    }

    return file.good();
}

// Load saved foods. Return false if the file is missing or has no valid records.
bool loadFoods(vector<Food>& foods, const string& filename)
{
    ifstream file(filename);
    if (!file)
        return false;

    vector<Food> loadedFoods;
    string name;
    double protein, iron, calcium, fiber, cost;

    while (file >> quoted(name) >> protein >> iron >> calcium >> fiber >> cost)
    {
        if (name.empty() || protein < 0 || iron < 0 || calcium < 0 ||
            fiber < 0 || cost < 0)
            continue;

        loadedFoods.push_back(Food(name, protein, iron, calcium, fiber, cost));
    }

    if (loadedFoods.empty())
        return false;

    foods = loadedFoods;
    return true;
}


