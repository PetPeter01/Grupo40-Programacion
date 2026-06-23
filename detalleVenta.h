#pragma once
#include "detalleTransaccion.h"

class DetalleVenta : public DetalleTransaccion{

public:

    void cargar(int idDetalleVenta, int idVenta, int idProducto, float precioUnitario);
    void mostrar();
};
