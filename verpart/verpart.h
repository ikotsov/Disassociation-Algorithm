#pragma once
#include "../horpart/types.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

// Structure representing a vertical partitioning output per cluster
struct VerPartOutput
{
    std::vector<std::vector<std::vector<std::string>>> record_chunks; // Each chunk is a list of projected records, one per group
    std::vector<std::vector<std::string>> item_chunk;                 // TT: items with support < k, grouped into one chunk per record
    std::vector<std::vector<std::string>> shared_chunks;              // Shared chunks identified during refinement across record chunks
};

/**
 * @brief Performs vertical partitioning with optional refinement on a single cluster
 *
 * Splits items from a horizontally partitioned cluster into groups based on utility constraints,
 * and ensures each group satisfies k-anonymity. Items with support < k are assigned to the TT chunk.
 *
 * @param P The cluster to vertically partition (output from HorPart)
 * @param U Utility constraints (e.g., similarity or hierarchy-based groupings)
 * @param k The k-anonymity threshold (minimum number of records required to support each item)
 * @param m The maximum number of item groups (controls how many attribute sets are formed)
 * @return VerPartOutput object containing record chunks, item chunk, and shared chunks
 */
VerPartOutput VerPart(const Cluster &P, const UtilityConstraints &U, size_t k, size_t m);

/**
 * @brief Exports the full disassociated dataset to a JSON file
 *
 * Converts the output of the VerPart and Refine steps into a JSON format suitable for evaluation.
 *
 * @param all_clusters A vector of VerPartOutput objects (one per horizontal cluster)
 * @param output_file The path to the output JSON file
 */
void exportToJson(const std::vector<VerPartOutput> &all_clusters, const std::string &output_file);

/**
 * @brief Refines clusters by extracting shared chunks across record chunks
 *
 * Identifies common item sets that appear in multiple record chunks and factors them out
 * into shared chunks. This reduces redundancy and increases interpretability.
 *
 * @param all_clusters The output of VerPart for all horizontal clusters
 * @param k The k-anonymity threshold (used to ensure shared chunks meet support criteria)
 */
void Refine(std::vector<VerPartOutput> &all_clusters, size_t k);
