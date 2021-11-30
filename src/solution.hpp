#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include "data.hpp"

class Solution
{
public:
    Solution(std::vector<std::vector<double>> adj_matrix, std::vector<Table> tables);
    double Value();
};

#endif