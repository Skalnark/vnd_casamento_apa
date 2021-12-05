#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        string file = argv[1];
        string filepath = "instancias/" + file;
        cout << "file: " << file << endl
             << endl;
        Data data(filepath);
        double bestSolution = 0;
        double solutionValue = 0;
        double average = 0;
        vector<double> solutions;

        Solution s1(data);
        int count = 0;
        int max_iterations = atoi(argv[2]);
        int alpha = atoi(argv[3]);

        for (int i = 0; i < 100; i++)
        {
            Solution::Disturb(100, s1);

            if (i == 0)
            {
                solutionValue = s1.Value(data.adj_matrix);
                bestSolution = solutionValue;
                std::cout << "Initial Solution: " << std::endl;
                s1.Show();
                cout << endl
                     << "First solution value: " << solutionValue << endl
                     << endl;
            }

            Solver::VariableNeighborhoodDescent(s1, data.adj_matrix, max_iterations, alpha);

            solutionValue = s1.Value(data.adj_matrix);
            solutions.push_back(solutionValue);
            average += solutionValue;

            if (solutionValue > bestSolution)
            {
                bestSolution = solutionValue;
                //cout << "New best solution: " << solutionValue << endl
                //     << endl;
            }
        }

        cout << "Final solution value: " << bestSolution << endl;

        s1.Show();

        /*cout << "Solutions: " << endl;
        for (int i = 0; i < solutions.size(); ++i)
        {
            cout << solutions[i] << " ";
            average += solutions[i];
        }
        std::cout << std::endl;*/

        cout << "Average solution: " << average / 100.0 << endl;
    }
    else
        cout << "No file specified" << endl;

    return 0;
}