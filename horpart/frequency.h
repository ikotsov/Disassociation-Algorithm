#pragma once
#include "types.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

std::unordered_map<std::string, int> computeFrequency(const Dataset &data, const std::unordered_set<std::string> &ignore);
std::string findMostFrequentCode(const std::unordered_map<std::string, int> &freq);
