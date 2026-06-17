#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "transaccion.h"

class Venta: Transaccion{
    private:
        int _idVenta;
        int _idCliente;
    public:
        int getIdVenta();
        int getIdCliente();

        void setIdVenta(int idVenta);
        void setIdCliente(int idCliente);

        void cargar(int idVenta, int idCliente, float importe);
};

#endif // VENTA_H_INCLUDED
