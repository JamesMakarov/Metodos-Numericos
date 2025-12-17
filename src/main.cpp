#include <iostream>
#include <vector>
#include <cmath>
#include "inverse/exact_inverse.h"

using namespace std;

static vector<vector<double>> multiply(const vector<vector<double>>& A,
                                                 const vector<vector<double>>& B) {
    int n = (int)A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double s = 0.0;
            for (int k = 0; k < n; ++k) s += A[i][k] * B[k][j];
            C[i][j] = s;
        }
    }
    return C;
}

static bool approx_equal(const vector<vector<double>>& M,
                         const vector<vector<double>>& N,
                         double tol) {
    int n = (int)M.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fabs(M[i][j] - N[i][j]) > tol) return false;
        }
    }
    return true;
}

static void print_matrix(const vector<vector<double>>& M) {
    for (const auto& row : M) {
        for (double v : row) cout << v << " ";
        cout << "\n";
    }
}

int main() {
    vector<vector<double>> A = {
        {4.0, 7.0, 2.0},
        {3.0, 6.0, 1.0},
        {2.0, 5.0, 1.0}
    };

    vector<vector<double>> expected_inv = {
        {1.0/3.0, 1.0, -5.0/3.0},
        {-1.0/3.0, 0.0, 2.0/3.0},
        {1.0, -2.0, 1.0}
    };

    auto A_inv = calcutate_inverse(A);
    
    if (A_inv.empty()) {
        cout << "calcutate_inverse retornou matriz vazia\n";
        return 1;
    }

    cout << "A_inv calculada:\n";
    print_matrix(A_inv);

    double tol = 1e-8;
    if (approx_equal(A_inv, expected_inv, tol)) {
        cout << "Teste OK: inversa calculada coincide com inversa conhecida\n";
    } else {
        cout << "Teste Falhou: inversa calculada NAO coincide com inversa conhecida\n";
        cout << "Produto A * A_inv:\n";
        auto prod = multiply(A, A_inv);
        print_matrix(prod);
    }

    return 0;
}
