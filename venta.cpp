#include "venta.h"
#include "FuncionesGenerales.h"

int  Venta::getIdVenta(){
    return _idVenta;
}

int Venta::getIdCliente(){
    return _idCliente;
}

void Venta::setIdVenta(int idVenta){
    _idVenta = idVenta;
}

void Venta::setIdCliente(int idCliente){
    _idCliente = idCliente;
}


void Venta::cargar(int idVenta, int idCliente, float importe){
    Transaccion::cargar(idVenta, importe);
    setIdCliente(idCliente);
}
