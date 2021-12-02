#include "solution.hpp"
#include <iostream>
#include <random>

Solution::Solution(std::vector<Table> tables)
{
    this->tables = tables;
}

Solution::Solution(Data data)
{
    this->tables = data.tables;

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

    for (int i = 0; i < 100; ++i)
        Disturb();
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

void Solution::Disturb()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, tables.size() - 1);

    int t2 = dist(rng);
    int t1 = dist(rng);
    std::uniform_int_distribution<std::mt19937::result_type> distT1(0, tables[t1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distT2(0, tables[t2].guests.size() - 1);
    int p1 = distT1(rng);
    int p2 = distT2(rng);

    int swap = tables[t1].guests[p1];
    tables[t1].guests[p1] = tables[t2].guests[p2];
    tables[t2].guests[p2] = swap;
}

void Solution::Show()
{
    for (int i = 0; i < tables.size(); ++i)
    {
        tables[i].Show(i);
    }
}