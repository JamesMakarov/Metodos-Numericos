# Numerical Methods — Linear Systems in C++

C++ application for solving a linear-system problem using **Gauss-Jacobi** and **Gauss-Seidel** iterative methods and comparing the resulting displacement vectors.

The program is presented in the context of seismic-wave analysis: a system (A d = b) is solved to estimate displacements and evaluate the resulting values.

## Implemented methods

- Gauss-Jacobi;
- Gauss-Seidel;
- iterative computation of matrix inverses;
- matrix-vector multiplication;
- configurable convergence tolerance;
- comparison between both iterative approaches;
- input of custom systems;
- predefined example data.

## Structure

```text
.
├── src/
│   ├── inverse/
│   ├── matrix/
│   ├── methods/
│   ├── utils/
│   └── main.cpp
├── include/
├── docs/
└── Makefile
```

### `src/methods/`

Contains the iterative solvers for Jacobi and Gauss-Seidel.

### `src/inverse/`

Builds an inverse matrix by solving systems whose right-hand sides are the canonical basis vectors.

### `src/matrix/`

Contains the matrix operations used by the numerical routines.

### `src/utils/`

Input and output helpers, including formatted results and comparison output.

## Building

### Requirements

- GCC/G++ with C++11 support;
- Make.

Compile:

```bash
make
```

Run:

```bash
make run
```

Remove generated files:

```bash
make clean
```

The Makefile supports both Windows and Unix-like systems.

## Program modes

The command-line menu allows:

1. Gauss-Jacobi with predefined data;
2. Gauss-Seidel with predefined data;
3. Gauss-Jacobi with custom data;
4. Gauss-Seidel with custom data;
5. comparison of both methods;
6. exit.

For custom input, the user provides the matrix, right-hand-side vector and convergence tolerance.

## Numerical context

For a system

```text
A d = b
```

the project computes an approximate inverse using the selected iterative method and then evaluates

```text
d = A⁻¹ b
```

The comparison mode runs both methods on the same input so their resulting displacement vectors can be inspected side by side.

## Documentation

Additional course material is available in `docs/`.
