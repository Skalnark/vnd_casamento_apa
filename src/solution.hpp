#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include "data.hpp"

class Solution
{
public:
    Solution(Data data);
    Solution(const Solution &sol);
    void Disturb();
    void Show();
    void TwoOpt();
    void ShiftN();
    double Value(const std::vector<std::vector<double>> &adj_matrix);
    std::vector<Table> tables;
    int Seats;
};

#endif