#include "jacobi.h"
#include <cmath>
#include <iostream>

using namespace std;

// Limite para detectar divergencia antes de chegar a NaN
const double DIVERGENCE_THRESHOLD = 1e100;

vector<double> solveJacobi(const vector<vector<double>> &A,
                           const vector<double> &b, double tol, int maxIter) {
  int n = A.size();
  vector<double> x(n, 0.0);
  vector<double> x_new(n, 0.0);

  for (int k = 0; k < maxIter; k++) {
    double maxDiff = 0.0;
    for (int i = 0; i < n; i++) {
      double sum = 0.0;
      for (int j = 0; j < n; j++) {
        if (i != j) {
          sum += A[i][j] * x[j];
        }
      }
      x_new[i] = (b[i] - sum) / A[i][i];

      // Detectar divergencia antes de chegar a NaN/Inf
      if (!isfinite(x_new[i]) || abs(x_new[i]) > DIVERGENCE_THRESHOLD) {
        // Retornar valores grandes mas finitos para indicar divergencia
        for (int m = 0; m < n; m++) {
          if (!isfinite(x_new[m])) {
            x_new[m] =
                (x[m] >= 0) ? DIVERGENCE_THRESHOLD : -DIVERGENCE_THRESHOLD;
          }
        }
        return x_new; // Parar iteracao - divergiu
      }

      double diff = abs(x_new[i] - x[i]);
      if (diff > maxDiff)
        maxDiff = diff;
    }
    x = x_new;
    if (maxDiff < tol)
      break;
  }
  return x;
}
