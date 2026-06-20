#pragma once
#include "detalleTransaccion.h"

class DetalleCompra : public DetalleTransaccion{

public:

    void cargar(int idDetalleCompra, int idCompra, int idProducto);
    void mostrar();
};
