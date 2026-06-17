#include <iostream>
#include <cstdio>
#include <cstring>
#include "ArchivoCliente.h"
#include "FuncionesGenerales.h"
using namespace std;

Cliente ArchivoCliente::leerRegistro(int pos){
    Cliente obj;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        return obj;
    }

    fseek(pCliente, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return obj;
}
int ArchivoCliente::contarRegistros() {
    Cliente c;
    FILE* cliente = fopen(_nombreArchivo, "rb");
    if (cliente == nullptr) {
        return 0;
    }

    int contador = 0;
    while (fread(&c, tamanioRegistro, 1, cliente) == 1) {
        contador++;
    }

    fclose(cliente);
    return contador;
}

int ArchivoCliente::generarIdCliente() {
    return contarRegistros() + 1;
}

int ArchivoCliente::agregarRegistro(Cliente reg) {
    FILE* pCliente = fopen(_nombreArchivo, "ab");
    if (pCliente == nullptr) {
        cout << "ERROR DE ARCHIVO";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return escribio;
}

bool ArchivoCliente::listarRegistros() {

    int cant = contarRegistros();

    if (cant == 0) {
        std::cout << "No hay clientes registrados o el archivo no existe.\n";
        return false;
    }

    bool hayRegistrosActivos = false;

    for (int i = 0; i < cant; i++) {
        Cliente reg = leerRegistro(i);
        if (reg.getEstado() == true) {
            reg.mostrar();
            std::cout << "--------------------------------\n";
            hayRegistrosActivos = true;
        }
    }

    return hayRegistrosActivos;
}

int ArchivoCliente::altaCliente(int tipo) {
    Cliente reg;
    reg.cargarDocumento(tipo);
    int id = generarIdCliente();
    int pos = BuscarPorDocumento(reg.getDocumento());

    if (pos < 0) {
        reg.cargar(reg.getDocumento(), id, tipo);
        reg.setEstado(true);
        if (agregarRegistro(reg) == 1) {
            return 1;
        }
        return -1;
    }

    Cliente existente = leerRegistro(pos);
    if (!existente.getEstado()) {
        int opcion;
        while(true){
            opcion = PedirEnteroValido("Cliente existe, pero esta inactivo, reactivar? 1. Si / 2. No: ");
            if(opcion == 1 || opcion == 2){
                break;
            }
            cout << "Opcion invalida, seleccione 1 o 2\n";
            system("pause");
        }

        if(opcion == 1){
            existente.setEstado(true);
            modificarRegistro(existente, pos);
            return 2;
        }
        return 3;
    }

    return 4;
}

int ArchivoCliente::BuscarPorDocumento(char* documentoBuscado) {
    Cliente cliente;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&cliente, tamanioRegistro, 1, pCliente) == 1) {
        if (strcmp(cliente.getDocumento(), documentoBuscado)==0) {
            fclose(pCliente);
            return pos;
        }
        pos++;
    }

    fclose(pCliente);
    return -1;
}

int ArchivoCliente::BuscarPorId(int idBuscado) {
    int cantidad = contarRegistros();
    if (cantidad == 0) return -1;

    Cliente reg;

    for (int i = 0; i < cantidad; i++) {
        reg = leerRegistro(i);
        if (!reg.getEstado()){
           cout << "EMPLEADO DADO DE BAJA" << endl;
        }

        if (reg.getIdCliente() == idBuscado) {
            return i;
        }
    }

    return -1;
}

int ArchivoCliente::modificarRegistro(Cliente reg, int pos) {
    FILE* pCliente = fopen(_nombreArchivo, "rb+");

    if (pCliente == nullptr) {
        return -1;
    }

    fseek(pCliente, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    if (escribio != 1) {
        return -2;
    }

    return 1;
}

