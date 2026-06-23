#pragma once
#include <cstring>
#include "venta.h"

class ArchivoVenta {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    ArchivoVenta(const char* nombreArchivo = "ventas.dat"){
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(Venta);
    }

    int altaVenta();

    int getProximoId();
    int generarIdVenta();

    int agregarRegistro(Venta reg);
    Venta leerRegistro(int pos);
    int modificarRegistro(Venta reg, int pos);

    int contarRegistros();
    bool listarRegistros();

    int buscarPorId(int idVenta);

    int bajaLogica(int idVenta);
    int reactivarVenta(int idVenta);

    float recaudacionAnual(int anio);
    float recaudacionPorCliente(char* documento);

};
