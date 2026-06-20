#include <iostream>
#include "venta.h"
#include "FuncionesGenerales.h"

using namespace std;

void Venta::cargar(int idVenta, int idCliente, float importeTotal){

    setId(idVenta);
    setIdCliente(idCliente);
    Transaccion::cargar(idVenta, importeTotal);
}

void Venta::mostrar(){

    cout << "---------------" << endl;
    cout << "ID Venta: " << getId() << endl;
    cout << "ID Cliente: " << getIdCliente() << endl;
    Transaccion::mostrar();
    cout << "---------------" << endl;

}

void Venta::setIdCliente(int idCliente){
    if(idCliente>0){
            _idCliente = idCliente;
    }
}

int Venta::getIdCliente(){
    return _idCliente;
}
