#include "Proveedor.h"
#include "Persona.h"

void Proveedor::cargar(int id){
    setIdProveedor(id);
    Persona::cargar();
}

void Proveedor::mostrar(){
    std::cout << "ID PROVEEDOR: " << getIdProveedor() << std::endl;
    Persona::mostrar();
}

void Proveedor::setIdProveedor(int id){
    _idProveedor = id;
}

int Proveedor::getIdProveedor(){
    return _idProveedor;
}


