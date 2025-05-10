#include "utility_constraints.h"
#include "types.h"
#include "../third_party/json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;

UtilityConstraints loadUtilityConstraints(const std::string &filepath)
{
    UtilityConstraints U;
    std::ifstream file(filepath);
    json j;
    file >> j;

    for (auto &[key, value] : j.items())
    {
        for (const auto &code : value)
        {
            U[key].insert(code);
        }
    }
    return U;
}
