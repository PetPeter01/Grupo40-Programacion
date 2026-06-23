#include "ArchivoMovimientoStock.h"
#include <iostream>

int ArchivoMovimientoStock::agregarRegistro(MovimientoStock reg){
    reg.setIdMovimiento(getProximoId());

    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}


int ArchivoMovimientoStock::getProximoId() {
    return contarRegistros() + 1;
}

int ArchivoMovimientoStock::contarRegistros() {
    MovimientoStock m;
    FILE* pMov = fopen(_nombreArchivo, "rb");
    if (pMov == nullptr) {
        return 0;
    }

    int contador = 0;
    while (fread(&m, tamanioRegistro, 1, pMov) == 1) {
        contador++;
    }

    fclose(pMov);
    return contador;
}

bool ArchivoMovimientoStock::listarRegistros() {
    int cant = contarRegistros();

    if (cant == 0) {
        std::cout << "No hay stock registrados o el archivo no existe.\n";
        return false;
    }

    bool hayRegistrosActivos = false;

    for (int i = 0; i < cant; i++) {
        MovimientoStock reg = leerRegistro(i);

        if (reg.getEstado() == true) {
            reg.mostrar();
            std::cout << "--------------------------------\n";
            hayRegistrosActivos = true;
        }
    }

    return hayRegistrosActivos;
}

MovimientoStock ArchivoMovimientoStock::leerRegistro(int pos) {
    MovimientoStock obj;
    FILE* pProd = fopen(_nombreArchivo, "rb");

    if (pProd == nullptr) {
        return obj;
    }

    fseek(pProd, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pProd);
    fclose(pProd);

    return obj;
}

bool ArchivoMovimientoStock::bajaLogica() {
    std::cout << "INGRESE ID DEL MOVIMIENTO: ";
    int id;
    std::cin >> id;
    std::cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        std::cout << "Movimiento de Stock no encontrado.\n";
        return false;
    }

    MovimientoStock reg = leerRegistro(pos);
    if (!reg.getEstado()) {
        std::cout << "El Movimiento de Stock ya esta dado de baja.\n";
        return false;
    }

    reg.setEstado(false);
    int ok = modificarRegistro(reg, pos);
    if (ok == 1) {
        std::cout << "Movimiento de Stock dado de baja correctamente.\n";
        return true;
    }
    std::cout << "No se pudo modificar el registro.\n";
    return false;
}

int ArchivoMovimientoStock::modificarRegistro(MovimientoStock reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return -1;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    if (escribio != 1) return -2;
    return 1;
}

int ArchivoMovimientoStock::buscarPorId(int idBuscado) {
    int tam = contarRegistros();
    int i;
    MovimientoStock mov;
    for(i=1; i < tam; i++){
        mov = leerRegistro(i);
        if(mov.getIdMovimiento()==idBuscado){
            return i;
        }
    }
    return -1;
}
