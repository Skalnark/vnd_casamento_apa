#include "data.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        double bestVND = 0;
        double bestGreed = 0;
        double solutionValue = 0;
        double nVND = 15;
        double nGreed = 100;
        double totalVND = 0;
        double totalGreed = 0;

        int max_iterations = atoi(argv[2]);
        int alpha = atoi(argv[3]);
        double optimal = atoi(argv[4]);
        double totalTime = 0;

        string file = argv[1];
        string filepath = "instancias/" + file;
        cout << "file: " << file << endl
             << endl;

        Data data(filepath);
        Solution sol;

        for (int i = 0; i < nGreed; ++i)
        {
            auto t1 = high_resolution_clock::now();
            sol = Solution(data);
            auto t2 = high_resolution_clock::now();

            duration<double, milli> ms = t2 - t1;
            totalTime += ms.count();

            solutionValue = sol.Value(data.adj_matrix);
            totalGreed += solutionValue;

            if (solutionValue > bestGreed)
                bestGreed = solutionValue;
        }

        cout << "Greed final solution: " << endl;
        sol.Show();
        cout << "Best greed solution: " << bestGreed << endl;
        cout << "Average greed solution: " << totalGreed / nGreed << endl;
        cout << "Greed gap : " << ((optimal - bestGreed) / optimal) * 100 << endl;
        cout << "Average Greed time: " << totalTime / nGreed << " ms" << endl
             << endl
             << endl;

        solutionValue = 0;

        for (int i = 0; i < nVND; i++)
        {
            auto t1 = high_resolution_clock::now();
            sol = Solution(100, sol);

            Solver::VariableNeighborhoodDescent(sol, data.adj_matrix, max_iterations, alpha);

            auto t2 = high_resolution_clock::now();
            duration<double, milli> ms = t2 - t1;

            totalTime += ms.count();

            solutionValue = sol.Value(data.adj_matrix);
            totalVND += solutionValue;

            if (solutionValue > bestVND)
            {
                bestVND = solutionValue;
            }
        }

        cout << "Vnd final solution: " << endl;
        sol.Show();
        cout << "Best VND solution: " << bestVND << endl;
        cout << "Average VND solution: " << totalVND / nVND << endl;
        cout << "VND gap : " << ((optimal - bestVND) / optimal) * 100 << endl;
        cout << "Average VND time: " << totalTime / nVND << " ms" << endl;
    }
    else
    {
        cout << "Wrong number of parameters" << endl;
        cout << "Usage: ./vnd <instance> <max_iterations> <alpha> <optimal_solution>" << endl;
    }

    return 0;
}