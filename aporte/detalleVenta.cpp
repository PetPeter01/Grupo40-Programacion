#include <iostream>
#include "detalleVenta.h"

using namespace std;

void DetalleVenta::cargar(int idDetalleVenta, int idVenta, int idProducto){

    setIdDetalleTransaccion(idDetalleVenta);
    setIdTransaccion(idVenta);

    DetalleTransaccion::cargar(idDetalleVenta, idVenta, idProducto);

}

void DetalleVenta::mostrar(){

    cout << "-----DETALLE VENTA-----" << endl;
    DetalleTransaccion::mostrar();
    cout<< "--------------------" << endl;

}
