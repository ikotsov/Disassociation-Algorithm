#pragma once
#include "utility.h"

std::vector<Cluster> HorPart(const Dataset &D,
                             std::unordered_set<std::string> ignore,
                             UtilityConstraints &U,
                             std::set<std::string> u,
                             size_t maxClusterSize);
