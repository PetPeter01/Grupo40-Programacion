#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "persona.h"

class Cliente: public Persona {
    private:
        int _idCliente;
        int _tipoCliente;
    public:
        int getIdCliente();
        int getTipoCliente();
        std::string getTipoClienteStr(int tipo);

        void setIdCliente(int id);
        bool setTipoCliente(int id);

        void cargar(char* documento, int id, int tipo);
        void mostrar();
};

#endif // CLIENTE_H_INCLUDED
