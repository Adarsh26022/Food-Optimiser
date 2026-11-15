# Food-Optimiser
# Food Combination Optimizer

## 1. Project Overview

The **Food Combination Optimizer** is a C++ based application developed as part of a B.Tech Computer Science and Engineering Project-Based Learning (PBL) project.

The application helps users manage food items, track their daily nutritional intake, analyze nutrient gaps, and find suitable food combinations based on nutritional requirements and budget.

It uses Object-Oriented Programming (OOP) concepts and Data Structures and Algorithms (DSA) to organize food information, calculate nutrition, generate recommendations, and optimize food combinations.

## 2. Objectives

- Maintain a database of food items and their nutritional values.
- Allow users to add food items to different meals with quantities.
- Calculate daily nutritional intake.
- Compare nutritional intake with user-defined targets.
- Generate food recommendations based on nutrient requirements.
- Find suitable food combinations within a given budget.
- Save and view daily nutritional history.

## 3. Features

1. **Food Database:** Display, add, and search food items.
2. **Meal Management:** Add food items to breakfast, lunch, and dinner with quantities.
3. **Nutrition Tracking:** Calculate the total protein, iron, calcium, fiber, and cost consumed.
4. **Nutrition Analysis:** Compare consumed nutrients with daily targets and calculate an overall nutritional score.
5. **Food Recommendations:** Suggest individual food items based on existing nutrient gaps.
6. **Food Combination Optimization:** Generate and rank food combinations based on nutritional score and budget.
7. **File Handling:** Store food database information for future use.
8. **Nutrition History:** Save and view previous daily nutritional records.

## 4. Technologies Used

- **Programming Language:** C++
- **Compiler Standard:** C++17
- **IDE:** Visual Studio Code
- **File Handling:** C++ file streams

## 5. Concepts Used

### Object-Oriented Programming
- Classes and Objects
- Encapsulation
- Constructors
- Data Abstraction

### Data Structures and Algorithms
- Vectors
- Linear Searching
- Sorting
- Priority Queue
- Bitmasking
- Subset Generation
- File Handling

## 6. Project Structure

| File | Description |
|---|---|
| `main.cpp` | Main menu and integration of all modules |
| `Food.h` / `Food.cpp` | Food class and food database operations |
| `Meal.h` / `Meal.cpp` | Meal management and nutrition calculations |
| `User.h` / `User.cpp` | User nutrition targets |
| `Nutrition.h` / `Nutrition.cpp` | Nutrition analysis and score calculation |
| `Recommendation.h` / `Recommendation.cpp` | Food recommendation system |
| `Optimizer.h` / `Optimizer.cpp` | Food combination optimization |
| `History.h` / `History.cpp` | Saving and viewing nutrition history |
| `foods.txt` | Food database storage file |
| `meal_history.txt` | Daily nutrition history storage file |

## 7. How to Run the Project

### Requirements
- A C++ compiler supporting C++17.
- Visual Studio Code or another C++ development environment.

### Compilation

Open the project folder in the terminal and run:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Food.cpp Meal.cpp User.cpp Nutrition.cpp Recommendation.cpp Optimizer.cpp History.cpp -o main
```

### Execution

On Windows PowerShell:

```powershell
.\main.exe
```

On Linux or macOS:

```bash
./main
```

## 8. How the Application Works

1. The application loads the available food database.
2. The user can add, search, or display food items.
3. Food items can be added to breakfast, lunch, or dinner with their quantities.
4. The application calculates the total nutritional intake.
5. The nutrition analyzer compares the intake with the user's targets.
6. The recommendation module suggests individual foods to address nutrient gaps.
7. The optimizer generates food combinations within the user's budget.
8. The user can save and view nutritional history.

## 9. Limitations

- The application currently tracks four nutrients: protein, iron, calcium, and fiber.
- Nutritional values are based on the values entered in the food database.
- The nutritional score is a simplified calculation and is not a medical assessment.
- The optimizer uses one serving of each selected food in a combination.
- The optimizer supports a maximum of 15 food items for combination generation.
- Meal selections are not permanently stored between application sessions.
- The application currently uses a console-based interface.

## 10. Future Scope

- Add more nutrients and food items.
- Develop a graphical user interface.
- Improve the recommendation algorithm.
- Add user accounts and multiple-user support.
- Store meal details permanently.
- Improve optimization with additional dietary preferences and constraints.

## 11. Conclusion

The Food Combination Optimizer demonstrates the practical application of C++, Object-Oriented Programming, Data Structures and Algorithms, and file handling.

It provides a basic system for tracking nutritional intake, identifying nutrient gaps, recommending food items, and generating budget-based food combinations.

--- 
**Course:** B.Tech Computer Science and Engineering  
**Institution:** Graphic Era Hill University, Dehradun
