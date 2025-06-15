#include "horpart.h"
#include "frequency.h"
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>

std::vector<Cluster> HorPart(const Dataset &D,
                             std::unordered_set<std::string> ignore,
                             UtilityConstraints &U,
                             std::set<std::string> u,
                             size_t maxClusterSize)
{

    if (D.size() < maxClusterSize)
        return {D};

    // Step 1: Collect T (diagnosis codes in D)
    std::unordered_set<std::string> T;
    for (const auto &record : D)
    {
        for (const auto &code : record)
        {
            T.insert(code);
        }
    }

    // Step 2: Collect T_U (diagnosis codes in all U)
    std::unordered_set<std::string> T_U;
    for (const auto &[_, constraintSet] : U)
    {
        T_U.insert(constraintSet.begin(), constraintSet.end());
    }

    // Step 3: Compute (T - ignore)
    std::unordered_set<std::string> T_minus_ignore;
    for (const auto &code : T)
    {
        if (ignore.find(code) == ignore.end())
        {
            T_minus_ignore.insert(code);
        }
    }

    // Step 4: Condition checks
    std::string a;
    std::unordered_map<std::string, int> freq;

    // Case 1: (T - ignore) ∩ u ≠ ∅
    if (!u.empty())
    {
        std::unordered_set<std::string> intersection;
        for (const auto &code : T_minus_ignore)
        {
            if (u.find(code) != u.end())
            {
                intersection.insert(code);
            }
        }
        if (!intersection.empty())
        {
            freq = computeFrequency(D, ignore);
            int maxCount = -1;
            for (const auto &code : intersection)
            {
                if (freq[code] > maxCount)
                {
                    maxCount = freq[code];
                    a = code;
                }
            }
        }
    }

    // Case 2: (T - ignore) ∩ T_U ≠ ∅
    if (a.empty())
    {
        std::unordered_set<std::string> intersection;
        for (const auto &code : T_minus_ignore)
        {
            if (T_U.find(code) != T_U.end())
            {
                intersection.insert(code);
            }
        }
        if (!intersection.empty())
        {
            freq = computeFrequency(D, ignore);
            int maxCount = -1;
            for (const auto &code : intersection)
            {
                if (freq[code] > maxCount)
                {
                    maxCount = freq[code];
                    a = code;
                }
            }
            // Update u with constraint that a belongs to
            for (const auto &[key, constraintSet] : U)
            {
                if (constraintSet.find(a) != constraintSet.end())
                {
                    u = constraintSet;
                    break;
                }
            }
        }
    }

    // Case 3: Just take most frequent
    if (a.empty())
    {
        freq = computeFrequency(D, ignore);
        a = findMostFrequentCode(freq);
        u.clear();
    }

    if (a.empty())
    {
        std::cout << "[HorPart] No valid splitting code found — returning cluster of size " << D.size() << "\n";
        return {D};
    }

    // Partition dataset based on 'a'
    ignore.insert(a);
    Dataset D1, D2;
    for (const auto &record : D)
    {
        if (record.find(a) != record.end())
        {
            D1.push_back(record);
        }
        else
        {
            D2.push_back(record);
        }
    }

    std::cout << "[HorPart] Splitting on '" << a << "' → D1 size: " << D1.size()
              << ", D2 size: " << D2.size() << "\n";

    auto clusters1 = HorPart(D1, ignore, U, u, maxClusterSize);
    auto clusters2 = HorPart(D2, ignore, U, {}, maxClusterSize);

    clusters1.insert(clusters1.end(), clusters2.begin(), clusters2.end());
    return clusters1;
}
