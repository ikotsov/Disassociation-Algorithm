#include <iostream>
#include "horpart/dataset.h"
#include "horpart/horpart.h"
#include "horpart/utility.h"

int main()
{
    std::string filename = "data/dataset.csv";
    std::string constraintsFile = "data/utility_constraints.json";

    size_t k = 3;
    size_t maxClusterSize = 2 * k;

    Dataset dataset = readCSV(filename);
    UtilityConstraints U = loadUtilityConstraints(constraintsFile);
    std::set<std::string> u;

    auto clusters = HorPart(dataset, {}, U, u, maxClusterSize);

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
