#include <iostream>
#include <vector>
#include <cmath>
#include "inverse/inverse_jacobi.h"
#include "inverse/inverse_seidel.h"
#include "utils/output.h"

using namespace std;

vector<double> calculateDisplacements(const vector<vector<double>>& A_inv, const vector<double>& b) {
    int n = A_inv.size();
    vector<double> d(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i] += A_inv[i][j] * b[j];
        }
    }
    return d;
}

#include "utils/input.h"

int main() {
    int option;
    do {
        cout << "\n=======================================" << endl;
        cout << "   ANALISE DE ONDAS SISMICAS (SISTEMAS LINEARES)" << endl;
        cout << "=======================================" << endl;
        cout << "1. Gauss-Jacobi (Dados Padrao)" << endl;
        cout << "2. Gauss-Seidel (Dados Padrao)" << endl;
        cout << "3. Gauss-Jacobi (Dados Personalizados)" << endl;
        cout << "4. Gauss-Seidel (Dados Personalizados)" << endl;
        cout << "5. Todos (Comparar Metodos)" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> option;
        cout << endl;

        if (option == 0) break;

        int n;
        vector<vector<double>> A;
        vector<double> b;
        double epsilon;

        bool useStandard = (option == 1 || option == 2);
        bool useCustom = (option == 3 || option == 4);
        bool isComparative = (option == 5);

        if (isComparative) {
            int subOption;
            cout << "--- Modo Comparativo ---" << endl;
            cout << "1. Usar Dados Padrao" << endl;
            cout << "2. Inserir Dados Personalizados" << endl;
            cout << "Opcao: ";
            cin >> subOption;
            if (subOption == 1) useStandard = true;
            else if (subOption == 2) useCustom = true;
            else { cout << "Opcao invalida" << endl; continue; }
        }

        if (useStandard) {
            n = 3;
            A = { 
                {5.0, 3.0, 1.0},
                {5.0, 6.0, 1.0},
                {1.0, 6.0, 7.0}
            };
            b = {1.0, 2.0, 3.0};
            epsilon = 1e-5;
            cout << "--- Utilizando Dados Padrao ---" << endl;
        } else if (useCustom) {
            readSystemData(n, A, b, epsilon);
        } else if (!isComparative) {
            cout << "Opcao invalida" << endl;
            continue;
        }

        if (isComparative) {
            vector<vector<double>> Inv_Jac = inverseJacobi(A, epsilon);
            cout << "\nMatriz Inversa (Gauss-Jacobi):" << endl;
            printMatrix(Inv_Jac);
            vector<double> d_Jac = calculateDisplacements(Inv_Jac, b);
            cout << "Vetor de Deslocamentos {d}:" << endl;
            printVector(d_Jac);
            analyzeSeismicRisk(d_Jac);

            vector<vector<double>> Inv_Sei = inverseSeidel(A, epsilon);
            cout << "\nMatriz Inversa (Gauss-Seidel):" << endl;
            printMatrix(Inv_Sei);
            vector<double> d_Sei = calculateDisplacements(Inv_Sei, b);
            cout << "Vetor de Deslocamentos {d}:" << endl;
            printVector(d_Sei);
            analyzeSeismicRisk(d_Sei);

            printComparativeTable(d_Jac, d_Sei);

        } else {
            vector<vector<double>> Inv_Matrix;
            vector<double> d;
            string metodoNome;

            if (option == 1 || option == 3) {
                metodoNome = "Gauss-Jacobi";
                Inv_Matrix = inverseJacobi(A, epsilon);
            } else {
                metodoNome = "Gauss-Seidel";
                Inv_Matrix = inverseSeidel(A, epsilon);
            }

            cout << "\n=== RESULTADOS: " << metodoNome << " ===" << endl;
            cout << "Matriz Inversa Calculada:" << endl;
            printMatrix(Inv_Matrix);
            d = calculateDisplacements(Inv_Matrix, b);
            cout << "Vetor de Deslocamentos {d}:" << endl;
            printVector(d);
            analyzeSeismicRisk(d);
        }

    } while (option != 0);

    cout << "Programa encerrado" << endl;
    return 0;
}
