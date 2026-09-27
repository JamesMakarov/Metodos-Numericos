#include <cassert>
#include <cmath>
#include <vector>

#include "../src/methods/jacobi.h"
#include "../src/methods/seidel.h"

namespace {
bool approx(double a, double b, double eps = 1e-6) {
    return std::abs(a - b) < eps;
}

void assertSolution(const std::vector<double>& x) {
    assert(x.size() == 2);
    assert(approx(x[0], 1.0));
    assert(approx(x[1], 2.0));
}
}

int main() {
    const std::vector<std::vector<double>> A = {
        {4.0, 1.0},
        {2.0, 3.0},
    };
    const std::vector<double> b = {6.0, 8.0};

    assertSolution(solveJacobi(A, b, 1e-10, 1000));
    assertSolution(solveSeidel(A, b, 1e-10, 1000));

    return 0;
}
