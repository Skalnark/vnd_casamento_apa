#include "solver.hpp"
#include <iostream>

void Solver::VariableNeighborhoodDescent(Solution &sol, const std::vector<std::vector<double>> &adj_matrix, int max_iter, int a)
{
    int count = 0;
    int r = 4;

    Solution best_sol(sol);
    while (count <= max_iter)
    {
        int k = 1;
        while (k <= r)
        {
            Solution current(best_sol);
            Solution::Disturb(a, current);

            switch (k)
            {
            case 1:
                SearchSwap1(current, adj_matrix);
                break;
            case 2:
                SearchShift1(current, adj_matrix);
                break;
            case 3:
                SearchSwap2(current, adj_matrix);
                break;
            case 4:
                SearchShift2(current, adj_matrix);
                break;
            default:
                break;
            }

            if (current.Value(adj_matrix) > best_sol.Value(adj_matrix))
            {
                best_sol = current;
                k = 1;
                count = 0;
            }
            else
            {
                k++;
            }
        }
        count++;
    }

    if (best_sol.Value(adj_matrix) > sol.Value(adj_matrix))
    {
        sol = best_sol;
    }
}

void Solver::SearchSwap1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix)
{
    for (int i = 0; i < sol.tables.size() - 1; ++i)
    {
        for (int j = 0; j < sol.tables[i].guests.size(); ++j)
        {
            for (int k = 0; k < sol.tables[i + 1].guests.size(); ++k)
            {
                Solution s1(sol);

                Swap1(i, j, k, s1);

                if (s1.Value(adj_matrix) > sol.Value(adj_matrix))
                {
                    // std::cout << "Swapping " << i << " and " << j << " from tables " << k << " and " << k + 1 << std::endl;
                    // s1.Show();
                    // std::cout << "New best. From  " << sol.Value(adj_matrix) << " to " << s1.Value(adj_matrix) << std::endl;

                    sol = s1;
                }
            }
        }
    }
}

void Solver::SearchSwap2(Solution &sol, const std::vector<std::vector<double>> &adj_matrix)
{
    for (int t = 0; t < sol.tables.size() - 1; ++t)
    {
        for (int i = 0; i < sol.tables[t].guests.size() - 1; ++i)
        {
            for (int j = i + 1; j < sol.tables[t].guests.size(); ++j)
            {
                for (int k = 0; k < sol.tables[t + 1].guests.size() - 1; ++k)
                {
                    for (int l = k + 1; l < sol.tables[t + 1].guests.size(); ++l)
                    {
                        Solution s1(sol);
                        Swap2(t, i, j, k, l, s1);

                        if (s1.Value(adj_matrix) > sol.Value(adj_matrix))
                        {
                            // std::cout << "Swapping " << i << " and " << j << " from table " << t
                            //<< " with " << k << " and " << l << " from table " << t + 1 << std::endl;

                            // s1.Show();
                            // std::cout << "New best. From  " << sol.Value(adj_matrix) << " to " << s1.Value(adj_matrix) << std::endl;
                            sol = s1;
                        }
                    }
                }
            }
        }
    }
}

void Solver::SearchShift1(Solution &sol, const std::vector<std::vector<double>> &adj_matrix)
{
    for (int t1 = 0; t1 < sol.tables.size(); ++t1)
    {
        for (int t2 = 0; t2 < sol.tables.size(); ++t2)
        {
            if (t1 != t2)
                if (sol.tables[t1].guests.size() > sol.tables[t1].minGuests)
                    for (int i = 0; i < sol.tables[t1].guests.size(); ++i)
                    {
                        Solution s1(sol);
                        Shift1(t1, t2, i, s1);

                        if (s1.Value(adj_matrix) > sol.Value(adj_matrix))
                        {
                            sol = s1;
                        }
                    }
        }
    }
}

void Solver::SearchShift2(Solution &sol, const std::vector<std::vector<double>> &adj_matrix)
{
    for (int t1 = 0; t1 < sol.tables.size() - 1; ++t1)
    {
        for (int t2 = 0; t2 < sol.tables.size(); ++t2)
        {
            for (int i = 0; i < sol.tables[t1].guests.size(); ++i)
            {
                for (int j = 0; j < sol.tables[t2].guests.size(); ++j)
                {
                    Solution s1(sol);
                    Shift2(t1, t2, i, j, s1);

                    if (s1.Value(adj_matrix) > sol.Value(adj_matrix))
                    {
                        sol = s1;
                    }
                }
            }
        }
    }
}

void Solver::Swap1(int t, int i, int j, Solution &sol)
{
    double swap = sol.tables[t].guests[i];
    sol.tables[t].guests[i] = sol.tables[t + 1].guests[j];
    sol.tables[t + 1].guests[j] = swap;
}

void Solver::Swap2(int table, int t1, int t2, int nt1, int nt2,
                   Solution &sol)
{
    double swap1 = sol.tables[table].guests[t1];
    double swap2 = sol.tables[table].guests[t2];

    sol.tables[table].guests[t1] = sol.tables[table + 1].guests[nt1];
    sol.tables[table].guests[t2] = sol.tables[table + 1].guests[nt2];

    sol.tables[table + 1].guests[nt1] = swap1;
    sol.tables[table + 1].guests[nt2] = swap2;
}

void Solver::Shift1(int t1, int t2, int i, Solution &sol)
{
    double guest = sol.tables[t1].guests[i];
    if (sol.tables[t1].CanGive() && sol.tables[t2].AddGuest(guest))
    {
        sol.tables[t1].guests.erase(sol.tables[t1].guests.begin() + i);
    }
}

void Solver::Shift2(int t1, int t2, int i, int j, Solution &sol)
{
    if (i > sol.tables[t1].guests.size() - 1)
        return;

    double guest1 = sol.tables[t1].guests[i];
    bool changed = false;

    if (sol.tables[t1].CanGive() && sol.tables[t2].CanTake())
    {
        if (sol.tables[t2].AddGuest(guest1))
        {
            changed = true;
            sol.tables[t1].guests.erase(sol.tables[t1].guests.begin() + i);
        }
    }

    if (j > sol.tables[t1].guests.size() - 1)
        return;

    double guest2 = sol.tables[t1].guests[j];
    if (sol.tables[t1].CanGive() && sol.tables[t2].CanTake())
    {
        if (sol.tables[t2].AddGuest(guest2))
        {
            changed = true;
            sol.tables[t1].guests.erase(sol.tables[t1].guests.begin() + j);
        }
    }
}
