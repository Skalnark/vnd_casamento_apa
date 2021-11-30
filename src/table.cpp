#include "table.hpp"
#include <iostream>

Table::Table(){}

Table::Table(int minGuests, int maxGuests)
{
    this->minGuests = minGuests;
    this->maxGuests = maxGuests;
}


bool Table::AddGuest(int guest)
{
    if (guests.size() < maxGuests)
    {
        guests.push_back(guest);
        return true;
    }

    return false;
}

bool Table::IsValid()
{
    return guests.size() >= minGuests;
}

double Table::Evaluate(std::vector<std::vector<double>> adj_matrix)
{
    double total = 0;

    for(int i = 0 ; i < guests.size() ; ++i)
    {
        for(int j = 0 ; j < guests.size() ; ++j)
        {
            if(i != j)
            {
                total += adj_matrix[guests[i]][guests[j]];
            }
        }
    }

    return total;
}
