#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        string file = argv[1];
        string filepath = "instancias/" + file;
        cout << "file: " << file << endl
             << endl;
        Data data(filepath);
        double bestSolution = 0;
        double solutionValue = 0;
        double greed = 0;
        double nSolutions = 100;
        double average = 0;

        Solution s1(data);
        int count = 0;
        int max_iterations = atoi(argv[2]);
        int alpha = atoi(argv[3]);
        int optimal = atoi(argv[4]);

        for (int i = 0; i < nSolutions; i++)
        {

            if (i == 0)
            {
                solutionValue = s1.Value(data.adj_matrix);
                bestSolution = solutionValue;
                cout << endl
                     << "First solution value: " << solutionValue << endl;
                std::cout << "Initial Solution: " << std::endl;
                s1.Show();
            }
            // if (i < 10)
            Solution::Disturb(100, s1);
            // else
            //     s1 = Solution(data);

            Solver::VariableNeighborhoodDescent(s1, data.adj_matrix, max_iterations, alpha);

            solutionValue = s1.Value(data.adj_matrix);
            average += solutionValue;

            if (solutionValue > bestSolution)
            {
                bestSolution = solutionValue;
            }
        }

        cout << "Final solution: " << endl;
        s1.Show();
        average = average / nSolutions;
        cout << "Final solution value: " << bestSolution << endl;
        cout << "Average solution: " << average << endl;
        cout << "Best greed solution: " << greed << endl;
        cout << "Gap : " << ((optimal - bestSolution) / optimal) * 100 << endl;
    }
    else
    {
        cout << "Wrong number of parameters" << endl;
        cout << "Usage: ./vnd <instance> <max_iterations> <alpha>" << endl;
    }

    return 0;
}