#include <iostream>
#include "persona.h"

using namespace std;

int main()
{
    persona p;
    cout<< "INGRESE TIPO DE DOCUMENTO: 1. DNI / 2. CUIL o CUIT: ";
    int tipo;
    cin>> tipo;
    p.cargar(tipo);
    p.mostrar();
    return 0;
}
