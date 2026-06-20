#include <iostream>
#include "DetalleCompra.h"

using namespace std;

void DetalleCompra::cargar(int idDetalleCompra, int idCompra, int idProducto){

    setIdDetalleTransaccion(idDetalleCompra);
    setIdTransaccion(idCompra);

    DetalleTransaccion::cargar(idDetalleCompra, idCompra, idProducto);

}

void DetalleCompra::mostrar(){

    cout << "-----DETALLE COMPRA-----" << endl;
    DetalleTransaccion::mostrar();
    cout<< "--------------------" << endl;

}
