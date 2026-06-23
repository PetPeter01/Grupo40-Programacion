#include <iostream>
#include "compra.h"

using namespace std;

void Compra::cargar(int idCompra, int idProveedor, float importe){
    setIdProveedor(idProveedor);
    Transaccion::cargar(idCompra, importe);

}

void Compra::mostrar(char* nombreProv, char* apellidoProv){

    cout << "---------------" << endl;
    cout << "ID Compra: " << getId() << endl;
    cout << "ID Proveedor: " << getIdProveedor() << endl;
    cout << "Proveedor: " << nombreProv << " " << apellidoProv << endl;
    Transaccion::mostrar();
    cout << "---------------" << endl;

}

void Compra::setIdProveedor(int idProveedor){
    if(idProveedor>0){
            _idProveedor = idProveedor;
    }
}

int Compra::getIdProveedor(){
    return _idProveedor;
}
