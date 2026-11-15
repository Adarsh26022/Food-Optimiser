#include "User.h"

NutritionTargets User::getNutritionTargets() const
{
    return targets;
}

void User::setNutritionTargets(double protein, double iron,
                               double calcium, double fiber)
{
    targets.protein = protein;
    targets.iron = iron;
    targets.calcium = calcium;
    targets.fiber = fiber;
}

