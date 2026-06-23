#include "ArchivoVenta.h"
#include "ArchivoCliente.h"
#include "ArchivoDetalleVenta.h"
#include "FuncionesGenerales.h"

using namespace std;

int ArchivoVenta::altaVenta(){

    ArchivoCliente archCli;
    ArchivoDetalleVenta archDetVen;

    cout << "VENTA\n";
    cout << "-------------------------\n";

    int idCliente = PedirEnteroValido("ID CLIENTE: ");
    int pCliente = archCli.BuscarPorId(idCliente);

    if(pCliente < 0){
        return -1;
    }

    Cliente cli = archCli.leerRegistro(pCliente);

    if(!cli.getEstado()){
        return -2;
    }

    int idVenta = getProximoId();

    Venta vnt;

    vnt.cargar(idVenta, idCliente, 0.0f);

    if(agregarRegistro(vnt) != 1){
        return -3;
    }

    int pVenta = contarRegistros() - 1;

    float total = archDetVen.altaDetalle(
        idVenta,
        vnt.getFecha()
    );

    if(total <= 0){
        return -4;
    }

    vnt.setImporteTotal(total);

    modificarRegistro(vnt, pVenta);

    return 1;
}

int ArchivoVenta::agregarRegistro(Venta reg){

    FILE* p = fopen(_nombreArchivo, "ab");

    if(p == nullptr){
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);

    fclose(p);
    return escribio;
}

Venta ArchivoVenta::leerRegistro(int pos){

    Venta obj;
    FILE* p = fopen(_nombreArchivo, "rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

int ArchivoVenta::contarRegistros() {

    FILE* p = fopen(_nombreArchivo, "rb");
    Venta aux;

    if(p == nullptr){
        return 0;
    }

    int cont = 0;

    while(fread(&aux, tamanioRegistro, 1, p) == 1){
            cont++;
    }

    fclose(p);
    return cont;
}

int ArchivoVenta::getProximoId(){
    return contarRegistros() + 1;
}

int ArchivoVenta::generarIdVenta(){
    return getProximoId();
}

int ArchivoVenta::modificarRegistro(Venta reg, int pos){

    FILE* p = fopen(_nombreArchivo, "rb+");

    if(p == nullptr){
        return -1;
    }

    fseek(p, pos* tamanioRegistro, SEEK_SET);

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);

    fclose(p);

    if(escribio != 1){
        return -2;
    }

    return 1;
}

bool ArchivoVenta::listarRegistros(){

    ArchivoCliente archCli;
    ArchivoDetalleVenta archDetVen;

    int cant = contarRegistros();

    if(cant == 0){
        cout << "No hay ventas registradas.\n";
        return false;
    }

    for(int i = 0; i < cant; i++){

        Venta vnt = leerRegistro(i);

        if (vnt.getEstado()) {

            int pCliente = archCli.BuscarPorId(vnt.getIdCliente());
            Cliente cli = archCli.leerRegistro(pCliente);

            cout << "Cliente: " << cli.getNombre() << " " << cli.getApellido() << endl;

            vnt.mostrar();

            cout << "Detalles:\n";

            int cantDetalles = archDetVen.listarPorVenta(vnt.getId());

            if(cantDetalles == 0){
                cout << "   (Sin items)\n";
            }

            cout << "--------------------------\n\n";
        }
    }

    return true;
}

int ArchivoVenta::buscarPorId(int idVenta){

    int tam = contarRegistros();

    for(int i = 0; i < tam; i++){

        Venta reg = leerRegistro(i);

        if(reg.getId() == idVenta){
            return i;
        }
    }

    return -1;
}

int ArchivoVenta::bajaLogica(int idVenta){

    int pos = buscarPorId(idVenta);

    if(pos < 0){
        return -1;
    }

    Venta vnt = leerRegistro(pos);

    if(!vnt.getEstado()){
        return -2;
    }

    vnt.setEstado(false);

    return modificarRegistro(vnt, pos);
}

int ArchivoVenta::reactivarVenta(int idVenta){

    int pos = buscarPorId(idVenta);

    if(pos < 0){
        return -1;
    }

    Venta vnt = leerRegistro(pos);

    if(vnt.getEstado()){
        return -2;
    }

    vnt.setEstado(true);
    return modificarRegistro(vnt, pos);
}

float ArchivoVenta::recaudacionPorCliente(char* documento) {
    ArchivoCliente c;
    int pos = c.BuscarPorDocumento(documento);
    Cliente cliente = c.leerRegistro(pos);

    Venta venta;
    float total = 0;
    int tam = contarRegistros();
    for(int i=0; i < tam; i++){
        if (venta.getEstado() && strcmp(documento, cliente.getDocumento())==1) {
            total += venta.getImporte();
        }
    }

    return total;
}

float ArchivoVenta::recaudacionAnual(int anio){
    Venta venta;
    float total = 0;
    int tam = contarRegistros();
    for(int i=0; i < tam; i++){
        if (venta.getFecha().getAnio()==anio) {
            total += venta.getImporte();
        }
    }
    return total;
}


