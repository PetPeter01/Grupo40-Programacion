#include <iostream>
#include "persona.h"
#include "cliente.h"

using namespace std;

int main()
{
    /*persona p;
    cout<< "INGRESE TIPO DE DOCUMENTO: 1. DNI / 2. CUIL o CUIT: ";
    int tipo;
    cin>> tipo;
    p.cargar(tipo);
    p.mostrar();*/

    cliente c;
    int id = 1;
    c.cargar(id);
    c.mostrar();
    return 0;
}
