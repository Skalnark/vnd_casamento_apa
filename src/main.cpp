#include "data.hpp"
#include "solution.hpp"
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

        Solution s2(s1.tables);

        cout << "Starting " << max_iterations << " iterations..." << endl << endl;
        
        while(count < max_iterations)
        {
            double sol2 = s2.Value(data.adj_matrix);
            if(sol2 >= solutionValue)
            {
                solutionValue = sol2;
                s1 = s2;
            }
            s2.Disturb();
            
            ++count;
        }

        cout << "Final solution value: " << solutionValue << endl;


        if (argc == 4 && string(argv[3]) == "-p")
            data.Show();

    }
    else
        cout << "No file specified" << endl;
    
    return 0;
}