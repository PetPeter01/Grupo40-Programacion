#pragma once
#include <cstring>
#include "Cliente.h"

class ArchivoCliente {
private:
    char _nombreArchivo[30];
    const int tamanioRegistro;

public:
    ArchivoCliente(const char* nombreArchivo = "cliente.dat")
        : tamanioRegistro(sizeof(Cliente)) {
        strcpy(_nombreArchivo, nombreArchivo);
    }

    int contarRegistros();
    bool listarRegistros();
    Cliente leerRegistro(int pos);
    int agregarRegistro(Cliente cliente);

    int altaCliente(int tipo);
    int reactivarCliente(char* documento);

    bool bajaLogica();
    void listarDocumentosDadosDeBaja();

    int generarIdCliente();
    int modificarRegistro(Cliente reg, int pos);
    int BuscarPorDocumento(char* documentoBuscado);
    void BuscarPorNombre(const char* nombreBuscado);
    void BuscarPorApellido(const char* apellidoBuscado);
    int BuscarPorId(int idBuscado);
};
