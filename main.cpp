#include <iostream>
#include "Menu.h"
#include "rlutil.h"
using namespace std;

int main() {

    int opcion = 0;
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::hidecursor();

    do {
        opcion = mostrarMenuPrincipal();

        switch (opcion) {
            case 0:
                menuLogicoDatosBase();
                break;
            case 1:
                menuLogicoOperaciones();
                break;
            case 2:
                cout << endl << "Saliendo...\n";
                return 0;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }

    } while (opcion != 2);

    return 0;
}
