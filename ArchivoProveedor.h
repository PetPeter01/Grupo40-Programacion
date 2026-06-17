#pragma once
#include "Proveedor.h"
#include <cstring>

class ArchivoProveedor {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    ArchivoProveedor(const char* nombreArchivo = "proveedores.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(Proveedor);
    }

    int  altaProveedor();
    int getProximoId();

    int  agregarRegistro(Proveedor reg);
    bool listarRegistros();
    Proveedor leerRegistro(int pos);
    int contarRegistros();

    bool bajaLogica();
    int  modificarRegistro(Proveedor reg, int pos);
    int  buscarPorId(int idProveedor);
    int  buscarPorNombre(const char* nombreBuscado);
    int  reactivarProveedor(int idProveedor);
    void listarProveedores();
};
