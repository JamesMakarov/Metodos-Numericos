a estrutura de pastas inicial é essa:
ondas\_sismicas/

│

├── bin/

│   └── ondas\_sismicas           # Executável final

│

├── src/

│   ├── main.cpp                 # Função principal

│   │

│   ├── matrix/

│   │   ├── matrix.h             # Estrutura da matriz e protótipos

│   │   └── matrix.cpp           # Operações com matriz (alocação, impressão, etc.)

│   │

│   ├── inverse/

│   │   ├── inverse.h            # Protótipos do cálculo da inversa

│   │   └── inverse.cpp          # Cálculo da matriz inversa coluna a coluna

│   │

│   ├── methods/

│   │   ├── jacobi.h             # Método de Gauss-Jacobi

│   │   ├── jacobi.cpp

│   │   ├── seidel.h             # Método de Gauss-Seidel

│   │   └── seidel.cpp

│   │

│   ├── system/

│   │   ├── system\_solver.h      # Resolver d = A⁻¹ b

│   │   └── system\_solver.cpp

│   │

│   └── utils/

│       ├── input.h              # Leitura de A e b

│       ├── input.cpp

│       ├── output.h             # Impressão de resultados e alertas

│       └── output.cpp

│

├── data/

│   ├── caso\_padrao.txt          # Matriz A e vetor b fornecidos pelo professor

│   ├── caso\_1.txt               # Variações de A e b

│   ├── caso\_2.txt

│   └── caso\_3.txt

│

├── include/

│   └── config.h                 # Constantes (tolerância, limite 0.4 cm, iterações)

│

├── docs/

│   ├── apresentacao.pdf         # Slides

│   └── relatorio.pdf            # (Opcional) documentação escrita

│

├── Makefile                     # Compilação do projeto

│

└── README.md                    # Instruções de execução



