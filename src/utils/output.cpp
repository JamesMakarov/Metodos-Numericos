#include "utils/output.h"
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
    
}