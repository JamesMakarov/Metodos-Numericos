#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

vector<vector<double>> identityVector(int size);
bool isSquared(vector<vector<double>> * matrix, int size);
vector<vector<double>> zerosMatrix(int size);
vector<vector<double>> matrixMultiplier(vector<vector<double>> m1, vector<vector<double>> m2, int size);
vector<vector<double>> transposeMatrix(vector<vector<double>> matrix);
double determinant(vector<vector<double>> matrix, int size);
int lowerTriangularization(vector<vector<double>> * matrix);
void weNeedToInverteSomeLine(vector<vector<double>> * matrix, int i, int * signal);
bool productDefined(int colunaM1, int linhaM2);

#endif
