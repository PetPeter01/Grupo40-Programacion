#ifndef PROVEEDOR_H_INCLUDED
#define PROVEEDOR_H_INCLUDED
#include "Persona.h"

class Proveedor: public Persona {
    private:
        int _idProveedor;
    public:
        int getIdProveedor();
        void setIdProveedor(int id);

        void cargar(int id);
        void mostrar();
};

#endif // PROVEEDOR_H_INCLUDED
