#include "History.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct DailyHistoryRecord
{
    string date;
    NutritionTotals totals;
    NutritionTargets targets;
    double score = 0;
};

// Return today's date in YYYY-MM-DD format using the computer's local date.
string getTodayDate()
{
    time_t currentTime = time(nullptr);
    tm* localDate = localtime(&currentTime);

    if (localDate == nullptr)
        return "Unknown-Date";

    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", localDate);
    return date;
}

// Read existing history records from the file.
vector<DailyHistoryRecord> loadHistory(const string& filename)
{
    vector<DailyHistoryRecord> records;
    ifstream file(filename);

    if (!file)
        return records;

    DailyHistoryRecord record;

    while (file >> record.date
                >> record.totals.protein
                >> record.totals.iron
                >> record.totals.calcium
                >> record.totals.fiber
                >> record.totals.cost
                >> record.targets.protein
                >> record.targets.iron
                >> record.targets.calcium
                >> record.targets.fiber
                >> record.score)
    {
        records.push_back(record);
    }

    return records;
}

bool saveTodayHistory(const NutritionTotals& totals,
                      const NutritionTargets& targets,
                      double score,
                      const string& filename)
{
    vector<DailyHistoryRecord> records = loadHistory(filename);
    string today = getTodayDate();

    DailyHistoryRecord newRecord;
    newRecord.date = today;
    newRecord.totals = totals;
    newRecord.targets = targets;
    newRecord.score = score;

    // If today's record already exists, update it instead of adding a duplicate.
    bool updated = false;
    for (DailyHistoryRecord& record : records)
    {
        if (record.date == today)
        {
            record = newRecord;
            updated = true;
            break;
        }
    }

    if (!updated)
        records.push_back(newRecord);

    ofstream file(filename);
    if (!file)
        return false;

    file << fixed << setprecision(6);

    for (const DailyHistoryRecord& record : records)
    {
        file << record.date << ' '
             << record.totals.protein << ' '
             << record.totals.iron << ' '
             << record.totals.calcium << ' '
             << record.totals.fiber << ' '
             << record.totals.cost << ' '
             << record.targets.protein << ' '
             << record.targets.iron << ' '
             << record.targets.calcium << ' '
             << record.targets.fiber << ' '
             << record.score << '\n';
    }

    return file.good();
}

void displayNutritionHistory(const string& filename)
{
    vector<DailyHistoryRecord> records = loadHistory(filename);

    cout << "\n===== NUTRITION HISTORY =====\n";

    if (records.empty())
    {
        cout << "No history records found. Save today's summary first.\n";
        return;
    }

    cout << left << setw(13) << "Date"
         << right << setw(11) << "Protein"
         << setw(10) << "Iron"
         << setw(12) << "Calcium"
         << setw(10) << "Fiber"
         << setw(11) << "Score" << '\n';
    cout << string(67, '-') << '\n';

    cout << fixed << setprecision(2);

    for (const DailyHistoryRecord& record : records)
    {
        cout << left << setw(13) << record.date
             << right << setw(11) << record.totals.protein
             << setw(10) << record.totals.iron
             << setw(12) << record.totals.calcium
             << setw(10) << record.totals.fiber
             << setw(9) << record.score << " / 100\n";
    }

    cout << "\nNote: Each date has one saved summary. Saving again on the same date\n"
         << "updates that day's record. The score uses the targets saved with it.\n";
}
