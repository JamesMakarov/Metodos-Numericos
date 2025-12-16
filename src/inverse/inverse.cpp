#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

vector<vector<double>> calcutate_inverse(vector<vector<double>> matrix) {
    int size = matrix.size(); 
    if (!isSquared(&matrix, size) || determinant(matrix, size) == 0) return {}; 

    vector<vector<double>> identity = identityVector(size);

    for (int i = 0; i < size; i++) {
        if (abs(matrix[i][i]) < 1e-9) {
            for (int m = i + 1; m < size; m++) {
                if (abs(matrix[m][i]) > 1e-9) {
                    swap(matrix[i], matrix[m]);
                    swap(identity[i], identity[m]); 
                    break;
                }
            }
        }
        double pivot = matrix[i][i];
        for (int j = i + 1; j < size; j++) {
            double mul_const = -matrix[j][i] / pivot;
            for (int k = 0; k < size; k++) {
                matrix[j][k] += mul_const * matrix[i][k];
                identity[j][k] += mul_const * identity[i][k];
            }
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        double pivot = matrix[i][i];
        
        for (int j = i - 1; j >= 0; j--) {
            double mul_const = -matrix[j][i] / pivot;
            for (int k = 0; k < size; k++) {
                identity[j][k] += mul_const * identity[i][k];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        double pivot = matrix[i][i];
        for (int j = 0; j < size; j++) {
            identity[i][j] /= pivot;
        }
    }
    return identity;
}

vector<vector<double>> identityVector(int size) { 
    vector<double> zeroLine;
    vector<vector<double>> identity;
    for (int i = 0; i < size; i++) zeroLine.push_back(0);
    for(int j = 0; j < size; j++) identity.push_back(zeroLine);
    for (int k = 0; k < size; k++) identity[k][k] = 1;
    return identity;
}

bool isSquared(vector<vector<double>> * matrix, int size) { 
    for (int i = 0; i < size; i++) {
        if((*matrix)[i].size() != size) { 
            cout << "Sua matriz não é quadrada";
            return false;
        }
    }
    return true;
}

double determinant(vector<vector<double>> matrix, int size) { 
    int signal = triangularization(&matrix);

    double det = signal;

    for (int i = 0; i < size; i++) det *= matrix[i][i];

    if (det == 0) cout << "A matriz inserida não tem inversa, pois seu determinante é igual a zero";
    
    return det;
}

void weNeedToInverteSomeLine(vector<vector<double>> * matrix, int i, int * signal) {
    int size = matrix->size();
    for (int m = i + 1; m < size; m++) { 
        if (abs((*matrix)[m][i]) > 1e-9) {
            swap((*matrix)[i], (*matrix)[m]);
            (*signal) *= -1;
            break;
        }
    }
}

int triangularization(vector<vector<double>> * matrix) {
    int size = matrix->size();
    int signal = 1;
    for (int i = 0; i < size; i++) {
        if (abs((*matrix)[i][i]) < 1e-9) { 
            weNeedToInverteSomeLine(matrix, i, &signal);
            if (abs((*matrix)[i][i]) < 1e-9) return 0;
        }
        double pivot = (*matrix)[i][i];
        for (int j = i+1; j < size; j++) {
            double mul_const = -(*matrix)[j][i]/pivot;
            for (int k = 0; k < size; k++) {
                (*matrix)[j][k] = mul_const*(*matrix)[i][k]+(*matrix)[j][k];
            }
        }
    }
    return signal;
}