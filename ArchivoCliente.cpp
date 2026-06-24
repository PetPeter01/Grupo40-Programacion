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
    int tam = contarRegistros();
    for(int i=0; i<tam; i++){
        Cliente cliente = leerRegistro(i);
        if (strcmp(cliente.getDocumento(), documentoBuscado)==0){
            return i;
        }
    }
    return -1;
}

void ArchivoCliente::BuscarPorNombre(const char* nombreBuscado) {
    int tam = contarRegistros();
    for(int i=0; i<tam; i++){
        Cliente cliente = leerRegistro(i);
        if (cliente.getEstado() && strcmp(cliente.getNombre(), nombreBuscado)==0){
            cliente.mostrar();
        }
    }

}

void ArchivoCliente::BuscarPorApellido(const char* apellidoBuscado) {
    int tam = contarRegistros();
    for(int i=0; i<tam; i++){
        Cliente cliente = leerRegistro(i);
        if (cliente.getEstado() && strcmp(cliente.getApellido(), apellidoBuscado)==0){
            cliente.mostrar();
        }
    }

}

void ArchivoCliente::listarDocumentosDadosDeBaja() {
    int tam = contarRegistros();
    bool hay =  false;
    for(int i=0; i<tam; i++){
        Cliente cliente = leerRegistro(i);
        if(!cliente.getEstado()){
            cout<< "- " << cliente.getDocumento()<< "\n";
            hay = true;
        }
    }
    if(!hay){
        cout << "No hay clientes dados de baja.\n";
    }
}

bool ArchivoCliente::bajaLogica(int tipo) {
    Cliente cliente;
    int tam = contarRegistros();
    bool hay = false;
    for (int i=0; i<tam; i++){
        cliente = leerRegistro(i);
        if(cliente.getEstado()){
            hay = true;
            cout << "- " << cliente.getDocumento();
        }
    }

    if (!hay) {
        cout << "No hay clientes activos para borrar.\n";
        return false;
    }

    cout << "Ingrese el documento (DNI/CUIT) del cliente a borrar: ";
    cliente.cargarDocumento(tipo);

    int pos = BuscarPorDocumento(cliente.getDocumento());
    if (pos < 0) {
        cout << "No existe un cliente con ese documento.\n";
        return false;
    }

    cliente = leerRegistro(pos);
    if (!cliente.getEstado()) {
        cout << "El cliente ya esta dado de baja.\n";
        return false;
    }

    cliente.setEstado(false);
    if (modificarRegistro(cliente, pos) == 1) {
        cout << "Cliente dado de baja correctamente.\n";
        return true;
    }

    cout << "No se pudo dar de baja al cliente.\n";
    return false;
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

int ArchivoCliente::reactivarCliente(char* documento) {
    int pos = BuscarPorDocumento(documento);
    if (pos >= 0) {
        Cliente c = leerRegistro(pos);
        if (c.getEstado()) {
            return 0;
        }
        c.setEstado(true);
        if (modificarRegistro(c, pos) == 1) {
            return 1;
        } else {
            return -1;
        }
    }
    return -2;
}
