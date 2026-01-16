#include "inverse_jacobi.h"
#include "../methods/jacobi.h"
#include <iostream>

using namespace std;

vector<vector<double>> inverseJacobi(const vector<vector<double>>& A, double tol) {
    int n = A.size();
    vector<vector<double>> A_inv(n, vector<double>(n));
    vector<double> vetorIdentidade(n, 0.0);

    for (int j = 0; j < n; j++) {
        fill(vetorIdentidade.begin(), vetorIdentidade.end(), 0.0);
        vetorIdentidade[j] = 1.0; 

        vector<double> colunaResultado = solveJacobi(A, vetorIdentidade, tol, 2000);

        for (int i = 0; i < n; i++) {
            A_inv[i][j] = colunaResultado[i];
        }
    }
    return A_inv;
}
