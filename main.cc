
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "cadena.h"
#include "grammar.h"


#define kArgumentos 3
#define POS_INPUT_GRA_FILE 1
#define POS_OUTPUT_GRA_FILE 2

// Funcion que indica la forma correcta de ejecutar y cada parametro a
// introducir en caso de error.
void information(char *p_name) {
  std::cout << "La forma correcta de ejecutar el programa es:\n"
            << p_name  << " input.gra output.gra\n\n"  "input.gra\tArchivo que describe la gramática de entrada.\n"
               "output.gra\tArchivo donde se guardará la gramática en formato CNF.\n";
}

int main(int argc, char *argv[]) {

  // Comprobar número de argumentos de ejecución
  if (argc != kArgumentos) {
    std::cout << "¡Error en los argumentos!\n\n";
    information(argv[0]);
    return 1;
  }
  std::string grammarFileName = argv[POS_INPUT_GRA_FILE]; 
  std::string outputFileName = argv[POS_OUTPUT_GRA_FILE];

  Grammar grammarToCheck(grammarFileName);

  if (grammarToCheck.checkGrammar()) {
    Grammar auxGrammar;
    auxGrammar = grammarToCheck.getCNFGrammar();
    auxGrammar.writeFile(outputFileName);
  } else {
    std::cout << "Existen producciones unitarias o vacías en la gramatica de entrada.\n";
  }
  return 0;
}
