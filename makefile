# Variables
CXX = g++
CXXFLAGS = -std=c++14 -Wall
MAIN_FILE = main.cc
SRC_FILES = cadena.cc simbolo.cc production.cc grammar.cc
OBJ_FILES = $(SRC_FILES:.cc=.o)
EXECUTABLE_FILE = p07_GRAMMAR2CNF

# Regla por defecto
default: $(EXECUTABLE_FILE)

# Creación del ejecutable
$(EXECUTABLE_FILE): $(MAIN_FILE) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Creación de los archivos objeto
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa
run:
	./$(EXECUTABLE_FILE) $(FILE_IN) $(RUN_ARGS)

# Limpiar archivos generados
clean:
	rm -f $(EXECUTABLE_FILE) $(OBJ_FILES)
