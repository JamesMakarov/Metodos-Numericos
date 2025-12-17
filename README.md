# Métodos Numéricos — Tema 2  
## Resolução de Sistemas Lineares e Cálculo da Inversa

Este projeto tem como objetivo implementar e comparar métodos numéricos para a **resolução de sistemas lineares** da forma:

\[
A x = b
\]

bem como o **cálculo da matriz inversa**, utilizando tanto um método **exato** quanto métodos **iterativos**, conforme solicitado no **Tema 2 da disciplina de Métodos Numéricos**.

---

## 🎯 Objetivos do Projeto

- Implementar métodos iterativos clássicos:
  - **Jacobi**
  - **Gauss-Seidel**
- Resolver sistemas lineares sem o uso de bibliotecas externas de álgebra linear
- Implementar o cálculo da **inversa exata** de uma matriz
- Implementar o cálculo da **inversa por métodos iterativos**
- Comparar resultados e validar a corretude numérica
- Trabalhar com organização modular e código estruturado

---

## 🧠 Fundamentação Teórica

### 1. Métodos Iterativos

Os métodos de **Jacobi** e **Gauss-Seidel** são métodos iterativos utilizados para resolver sistemas lineares quando a matriz dos coeficientes satisfaz determinadas condições (ex.: diagonal dominante).

Ambos os métodos são implementados **diretamente a partir das equações escalares**, sem o uso explícito de operações matriciais como soma ou subtração de matrizes.

---

### 2. Cálculo da Inversa

O projeto contempla três abordagens:

- **Inversa Exata**  
  Calculada por métodos diretos (ex.: eliminação de Gauss-Jordan).

- **Inversa por Jacobi**  
  Cada coluna da inversa é obtida resolvendo um sistema:
  \[
  A x = e_i
  \]
  onde \( e_i \) é o vetor da base canônica.

- **Inversa por Gauss-Seidel**  
  Abordagem análoga à do Jacobi, utilizando o método de Gauss-Seidel.

---
