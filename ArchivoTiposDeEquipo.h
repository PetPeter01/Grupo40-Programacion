#pragma once
#include <cstring>
#include "TiposDeEquipo.h"

class ArchivoTiposDeEquipo {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    ArchivoTiposDeEquipo(const char* nombreArchivo = "tiposDeEquipo.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(TiposDeEquipo);
    }

    void inicializarSiNoExiste();
    void inicializar10PorDefecto();

    bool agregarRegistro(TiposDeEquipo reg);
    TiposDeEquipo leerRegistro(int pos);
    int contarRegistros();
    int buscarPorId(int idTipo);
    int modificarRegistro(TiposDeEquipo reg, int pos);

    bool listarTodos();
    bool listarActivos();

    bool activarTipo();
    bool desactivarTipo();
};
