#pragma once
#include "utility.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> computeFrequency(const Dataset &data, const std::unordered_set<std::string> &ignore);
std::string findMostFrequentCode(const std::unordered_map<std::string, int> &freq);
