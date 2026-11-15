#include "Nutrition.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

NutritionReport NutritionAnalyzer::analyze(const NutritionTotals& totals,
                                            const NutritionTargets& targets) const
{
    NutritionReport report;

    report.nutrients = {
        {"Protein", totals.protein, targets.protein, "g"},
        {"Iron", totals.iron, targets.iron, "mg"},
        {"Calcium", totals.calcium, targets.calcium, "mg"},
        {"Fiber", totals.fiber, targets.fiber, "g"}
    };

    // Each of the four nutrients can contribute up to 25 points.
    for (const NutrientResult& nutrient : report.nutrients)
    {
        double ratio = nutrient.consumed / nutrient.target;
        report.score += min(ratio, 1.0) * 25;
    }
    return report;
}

void NutritionAnalyzer::displayReport(const NutritionReport& report) const
{
    cout << "\n===== NUTRITION ANALYSIS =====\n" << fixed << setprecision(2);

    for (const NutrientResult& nutrient : report.nutrients)
    {
        double percent = nutrient.consumed / nutrient.target * 100;

        cout << "\n" << nutrient.name << ": " << nutrient.consumed
             << " / " << nutrient.target << " " << nutrient.unit
             << " (" << percent << "% of target)\n";

        if (nutrient.consumed >= nutrient.target)
            cout << "Target met.\n";
        else
            cout << "Below target. Remaining: "
                 << nutrient.target - nutrient.consumed << " "
                 << nutrient.unit << ".\n";
    }

    cout << "\nOverall nutrition score: " << report.score << " / 100\n";
    cout << "This is a simple project score, not a medical assessment.\n";
}
