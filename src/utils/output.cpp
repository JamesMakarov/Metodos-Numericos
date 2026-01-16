#include "output.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector> 
#include <cmath> 

using namespace std;

void printMatrix(const vector<vector<double>>& matrix) {
    if (matrix.empty()) return;

    int precision = 3; 
    int max_width = 0;

    for (const auto& row : matrix) {
        for (double val : row) {
            stringstream ss;
            ss << fixed << setprecision(precision) << val;
            int length = ss.str().length();
            if (length > max_width) max_width = length;
        }
    }

    int field_width = max_width + 2; 

    cout << "----------------------------------------" << endl;
    for (const auto& row : matrix) {
        cout << "|"; 
        for (double val : row) {
            cout << fixed << setprecision(precision) 
                 << setw(field_width) << val; 
        }
        cout << "  |" << endl; 
    }
    cout << "----------------------------------------" << endl;
}

void printVector(const vector<double>& vec) {
    cout << "[ ";
    for (double val : vec) {
        cout << fixed << setprecision(4) << val << " ";
    }
    cout << "]^T" << endl;
}


void analyzeSeismicRisk(const vector<double>& d) {
    bool perigo = false;
    cout << "--- Analise do Risco ---" << endl;
    for (size_t i = 0; i < d.size(); i++) {
        cout << "d" << i+1 << ": " << fixed << setprecision(5) << abs(d[i]) << " cm";
        if (abs(d[i]) > 0.4) {
            cout << " PERIGO: > 0.4";
            perigo = true;
        }
        cout << endl;
    }
    if (perigo) cout << "RESULTADO: Pode ocorrer danos graves" << endl;
    else cout << "RESULTADO: Estrutura está segura" << endl;
}

void printComparativeTable(const vector<double>& d_jacobi, const vector<double>& d_seidel) {
    cout << "\n========================================================" << endl;
    cout << "               QUADRO COMPARATIVO DE RESULTADOS" << endl;
    cout << "========================================================" << endl;
    cout << "| Desloc. | Gauss-Jacobi (cm) | Gauss-Seidel (cm) | Diff |" << endl;
    cout << "--------------------------------------------------------" << endl;
    
    size_t n = d_jacobi.size();
    for(size_t i=0; i<n; i++) {
        double diff = abs(d_jacobi[i] - d_seidel[i]);
        cout << "| d" << i+1 << "      | " 
             << setw(17) << fixed << setprecision(5) << d_jacobi[i] << " | "
             << setw(17) << d_seidel[i] << " | "
             << setw(4) << setprecision(5) << diff << " |" << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}