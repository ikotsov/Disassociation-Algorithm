#pragma once
#include "types.h"
#include <vector>
#include <unordered_set>
#include <set>
#include <string>

std::vector<Cluster> HorPart(const Dataset &D,
                             std::unordered_set<std::string> ignore,
                             UtilityConstraints &U,
                             std::set<std::string> u,
                             size_t maxClusterSize);
