#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <string>
#include "table.hpp"

class Data
{
    private:
        std::vector<std::vector<double>> adj_matrix;
        int nGuests;
        int nTables;
        std::vector<Table> tables;

    public:
        Data(std::string filepath);
        void Show();
};

#endif
