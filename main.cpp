#include <iostream>
#include "horpart/dataset.h"
#include "horpart/horpart.h"
#include "horpart/utility.h"

const std::string DATASET_FILE = "data/dataset.csv";
const std::string CONSTRAINTS_FILE = "data/utility_constraints.json";

const size_t k = 3;
const size_t MAX_CLUSTER_SIZE = 2 * k;

int main()
{
    Dataset dataset = readCSV(DATASET_FILE);
    UtilityConstraints U = loadUtilityConstraints(CONSTRAINTS_FILE);
    std::set<std::string> u;

    auto clusters = HorPart(dataset, {}, U, u, MAX_CLUSTER_SIZE);

    int i = 1;
    for (const auto &cluster : clusters)
    {
        std::cout << "Cluster " << i++ << ":\n";
        for (const auto &record : cluster)
        {
            for (const auto &code : record)
                std::cout << code << " ";
            std::cout << "\n";
        }
        std::cout << "-------------------\n";
    }

    return 0;
}
