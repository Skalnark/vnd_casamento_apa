#include "data.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string file = argv[1];
        std::string filepath = "instancias/" + file;
        cout << "Initializing..." << endl;
        Data data(filepath);
        cout << "Done!" << endl;

        cout << argv[2] << endl;

        if (argc >= 2 && string(argv[2]) == "-p")
            data.Show();
    }

    return 0;
}