#ifndef INVERSE_INVERSE_H
#define INVERSE_INVERSE_H

#include <vector>

using namespace std;

vector<vector<double>> calcutate_inverse(vector<vector<double>> * matrix);
bool isSquared(std::vector<std::vector<double>>* matrix, int size);
double determinant(std::vector<std::vector<double>> matrix, int size);
void weNeedToInverteSomeLine(std::vector<std::vector<double>>* matrix, int i, int* signal);
int triangularization(std::vector<std::vector<double>>* matrix);

#endif 

