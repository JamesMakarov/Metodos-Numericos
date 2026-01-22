#include "matrix.h"
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

vector<vector<double>> identityVector(int size) {
  vector<double> zeroLine;
  vector<vector<double>> identity;
  for (int i = 0; i < size; i++)
    zeroLine.push_back(0);
  for (int j = 0; j < size; j++)
    identity.push_back(zeroLine);
  for (int k = 0; k < size; k++)
    identity[k][k] = 1;
  return identity;
}

double determinant(vector<vector<double>> matrix, int size) {
  int signal = lowerTriangularization(&matrix);
  double det = signal;

  for (int i = 0; i < size; i++)
    det *= matrix[i][i];

  if (det == 0)
    cout << "A matriz inserida nao tem inversa, pois seu determinante e igual "
            "a zero"
         << endl;

  return det;
}

int lowerTriangularization(vector<vector<double>> *matrix) {
  int size = matrix->size();
  int signal = 1;

  for (int i = 0; i < size; i++) {
    if (abs((*matrix)[i][i]) < 1e-8) {
      weNeedToInverteSomeLine(matrix, i, &signal);
      if (abs((*matrix)[i][i]) < 1e-9)
        return 0;
    }
    double pivot = (*matrix)[i][i];
    for (int j = i + 1; j < size; j++) {
      double mul_const = -(*matrix)[j][i] / pivot;
      for (int k = 0; k < size; k++) {
        (*matrix)[j][k] = mul_const * (*matrix)[i][k] + (*matrix)[j][k];
      }
    }
  }
  return signal;
}

int upperTriangulazation(vector<vector<double>> *matrix) {
  int size = matrix->size();
  int signal = 1;
  for (int i = size - 1; i > 0; i--) {
    if (abs((*matrix)[i][i]) < 1e-9) {
      weNeedToInverteSomeLine(matrix, i, &signal);
      if (abs((*matrix)[i][i]) < 1e-9)
        return 0;
    }
    double pivot = (*matrix)[i][i];
    for (int j = i - 1; j >= 0; j--) {
      double mul_const = (*matrix)[j][i] / pivot;
      for (int k = 0; k <= i; k++) {
        (*matrix)[j][k] = (*matrix)[j][k] - (mul_const * (*matrix)[i][k]);
      }
      (*matrix)[j][i] = 0.0;
    }
  }
  return signal;
}

void weNeedToInverteSomeLine(vector<vector<double>> *matrix, int i,
                             int *signal) {
  int size = matrix->size();
  for (int m = i + 1; m < size; m++) {
    if (abs((*matrix)[m][i]) > 1e-9) {
      swap((*matrix)[i], (*matrix)[m]);
      (*signal) *= -1;
      break;
    }
  }
}

bool isSquared(vector<vector<double>> *matrix, int size) {
  for (int i = 0; i < size; i++) {
    if ((*matrix)[i].size() != static_cast<size_t>(size)) {
      cout << "Sua matriz nao e quadrada" << endl;
      return false;
    }
  }
  return true;
}

vector<vector<double>> zerosMatrix(int linha, int coluna) {
  vector<double> zeroLine;
  vector<vector<double>> zerosMatrix;
  for (int i = 0; i < coluna; i++)
    zeroLine.push_back(0);
  for (int j = 0; j < linha; j++)
    zerosMatrix.push_back(zeroLine);
  return zerosMatrix;
}

vector<vector<double>> transposeMatrix(vector<vector<double>> matrix) {
  if (matrix.empty()) {
    cout << "A matrix para a funcao de transposicao e vazia!" << endl;
    return {};
  }

  vector<vector<double>> result = zerosMatrix(matrix[0].size(), matrix.size());

  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

bool productDefined(int colunaM1, int linhaM2) {
  if (colunaM1 != linhaM2)
    cout << "A matriz m1 e m2 nao tem produto definido.\n";
  return colunaM1 == linhaM2;
}

vector<vector<double>> matrixMultiplier(vector<vector<double>> m1,
                                        vector<vector<double>> m2, int size) {

  if (m1.empty() || m2.empty() || !productDefined(m1[0].size(), m2.size()))
    return {};

  vector<vector<double>> result = zerosMatrix(m1.size(), m2[0].size());
  vector<vector<double>> m2T = transposeMatrix(m2);

  for (size_t i = 0; i < m1.size(); i++) {
    for (size_t j = 0; j < m2[0].size(); j++) {
      double sum = 0;
      for (size_t k = 0; k < m1[0].size(); k++) {
        sum += m1[i][k] * m2T[j][k];
      }
      result[i][j] = sum;
    }
  }

  return result;
}