#pragma once
#include <cstring>
#include "detalleVenta.h"
#include "Fecha.h"

class ArchivoDetalleVenta {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;
public:
    ArchivoDetalleVenta(const char* nombreArchivo = "detallesVentas.dat") {
        std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(DetalleVenta);
        }

    int contarRegistros();
    int contarRegistrosXVenta(int idVenta);
    DetalleVenta leerRegistro(int pos);
    float altaDetalle(int idVenta, Fecha fecha);
    int agregarRegistro(DetalleVenta reg);
    int listarPorVenta(int idVenta);
    float totalPorVenta(int idVenta);
    int getProximoId();

};
