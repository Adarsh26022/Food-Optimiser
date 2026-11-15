#ifndef HISTORY_H
#define HISTORY_H

#include "Meal.h"
#include "User.h"
#include <string>

// Save or display daily nutrition summaries in a history file.
bool saveTodayHistory(const NutritionTotals& totals,
                      const NutritionTargets& targets,
                      double score,
                      const std::string& filename);

void displayNutritionHistory(const std::string& filename);

#endif
