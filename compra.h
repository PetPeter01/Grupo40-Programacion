#pragma once
#include "transaccion.h"

class Compra : public Transaccion{
private:
    int _idProveedor;
public:
    int getIdProveedor();

    void setIdProveedor(int idProveedor);

    void cargar(int idCompra, int idProveedor, float importe);
    void mostrar(char* nombreProv, char* apellidoProv);
};
