#ifndef SEIDEL_H
#define SEIDEL_H

#include <vector>

using namespace std;
vector<double> solveSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter);

#endif
