#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include "data.hpp"

class Solution
{
private:
    std::vector<Table> tables;

public:
    Solution(Data data);
    double Value(const std::vector<std::vector<double>> &adj_matrix);
};

#endif