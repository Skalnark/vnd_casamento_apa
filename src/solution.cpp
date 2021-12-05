#include "solution.hpp"
#include <iostream>
#include <random>
#include "solver.hpp"

Solution::Solution(const Solution &sol)
{
    this->Seats = sol.Seats;
    this->tables = sol.tables;
}

Solution::Solution(Data data)
{
    this->tables = data.tables;
    this->Seats = data.Seats;

    int count = 0;
    int currentTable = 0;

    int guestsPerTable = data.nGuests / data.nTables;

    while (count < data.Seats && currentTable < data.nTables)
    {
        if (tables[currentTable].guests.size() < guestsPerTable && tables[currentTable].AddGuest(count))
        {
            ++count;
        }
        else
        {
            ++currentTable;
        }
    }

    currentTable = 0;
    while (count < data.nGuests)
    {
        if (tables[currentTable].AddGuest(count))
        {
            ++count;
        }
        else
        {
            ++currentTable;
        }
    }
}

double Solution::Value(const std::vector<std::vector<double>> &adj_matrix)
{
    double total = 0;

    for (int i = 0; i < tables.size(); i++)
    {
        if (!tables[i].IsValid())
            return 0;

        total += tables[i].Evaluate(adj_matrix);
    }

    return total;
}

void Solution::Disturb(int n, Solution &sol)
{
    for (int i = 0; i < n; ++i)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, sol.tables.size() - 1);

        int t2 = dist(rng);
        int t1 = dist(rng);
        std::uniform_int_distribution<std::mt19937::result_type> distT1(0, sol.tables[t1].guests.size() - 1);
        std::uniform_int_distribution<std::mt19937::result_type> distT2(0, sol.tables[t2].guests.size() - 1);
        int p1 = distT1(rng);
        int p2 = distT2(rng);

        int swap = sol.tables[t1].guests[p1];
        sol.tables[t1].guests[p1] = sol.tables[t2].guests[p2];
        sol.tables[t2].guests[p2] = swap;
    }
}

void Solution::RandomNeighbor(Solution &sol, int k)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, k);
    int t1 = 0;
    int t2 = 0;
    int g1 = 0;
    int g2 = 0;
    int g1t1 = 0;
    int g2t1 = 0;
    int g1t2 = 0;
    int g2t2 = 0;
    int n = dist(rng);
    std::uniform_int_distribution<std::mt19937::result_type> Shift11(0, sol.tables.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> Shift1G(0, sol.tables[t1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> swap1(0, sol.tables.size() - 2);
    std::uniform_int_distribution<std::mt19937::result_type> swap1g1(0, sol.tables[t1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> swap1g2(0, sol.tables[t1 + 1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> table(0, sol.tables.size() - 2);
    std::uniform_int_distribution<std::mt19937::result_type> guest1t1(0, sol.tables[t1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> guest2t2(0, sol.tables[t1 + 1].guests.size() - 1);

    switch (3)
    {
    case 1:
        Solution::TryShift1(sol);
        break;
    case 2:
        t1 = swap1(rng);

        swap1g1 = std::uniform_int_distribution<std::mt19937::result_type>(0, sol.tables[t1].guests.size() - 1);
        g1 = swap1g1(rng);

        swap1g2 = std::uniform_int_distribution<std::mt19937::result_type>(0, sol.tables[t1 + 1].guests.size() - 1);

        g2 = swap1g2(rng);

        Solver::Swap1(t1, g1, g2, sol);
        break;
    case 3:
        t1 = table(rng);
        guest1t1 = std::uniform_int_distribution<std::mt19937::result_type>(0, sol.tables[t1].guests.size() - 1);
        g1t1 = guest1t1(rng);
        g2t1 = guest1t1(rng);

        guest2t2 = std::uniform_int_distribution<std::mt19937::result_type>(0, sol.tables[t1 + 1].guests.size() - 1);
        g1t2 = guest2t2(rng);
        g2t2 = guest2t2(rng);

        if (g1t2 == g2t2 || g1t1 == g2t1)
            return;

        /*        std::cout << "----------------------" << std::endl;
                sol.Show();
                std::cout << "Swapping: " << g1t1 << ", " << g2t1 << " from table " << t1
                          << " and: " << g1t2 << ", " << g2t2 << " from table " << t1 + 1 << std::endl;

                sol.Show();
                std::cout << "----------------------" << std::endl;*/
        Solver::Swap2(t1, g1t1, g2t1, g1t2, g2t2, sol);
        break;
    default:
        break;
    }
}

void Solution::Show()
{
    std::cout << "-----------------------" << std::endl;
    for (int i = 0; i < tables.size(); ++i)
    {
        tables[i].Show(i);
    }
    std::cout << "-----------------------" << std::endl;
}

void Solution::TryShift1(Solution &sol)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, sol.tables.size() - 1);

    int l1 = 0;
    int l2 = 0;
    for (int i = 0; i < sol.tables.size(); ++i)
    {
        if (sol.tables[i].CanGive())
        {
            l1 = i;
            break;
        }
    }

    if (l1 == sol.tables.size())
        return;

    for (int i = l1 + 1; i < sol.tables.size(); ++i)
    {
        if (sol.tables[i].CanTake())
        {
            l2 = i;
        }
    }

    if (l2 <= l1)
        return;

    int t1 = 0;
    int t2 = 0;

    if (l1 < l2 + 2)
    {

        dist = std::uniform_int_distribution<std::mt19937::result_type>(0, l1);
        t1 = dist(rng);
        dist = std::uniform_int_distribution<std::mt19937::result_type>(0, l2);
        t2 = dist(rng);

        while (t1 == t2)
            t2 = dist(rng);
    }
    else
    {
        t1 = l1;
        t2 = l2;
    }

    dist = std::uniform_int_distribution<std::mt19937::result_type>(0, sol.tables[t1].guests.size() - 1);

    int guest = dist(rng);

    Solver::Shift1(t1, t2, guest, sol);
}