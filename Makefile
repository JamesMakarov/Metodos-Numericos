# 1. Configurações do Compilador
CXX = g++

CXXFLAGS = -Wall -Iinclude -Isrc

# 2. Arquivo Final
TARGET = bin/main.exe

# 3. Encontrando os Arquivos Automaticamente 
SRCS = $(wildcard src/*.cpp) \
       $(wildcard src/inverse/*.cpp) \
       $(wildcard src/matrix/*.cpp) \
       $(wildcard src/methods/*.cpp) \
       $(wildcard src/system/*.cpp) \
       $(wildcard src/utils/*.cpp)

# 4. Transformando a lista de .cpp em lista de .o
OBJS = $(SRCS:.cpp=.o)

# 5. Regra Principal (O que roda quando digita 'make')
all: folder $(TARGET)

# Cria a pasta bin se ela não existir (para evitar erro no Windows)
folder:
	if not exist bin mkdir bin

# 6. Linkagem (Junta todos os .o para criar o .exe na pasta bin)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 7. Regra Genérica de Compilação
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 8. Rodar o main que está em bin
run:
	.\bin\main.exe

# 9. Limpeza (Windows)
clean:
	del /Q bin\main.exe
	del /S /Q src\*.o