#include "dataset.h"
#include <fstream>
#include <sstream>
#include <string>

Dataset readCSV(const std::string &filename)
{
    Dataset dataset;
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line))
    {
        Record record;
        std::stringstream ss(line);
        std::string code;
        while (getline(ss, code, ','))
        {
            record.insert(code);
        }
        dataset.push_back(record);
    }
    return dataset;
}
