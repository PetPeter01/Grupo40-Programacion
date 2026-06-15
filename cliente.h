#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

class cliente: persona {
    private:
        int _idCliente;
        int _tipoCliente;
    public:
        int getIdCliente();
        int getTipoCliente();
        std::string getTipoClienteStr(int tipo);

        void setIdCliente(int id);
        bool setTipoCliente(int id);

        void cargar(int id);
        void mostrar();
};

#endif // CLIENTE_H_INCLUDED
