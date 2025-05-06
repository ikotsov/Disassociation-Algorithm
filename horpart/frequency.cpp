#include "frequency.h"

std::unordered_map<std::string, int> computeFrequency(const Dataset &data, const std::unordered_set<std::string> &ignore)
{
    std::unordered_map<std::string, int> freq;
    for (const auto &record : data)
    {
        for (const auto &code : record)
        {
            if (ignore.find(code) == ignore.end())
            {
                freq[code]++;
            }
        }
    }
    return freq;
}

std::string findMostFrequentCode(const std::unordered_map<std::string, int> &freq)
{
    std::string mostFrequent;
    int maxCount = -1;
    for (const auto &[code, count] : freq)
    {
        if (count > maxCount)
        {
            maxCount = count;
            mostFrequent = code;
        }
    }
    return mostFrequent;
}
