#ifndef USER_H
#define USER_H

struct NutritionTargets
{
    double protein = 50;   // grams per day
    double iron = 18;      // milligrams per day
    double calcium = 1000; // milligrams per day
    double fiber = 25;     // grams per day
};

class User
{
private:
    NutritionTargets targets;

public:
    NutritionTargets getNutritionTargets() const;
    void setNutritionTargets(double protein, double iron,
                             double calcium, double fiber);
};

#endif