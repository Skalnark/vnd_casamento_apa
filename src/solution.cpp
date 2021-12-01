#include "solution.hpp"
#include <iostream>
#include <random>

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

    Randomize();

    std::cout << "Initial Solution created" << std::endl;

    for (int i = 0; i < data.nTables; ++i)
    {
        tables[i].Show(i);
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

void Solution::Randomize()
{

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 4);
    std::uniform_int_distribution<std::mt19937::result_type> dist10(10, 30);

    int times = dist10(rng);

    for (int i = 0; i < times; ++i)
    {
        Disturb(dist4(rng));
    }
}

void Solution::Disturb(int n)
{
    switch (n)
    {
    case 0:
        TwoOpt();
        break;
    case 1:
        // ShiftN(tables, 1);
        break;
    case 2:
        // ShiftN(tables, 2);
        break;
    case 3:
        // ShiftN(tables, 3);
        break;
    default:
        break;
    }
}

void Solution::TwoOpt()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, tables.size() - 1);

    int t1 = dist(rng);
    int t2 = dist(rng);

    std::uniform_int_distribution<std::mt19937::result_type> distT1(0, tables[t1].guests.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distT2(0, tables[t2].guests.size() - 1);

    int p1 = distT1(rng);
    int p2 = distT2(rng);

    //std::cout << "Swapping " << tables[t1].guests[p1] << " from position " << p1 << ", table: " << t1 << " with " << tables[t2].guests[p2] << " from position " << p2 << ", table: " << t2 << std::endl;
 
    int swap = tables[t1].guests[p1];
    tables[t1].guests[p1] = tables[t2].guests[p2];
    tables[t2].guests[p2] = swap;
}