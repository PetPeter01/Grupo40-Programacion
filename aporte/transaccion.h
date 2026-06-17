#ifndef TRANSACCION_H_INCLUDED
#define TRANSACCION_H_INCLUDED
#include <string>
#include "Fecha.h"

class Transaccion {
    private:
        int _idTransaccion;
        Fecha _fecha;
        float _importe;
        int _formaDePago;
        bool _estado;

    public:
        // Getters
        int getId();
        Fecha getFecha();
        float getImporte();
        int getFormaDePago();
        bool getEstado();
        std::string getFormaDePagoStr(int formaPago);

        // Setters
        bool setId(int idTransaccion);
        void setFecha(Fecha fecha);
        void setImporteTotal(float importeTotal);
        bool setFormaDePago(int formaPago);
        void setEstado(bool estado);

        // Métodos de Interfaz
        void cargar(int id, float importe);
        void mostrar();
};

#endif // TRANSACCION_H_INCLUDED
