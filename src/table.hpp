#ifndef _TABLE_
#define _TABLE_

#include <vector>

class Table {
public:
    Table();
    Table(int minGuests, int maxGuests);
    int minGuests;
    int maxGuests;
    std::vector<int> guests;
    bool AddGuest(int guest);
    double Evaluate(std::vector<std::vector<double>> adj_matrix);
    std::vector<std::vector<double>> adj_matrix;
    bool IsValid();
};

#endif