#include "utils/input.h" 
#include "matrix/matrix.h" 
#include <iostream>

using namespace std;



void readSystemData(int& n, vector<vector<double>>& A, vector<double>& b, double& epsilon) {

    cout << "=== Entrada de Dados ===" << endl;
    cout << "Digite a dimensao do sistema (n): ";
    cin >> n;

    A = zerosMatrix(n, n); 
    cout << "\n--- Digite os termos da Matriz A [" << n << "x" << n << "] ---" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }

    b.resize(n);
    cout << "\n--- Digite os termos do vetor b (termos independentes) ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "]: ";
        cin >> b[i];
    }

    cout << "\n--- Digite a precisao (epsilon) ---" << endl;
    cout << "Ex: 0.001 ou 1e-5: ";
    cin >> epsilon;
    
    cout << "=== Leitura Concluida ===" << endl << endl;
}