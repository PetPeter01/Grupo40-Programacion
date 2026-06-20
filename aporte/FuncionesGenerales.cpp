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

int PedirEnteroValido(string texto) {
    char entrada[20];
    int numero;

    while (true) {
        cout << texto;
        cin >> entrada;

        if (esEnteroValido(entrada, numero)) {
            cin.ignore();
            break;
        }

        cout << "Numero invalido." << endl;
        system("pause");
        cin.ignore();
    }

    return numero;
}

float PedirFloatValido(string texto){
    float numero;

    while(true){
        cout << texto;

        if(cin >> numero){
            cin.ignore(1000, '\n');
            return numero;
        }

        cout << "Numero invalido." << endl;

        cin.clear();
        cin.ignore(1000, '\n');
    }
}
