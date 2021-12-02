#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        string file = argv[1];
        string filepath = "instancias/" + file;
        cout << "Initializing..." << endl;
        Data data(filepath);

        Solution s1(data);
        int count = 0;
        int max_iterations = atoi(argv[2]);

        double solutionValue = s1.Value(data.adj_matrix);

        cout << endl << "First solution value: " << solutionValue << endl << endl;

        cout << "Starting " << max_iterations << " iterations..." << endl << endl;
        
        while(count < max_iterations)
        {
            Solver::Swap1(s1, data.adj_matrix);
            ++count;
        }

        solutionValue = s1.Value(data.adj_matrix);

        cout << "Final solution value: " << solutionValue << endl;


        if (argc == 4 && string(argv[3]) == "-p")
            data.Show();

    }
    else
        cout << "No file specified" << endl;
    
    return 0;
}