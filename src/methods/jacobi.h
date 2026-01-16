#ifndef JACOBI_H
#define JACOBI_H

#include <vector>

using namespace std;
vector<double> solveJacobi(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter);

#endif
