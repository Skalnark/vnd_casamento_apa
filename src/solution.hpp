#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include "data.hpp"

class Solution
{
private:
    static void TryShift1(Solution &sol);
public:
    Solution(Data data);
    Solution(const Solution &sol);
    static void RandomNeighbor(Solution &sol, const int k);
    static void Disturb(int n, Solution &sol);
    void Show();
    void TwoOpt();
    void ShiftN();
    double Value(const std::vector<std::vector<double>> &adj_matrix);
    std::vector<Table> tables;
    int Seats;
};

#endif