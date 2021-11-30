#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <string>

struct Table
{
    int minGuests;
    int maxGuests;
};

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
