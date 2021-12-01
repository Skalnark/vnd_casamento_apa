#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <string>
#include "table.hpp"

class Data
{
    public:
        int nTables;
        int nGuests;
        Data(std::string filepath);
        void Show();
        std::vector<Table> tables;
        std::vector<std::vector<double>> adj_matrix;
        int Seats;
};

#endif
