#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <set>

using Record = std::unordered_set<std::string>;
using Dataset = std::vector<Record>;
using Cluster = std::vector<Record>;
using UtilityConstraints = std::unordered_map<std::string, std::set<std::string>>;
