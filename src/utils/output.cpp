#include "output.h"
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

// Constantes para deteccao de overflow/divergencia
const double OVERFLOW_THRESHOLD =
    1e10; // Valores acima disso indicam divergencia

// Verifica se um valor e considerado "overflow" (divergiu)
bool isOverflow(double val) {
  return !isfinite(val) || abs(val) > OVERFLOW_THRESHOLD;
}

// Formata um valor para exibicao, usando notacao cientifica compacta se
// necessario
string formatValue(double val, int precision = 3) {
  stringstream ss;

  if (!isfinite(val)) {
    if (isnan(val))
      return "     NaN     ";
    return val > 0 ? "    +Inf     " : "    -Inf     ";
  }

  if (abs(val) > OVERFLOW_THRESHOLD) {
    // Notacao cientifica compacta para valores muito grandes
    ss << scientific << setprecision(2) << val;
    string result = ss.str();
    // Limitar tamanho maximo
    if (result.length() > 13) {
      result = result.substr(0, 13);
    }
    return result;
  }

  // Valores normais
  ss << fixed << setprecision(precision) << val;
  return ss.str();
}

// Verifica se uma matriz contem valores de overflow (divergencia)
bool matrixHasOverflow(const vector<vector<double>> &matrix) {
  for (const auto &row : matrix) {
    for (double val : row) {
      if (isOverflow(val))
        return true;
    }
  }
  return false;
}

// Verifica se um vetor contem valores de overflow (divergencia)
bool vectorHasOverflow(const vector<double> &vec) {
  for (double val : vec) {
    if (isOverflow(val))
      return true;
  }
  return false;
}

void printMatrix(const vector<vector<double>> &matrix) {
  if (matrix.empty())
    return;

  bool hasOverflow = matrixHasOverflow(matrix);

  if (hasOverflow) {
    cout << "\n[!] AVISO: O metodo NAO CONVERGIU! Valores abaixo sao invalidos."
         << endl;
    cout << "    A matriz de entrada pode nao satisfazer o criterio de "
            "convergencia."
         << endl;
  }

  int precision = 3;
  int max_width = 0;
  const int MAX_FIELD_WIDTH = 15; // Limita largura maxima do campo

  for (const auto &row : matrix) {
    for (double val : row) {
      string formatted = formatValue(val, precision);
      int length = formatted.length();
      if (length > max_width)
        max_width = length;
    }
  }

  // Limitar largura maxima
  if (max_width > MAX_FIELD_WIDTH)
    max_width = MAX_FIELD_WIDTH;
  int field_width = max_width + 2;

  int n = matrix[0].size();
  int table_width = (field_width * n) + 4;
  string separator(table_width, '-');

  cout << separator << endl;
  for (const auto &row : matrix) {
    cout << "|";
    for (double val : row) {
      string formatted = formatValue(val, precision);
      // Truncar se muito longo
      if (formatted.length() > (size_t)field_width) {
        formatted = formatted.substr(0, field_width - 1) + "~";
      }
      cout << setw(field_width) << formatted;
    }
    cout << "  |" << endl;
  }
  cout << separator << endl;
}

void printVector(const vector<double> &vec) {
  bool hasOverflow = vectorHasOverflow(vec);

  if (hasOverflow) {
    cout << "\n[!] AVISO: O metodo NAO CONVERGIU! Valores abaixo sao invalidos."
         << endl;
  }

  cout << "[ ";
  for (double val : vec) {
    cout << formatValue(val, 4) << " ";
  }
  cout << "]^T" << endl;
}

void analyzeSeismicRisk(const vector<double> &d) {
  // Primeiro verifica se houve divergencia
  if (vectorHasOverflow(d)) {
    cout << "--- Analise do Risco ---" << endl;
    cout << "[!] ERRO: Impossivel analisar risco - metodo nao convergiu!"
         << endl;
    cout << "    Os valores calculados sao invalidos (overflow/divergencia)."
         << endl;
    cout << "    Verifique se a matriz satisfaz o criterio de convergencia"
         << endl;
    cout << "    (diagonal dominante) para o metodo iterativo utilizado."
         << endl;
    cout << "RESULTADO: Analise INCONCLUSIVA (dados invalidos)" << endl;
    return;
  }

  bool perigo = false;
  cout << "--- Analise do Risco ---" << endl;
  for (size_t i = 0; i < d.size(); i++) {
    cout << "d" << i + 1 << ": " << fixed << setprecision(5) << abs(d[i])
         << " cm";
    if (abs(d[i]) > 0.4) {
      cout << " PERIGO: > 0.4";
      perigo = true;
    }
    cout << endl;
  }
  if (perigo)
    cout << "RESULTADO: Pode ocorrer danos graves" << endl;
  else
    cout << "RESULTADO: Estrutura esta segura" << endl;
}

void printComparativeTable(const vector<double> &d_jacobi,
                           const vector<double> &d_seidel) {
  bool jacobiDiverged = vectorHasOverflow(d_jacobi);
  bool seidelDiverged = vectorHasOverflow(d_seidel);

  cout << "\n========================================================" << endl;
  cout << "               QUADRO COMPARATIVO DE RESULTADOS" << endl;
  cout << "========================================================" << endl;

  if (jacobiDiverged || seidelDiverged) {
    cout << "[!] AVISO: ";
    if (jacobiDiverged && seidelDiverged) {
      cout << "Ambos os metodos NAO CONVERGIRAM!" << endl;
    } else if (jacobiDiverged) {
      cout << "Gauss-Jacobi NAO CONVERGIU!" << endl;
    } else {
      cout << "Gauss-Seidel NAO CONVERGIU!" << endl;
    }
    cout << "    Valores marcados com '*' sao invalidos." << endl;
  }

  cout << "| Desloc. | Gauss-Jacobi (cm) | Gauss-Seidel (cm) | Diff |" << endl;
  cout << "--------------------------------------------------------" << endl;

  size_t n = d_jacobi.size();
  for (size_t i = 0; i < n; i++) {
    string jacobiStr, seidelStr, diffStr;

    if (jacobiDiverged) {
      jacobiStr = "   *DIVERGIU*   ";
    } else {
      stringstream ss;
      ss << fixed << setprecision(5) << d_jacobi[i];
      jacobiStr = ss.str();
    }

    if (seidelDiverged) {
      seidelStr = "   *DIVERGIU*   ";
    } else {
      stringstream ss;
      ss << fixed << setprecision(5) << d_seidel[i];
      seidelStr = ss.str();
    }

    if (jacobiDiverged || seidelDiverged) {
      diffStr = " N/A";
    } else {
      double diff = abs(d_jacobi[i] - d_seidel[i]);
      stringstream ss;
      ss << fixed << setprecision(5) << diff;
      diffStr = ss.str();
    }

    cout << "| d" << i + 1 << "      | " << setw(17) << jacobiStr << " | "
         << setw(17) << seidelStr << " | " << setw(7) << diffStr << " |"
         << endl;
  }
  cout << "--------------------------------------------------------" << endl;
}