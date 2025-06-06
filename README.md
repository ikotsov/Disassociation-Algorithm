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
├── horpart/                   # Horizontal partitioning logic
├── verpart/                   # Vertical partitioning and refinement logic
├── third_party/               # Header-only external dependencies
│   └── json.hpp
└──main.cpp                    # Main program entry point
```

# Setup Instructions

1. Clone the repository
2. Create the `third_party/` folder
3. Download [`json.hpp`](https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp) and place it inside `third_party/json.hpp`. You can do it by running in a terminal:
   ```
   curl -o third_party/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
   ```
4. Open the project in **Visual Studio Code**
5. Ensure local `settings.json` includes:

```json
"code-runner.executorMap": {
   "cpp": "cd $dir && g++ -std=c++17 -I./horpart -I./verpart -I./third_party main.cpp horpart/*.cpp verpart/*.cpp -o main && ./main"
}
```

or if you are on windows:

```json
  "code-runner.executorMap": {
    "cpp": "cd $dir && g++ -std=c++17 -I./horpart -I./third_party main.cpp horpart/*.cpp -o main.exe && main.exe"
  }
```

5. Run `main.cpp`

# Output

The program loads the dataset and utility constraints, applies the HorPart algorithm recursively to cluster records horizontally, then performs vertical partitioning (VerPart) on each cluster, followed by an optional refining step. The final disassociated dataset is exported to a JSON file.
