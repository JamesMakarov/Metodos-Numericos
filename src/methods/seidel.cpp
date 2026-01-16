#include "seidel.h"
#include <cmath>
#include <iostream>

using namespace std;

vector<double> solveSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0);

    for (int k = 0; k < maxIter; k++) {
        double maxDiff = 0.0;
        vector<double> x_old = x;
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        for(int i = 0; i < n; i++) {
            double diff = abs(x[i] - x_old[i]);
            if(diff > maxDiff) maxDiff = diff;
        }
        if (maxDiff < tol) break;
    }
    return x;
}
