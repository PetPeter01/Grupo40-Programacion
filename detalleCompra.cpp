#include <iostream>
#include "DetalleCompra.h"
#include "FuncionesGenerales.h"

using namespace std;

void DetalleCompra::cargar(int idDetalleCompra, int idCompra, int idProducto){

    setIdDetalleTransaccion(idDetalleCompra);
    setIdTransaccion(idCompra);

    float precioUnitario;
    while (true) {
        precioUnitario = pedirFloatValido("PRECIO UNITARIO: ");
        if (setPrecioUnitario(precioUnitario)) break;
        cout << "Cantidad invalida (debe ser > 0).\n";
    }
    DetalleTransaccion::cargar(idDetalleCompra, idCompra, idProducto, precioUnitario);

}

void DetalleCompra::mostrar(){

    cout << "-----DETALLE COMPRA-----" << endl;
    DetalleTransaccion::mostrar();
    cout<< "--------------------" << endl;

}
