#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "transaccion.h"

class Venta: Transaccion{
    private:
        int _idCliente;
    public:
        int getIdCliente();

        void setIdCliente(int idCliente);

        void cargar(int idVenta, int idCliente, float importeTotal);
        void mostrar();
};

#endif // VENTA_H_INCLUDED
