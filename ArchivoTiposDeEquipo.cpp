#include "ArchivoTiposDeEquipo.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

bool ArchivoTiposDeEquipo::agregarRegistro(TiposDeEquipo reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) return false;
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return escribio == 1;
}

TiposDeEquipo ArchivoTiposDeEquipo::leerRegistro(int pos) {
    TiposDeEquipo reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

int ArchivoTiposDeEquipo::contarRegistros() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return 0;

    TiposDeEquipo reg;
    int cont = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) cont++;
    fclose(p);
    return cont;
}

int ArchivoTiposDeEquipo::buscarPorId(int idTipo) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;

    TiposDeEquipo reg;
    int pos = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getIdTiposDeEquipo() == idTipo) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoTiposDeEquipo::modificarRegistro(TiposDeEquipo reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return 0;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoTiposDeEquipo::listarTodos() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return false;

    TiposDeEquipo reg;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        reg.mostrar();
    }
    fclose(p);
    return true;
}

bool ArchivoTiposDeEquipo::listarActivos() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return false;

    TiposDeEquipo reg;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado()) reg.mostrar();
    }
    fclose(p);
    return true;
}

//  CREA 10 TIPOS YA CARGADOS


void ArchivoTiposDeEquipo::inicializar10PorDefecto() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p != nullptr) {
        fseek(p, 0, SEEK_END);
        long tam = ftell(p);
        fclose(p);
        if (tam > 0) return;
    }

    TiposDeEquipo t;

    t.setIdTiposDeEquipo(1);  t.setDescripcion("PC");               t.setEstado(true); agregarRegistro(t);
    t.setIdTiposDeEquipo(2);  t.setDescripcion("PORTATIL");         t.setEstado(true); agregarRegistro(t);
    t.setIdTiposDeEquipo(3);  t.setDescripcion("PERIFERICO");       t.setEstado(true); agregarRegistro(t);
    t.setIdTiposDeEquipo(4);  t.setDescripcion("COMPONENTE");       t.setEstado(true); agregarRegistro(t);
    t.setIdTiposDeEquipo(5);  t.setDescripcion("IMPRESORA");        t.setEstado(false); agregarRegistro(t);
    t.setIdTiposDeEquipo(6);  t.setDescripcion("MONITOR");          t.setEstado(false); agregarRegistro(t);
    t.setIdTiposDeEquipo(7);  t.setDescripcion("ALMACENAMIENTO");   t.setEstado(false); agregarRegistro(t);
    t.setIdTiposDeEquipo(8);  t.setDescripcion("REDES");            t.setEstado(false); agregarRegistro(t);
    t.setIdTiposDeEquipo(9);  t.setDescripcion("AUDIO");            t.setEstado(false); agregarRegistro(t);
    t.setIdTiposDeEquipo(10); t.setDescripcion("ACCESORIO");        t.setEstado(false); agregarRegistro(t);
}

bool ArchivoTiposDeEquipo::activarTipo() {
    inicializar10PorDefecto();

    cout << "TIPOS (ACTIVOS E INACTIVOS)\n";
    cout << "---------------------------\n";
    listarTodos();

    cout << "CODIGO A ACTIVAR: ";
    int id;
    cin >> id;
    cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "No existe ese codigo.\n";
        return false;
    }

    TiposDeEquipo t = leerRegistro(pos);
    t.setEstado(true);

    if (modificarRegistro(t, pos) == 1) {
        cout << "Activado.\n";
        return true;
    }
    cout << "No se pudo guardar.\n";
    return false;
}

bool ArchivoTiposDeEquipo::desactivarTipo() {
    inicializar10PorDefecto();

    cout << "TIPOS (ACTIVOS E INACTIVOS)\n";
    cout << "---------------------------\n";
    listarTodos();

    cout << "CODIGO A DESACTIVAR: ";
    int id;
    cin >> id;
    cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "No existe ese codigo.\n";
        return false;
    }

    TiposDeEquipo t = leerRegistro(pos);
    t.setEstado(false);

    if (modificarRegistro(t, pos) == 1) {
        cout << "Desactivado.\n";
        return true;
    }
    cout << "No se pudo guardar.\n";
    return false;
}
