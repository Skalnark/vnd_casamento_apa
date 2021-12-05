#ifndef _SOLVER_ 
#define _SOLVER_

#include "solution.hpp"
#include <vector>

class Solver 
{
private:
    Solver();

public:
    static void VariableNeighborhoodDescent(Solution& sol, const std::vector<std::vector<double>> &adj_matrix, int max_iterations, int r, int a);
    static void Swap1(int t, int i, int j, Solution &sol);
    static void SearchSwap1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix);
    static void Swap2(int table, int t1, int t2, int nt1, int nt2, Solution &sol);
    static void SearchSwap2(Solution &sol, const std::vector<std::vector<double>> &adj_matrix);
    static void Shift1(int t1, int t2, int i, Solution &sol);
    static void SearchShift1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix);
};

#endif