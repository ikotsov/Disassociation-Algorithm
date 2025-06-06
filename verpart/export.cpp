#include "verpart.h"
#include <fstream>
#include "../third_party/json.hpp"

using json = nlohmann::json;

/**
 * @brief Exports a list of VerPartOutput clusters to a JSON file.
 *
 * The JSON structure will contain an array of clusters, each with:
 * - record_chunks: vertically partitioned record groups
 * - item_chunk: the TT chunk (infrequent items)
 * - shared_chunks: chunks shared across record groups (post-refinement)
 *
 * @param all_clusters Vector of VerPartOutput objects from vertical partitioning
 * @param output_file Path to the JSON file to write
 */
void exportToJson(const std::vector<VerPartOutput> &all_clusters, const std::string &output_file)
{
    json j;

    // Iterate over all clusters (each from HorPart + VerPart)
    for (size_t i = 0; i < all_clusters.size(); ++i)
    {
        const auto &cluster = all_clusters[i];
        json cluster_json;

        // Populate cluster structure with its partitioned outputs
        cluster_json["record_chunks"] = cluster.record_chunks;
        cluster_json["item_chunk"] = cluster.item_chunk;
        cluster_json["shared_chunks"] = cluster.shared_chunks;

        // Append to the main JSON object
        j["clusters"].push_back(cluster_json);
    }

    // Write JSON to file with 2-space indentation
    std::ofstream out(output_file);
    out << j.dump(2);
}
