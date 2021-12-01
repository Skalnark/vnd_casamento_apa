#include "data.hpp"
#include "solution.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        string file = argv[1];
        string filepath = "instancias/" + file;
        cout << "Initializing..." << endl;
        Data data(filepath);

        Solution solution(data);
        cout << "Done!" << endl;

        cout << "Solution value: " << solution.Value(data.adj_matrix) << endl;

        if (argc >= 3 && string(argv[2]) == "-p")
            data.Show();
        
    }
    else
        cout << "No file specified" << endl;
    
    return 0;
}