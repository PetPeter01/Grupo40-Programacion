#include "venta.h"
#include "FuncionesGenerales.h"

int Venta::getIdCliente(){
    return _idCliente;
}

void Venta::setIdCliente(int idCliente){
    _idCliente = idCliente;
}


void Venta::cargar(int idVenta, int idCliente, float importe){
    Transaccion::cargar(idVenta, importe);
    setIdCliente(idCliente);
}
