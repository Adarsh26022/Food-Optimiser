#ifndef NUTRITION_H
#define NUTRITION_H

#include "Meal.h"
#include "User.h"
#include <string>
#include <vector>

struct NutrientResult
{
    std::string name;
    double consumed;
    double target;
    std::string unit;
};

struct NutritionReport
{
    std::vector<NutrientResult> nutrients;
    double score = 0;
};

class NutritionAnalyzer
{
public:
    NutritionReport analyze(const NutritionTotals& totals,
                            const NutritionTargets& targets) const;
    void displayReport(const NutritionReport& report) const;
};

#endif