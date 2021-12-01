#include "solution.hpp"
#include <iostream>

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

    std::cout << "Initial Solution created" << std::endl;

    for(int i = 0; i < data.nTables; ++i)
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