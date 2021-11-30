#include "data.hpp"
#include "table.hpp"
#include <iostream>
#include <fstream>
#include <string>

Data::Data(std::string filepath)
{
    std::fstream file(filepath, std::ios_base::in);
    bool tables_found = false;
    bool guests_found = false;

    if (!file)
    {
        std::cout << "Error: File not found!" << std::endl;
        exit(-1);
    }

    std::string line;

    file >> line;
    file >> nGuests;

    file >> line;
    file >> nTables;

    std::cout << "nGuests: " << nGuests << " "
              << "nTables: " << nTables << std::endl;

    while (!(tables_found && guests_found))
    {
        file >> line;

        if (line == "#limites_minimo_maximo_mesas")
        {
            tables = std::vector<Table>(nTables);
            tables_found = true;

            for (int i = 0; i < nTables; ++i)
            {
                int min, max;

                file >> min;
                file >> max;

                Table table(min, max);

                tables[i] = table;
            }
        }

        if (line == "#beneficios")
        {
            adj_matrix = std::vector<std::vector<double>>(nGuests);
            guests_found = true;

            for (int i = 0; i < nGuests; ++i)
            {
                adj_matrix[i] = std::vector<double>(nGuests);
            }
            while (!file.eof())
            {
                int guest;
                int other_guest;
                double benefit;

                file >> guest;
                file >> other_guest;
                file >> benefit;

                adj_matrix[guest][other_guest] = benefit;
            }
        }
    }

    file.close();
}

void Data::Show()
{
    for (int i = 0; i < nGuests; ++i)
    {
        for (int j = 0; j < nGuests; ++j)
        {
            std::cout << adj_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << adj_matrix[47][49] << std::endl;
}