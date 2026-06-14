#include "FuncionesGenerales.h"
#include <limits>
#include <iostream>
using namespace std;

bool esTextoValido(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isalpha(texto[i]) && texto[i] != ' ') {
            return false;
        }
    }
    return true;
}

bool esEnteroValido(const char* entrada, int& numero) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return false;
        }
    }
    numero = atoi(entrada);
    return true;
}

