#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include "data.hpp"

class Solution
{
private:
    static void TryShift1(Solution &sol);
public:
    Solution();
    Solution(const Solution &sol);
    Solution(int n, const Solution &sol);
    Solution(const Data &dt);
    static void Greed(const Data &dt);
    static void RandomNeighbor(Solution &sol, const int k);
    void Show();
    void TwoOpt();
    void ShiftN();
    double Value(const std::vector<std::vector<double>> &adj_matrix);
    std::vector<Table> tables;
    int Seats;
};

#endif