CXX = g++
CXXFLAGS = -Isrc -Wall -std=c++11

ifeq ($(OS),Windows_NT)
    MKDIR = powershell -Command "if (-not (Test-Path 'bin')) { New-Item -ItemType Directory -Path 'bin' | Out-Null }"
    RM = del /Q /F
    RM_DIR = del /S /Q
    TARGET = bin/main.exe
    FIXPATH = $(subst /,\,$1)
    EXT = .exe
else
    MKDIR = mkdir -p bin
    RM = rm -f
    RM_DIR = rm -rf
    TARGET = bin/main
    FIXPATH = $1
    EXT = 
endif

SRCS = src/main.cpp \
       src/methods/jacobi.cpp \
       src/methods/seidel.cpp \
       src/inverse/inverse_jacobi.cpp \
       src/inverse/inverse_seidel.cpp \
       src/matrix/matrix.cpp \
       src/utils/output.cpp \
       src/utils/input.cpp


OBJS = $(SRCS:.cpp=.o)

all: directories $(TARGET)

directories:
	$(MKDIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(call FIXPATH,$(TARGET)) $(call FIXPATH,$(OBJS))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
ifeq ($(OS),Windows_NT)
	$(call FIXPATH,$(TARGET))
else
	./$(TARGET)
endif

clean:
	-$(RM) $(call FIXPATH,$(TARGET))
	-$(RM) $(call FIXPATH,src/*.o)
	-$(RM) $(call FIXPATH,src/methods/*.o)
	-$(RM) $(call FIXPATH,src/inverse/*.o)
	-$(RM) $(call FIXPATH,src/matrix/*.o)
	-$(RM) $(call FIXPATH,src/utils/*.o)