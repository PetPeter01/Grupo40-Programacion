#include <iostream>
#include "compra.h"

using namespace std;

void compra::cargar(int idCompra, int idProveedor, float importe){

    setId(idCompra);
    setIdProveedor(idProveedor);
    Transaccion::cargar(idCompra, importe);

}

void compra::mostrar(){

    cout << "---------------" << endl;
    cout << "ID Compra: " << getId() << endl;
    cout << "ID Proveedor: " << getIdProveedor() << endl;
    Transaccion::mostrar();
    cout << "---------------" << endl;

}

void compra::setIdProveedor(int idProveedor){
    if(idProveedor>0){
            _idProveedor = idProveedor;
    }
}

int compra::getIdProveedor(){
    return _idProveedor;
}
