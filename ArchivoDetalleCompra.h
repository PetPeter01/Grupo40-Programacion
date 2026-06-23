#pragma once
#include <cstring>
#include "detalleCompra.h"
#include "Fecha.h"

class ArchivoDetalleCompra {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    ArchivoDetalleCompra(const char* nombreArchivo = "detallesCompras.dat") {
        std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(DetalleCompra);
    }

    float altaDetalle(int idCompra, Fecha fecha);
    DetalleCompra leerRegistro(int pos);
    int contarRegistros();
    int contarRegistroXCompra(int idCompra);
    int getProximoId();
    int   agregarRegistro(DetalleCompra reg);
    int   listarPorCompra(int idCompra);
    float totalPorCompra(int idCompra);
    int puedeAnularCompra(int idCompra);
    int revertirCompra(int idCompra, Fecha fecha);


};
