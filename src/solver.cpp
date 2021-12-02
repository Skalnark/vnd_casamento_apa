#include "solver.hpp"

void Solver::Swap1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix)
{
    for (int i = 0; i < sol.tables.size() - 1; ++i)
    {
        for (int j = 0; j < sol.tables[i].guests.size(); ++j)
        {
            for (int k = 0; k < sol.tables[i + 1].guests.size(); ++k)
            {
                Solution s1(sol);

                double swap = s1.tables[i].guests[j];
                s1.tables[i].guests[j] = s1.tables[i + 1].guests[k];
                s1.tables[i + 1].guests[k] = swap;

                if(s1.Value(adj_matrix) > sol.Value(adj_matrix))
                {
                    sol = s1;
                }
            }
        }
    }
}