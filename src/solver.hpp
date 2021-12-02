#ifndef _SOLVER_ 
#define _SOLVER_

#include "solution.hpp"
#include <vector>

class Solver 
{
private:
    Solver();

public:
    static void Swap1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix);
};

#endif