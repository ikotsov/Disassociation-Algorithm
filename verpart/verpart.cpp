#include "verpart.h"
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

VerPartOutput VerPart(const Cluster &P, const UtilityConstraints &U, size_t k, size_t m)
{
    VerPartOutput output;

    // Guard: empty input cluster
    if (P.empty())
    {
        std::cout << "[VerPart] Warning: Empty cluster received.\n";
        return output;
    }

    // Step 1: Compute support s(t) for each diagnosis code in the cluster P
    std::unordered_map<std::string, int> support; // support count for each code
    std::unordered_set<std::string> TP;           // set of all distinct codes in P
    for (const auto &record : P)
    {
        for (const auto &code : record)
        {
            support[code]++;
            TP.insert(code);
        }
    }

    // Step 2–4: Move codes with support < k to TT, keep others in TP_remaining
    std::vector<std::string> TT; // item chunk (infrequent items)
    std::set<std::string> TP_remaining;
    for (const auto &code : TP)
    {
        if (support[code] < k)
        {
            TT.push_back(code); // TT finalized
        }
        else
        {
            TP_remaining.insert(code);
        }
    }

    // Step 5: Group TP codes by utility constraint, sort codes in each group by support,
    // then sort groups by the support of the first element
    std::map<std::string, std::vector<std::string>> grouped; // constraint_name → codes
    std::set<std::string> assigned;                          // track codes already grouped
    for (const auto &[constraint_name, codes] : U)
    {
        std::vector<std::string> group;
        for (const auto &code : codes)
        {
            if (TP_remaining.count(code))
            {
                group.push_back(code);
                assigned.insert(code);
            }
        }
        std::sort(group.begin(), group.end(), [&](const std::string &a, const std::string &b)
                  { return support[a] > support[b]; }); // sort within group
        if (!group.empty())
            grouped[constraint_name] = group;
    }

    // Handle unassigned codes not covered by any utility constraint
    for (const auto &code : TP_remaining)
    {
        if (!assigned.count(code))
            grouped["_none_" + code] = {code}; // treated as one-element group
    }

    size_t v = 0; // number of record chunks created

    // Step 6–20: Create record chunks per group
    for (const auto &[group_name, group_codes] : grouped)
    {
        if (group_codes.empty())
        {
            std::cout << "[VerPart] Skipping group " << group_name << " (no valid codes).\n";
            continue;
        }

        std::vector<std::vector<std::string>> projected_group;
        for (const auto &record : P)
        {
            std::vector<std::string> projected;
            for (const auto &code : group_codes)
            {
                if (record.count(code))
                    projected.push_back(code);
            }
            if (!projected.empty())
                projected_group.push_back(projected);
        }

        if (projected_group.size() < k)
        {
            std::cout << "[VerPart] Skipping group " << group_name
                      << " (projected size " << projected_group.size() << " < k=" << k << ").\n";
            continue;
        }

        output.record_chunks.push_back(projected_group);
        v++;
        if (v >= m)
            break; // enforce m-constraint
    }

    // Step 21–22: Construct item chunk (TT)
    std::unordered_set<std::string> item_codes_set;
    for (const auto &record : P)
    {
        for (const auto &code : TT)
        {
            if (record.count(code))
            {
                item_codes_set.insert(code);
            }
        }
    }

    if (item_codes_set.empty())
    {
        std::cout << "[VerPart] No TT chunk created.\n";
    }
    else
    {
        std::vector<std::string> merged_item_codes(item_codes_set.begin(), item_codes_set.end());
        std::sort(merged_item_codes.begin(), merged_item_codes.end()); // deterministic order
        output.item_chunk.push_back(merged_item_codes);                // single merged TT chunk
        std::cout << "[VerPart] TT chunk created with " << merged_item_codes.size() << " codes.\n";
    }

    return output;
}
