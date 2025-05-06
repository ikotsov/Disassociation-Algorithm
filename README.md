# Purpose

This project is an effort to replicate the disassociation algorithm described in the paper:

**Disassociation for electronic health record privacy**  
_Grigorios Loukides, John Liagouris, Aris Gkoulalas-Divanis and Manolis Terrovitis. Journal of Biomedical Informatics, 2014._  
[Available on ScienceDirect](https://www.sciencedirect.com/science/article/pii/S1532046414001269)

# Project Structure

```
├── data/                      # Contains input dataset and utility constraints
│   ├── dataset.csv
│   └── utility_constraints.json
├── horpart/                   # Core C++ implementation of HorPart
├── third_party/               # Header-only external dependencies
│   └── json.hpp
└──main.cpp                    # Main program entry point
```

# Setup Instructions

1. Clone the repository
2. Download [`json.hpp`](https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp) and place it inside `third_party/json.hpp`. You can do it by running in a terminal:
   ```
   curl -o third_party/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
   ```
3. Open the project in **Visual Studio Code**
4. Ensure local `settings.json` includes:

```json
"code-runner.executorMap": {
  "cpp": "cd $dir && g++ -std=c++17 -I./horpart -I./third_party main.cpp horpart/*.cpp -o main && ./main"
}
```

5. Run `main.cpp`

# Output

The program will load the dataset and utility constraints, apply the HorPart algorithm recursively, and print clustered records.
