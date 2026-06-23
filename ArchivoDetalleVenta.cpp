#include "ArchivoDetalleVenta.h"
#include "detalleVenta.h"
#include "ArchivoProducto.h"
#include "Producto.h"
#include "ArchivoStock.h"
#include "FuncionesGenerales.h"

using namespace std;

float ArchivoDetalleVenta::altaDetalle(int idVenta, Fecha fechaVenta){

    ArchivoProducto archProd;
    ArchivoStock archStock;

    DetalleVenta detVen;

    float total = 0.0f;
    int continuar = 1;

    while(continuar == 1){

        int idProducto = PedirEnteroValido("ID PRODUCTO: ");
        int pProd = archProd.buscarPorId(idProducto);

        if(pProd < 0){
            cout << "Producto no encontrado.\n";
            system("pause");
            continue;
        }

        Producto prod = archProd.leerRegistro(pProd);

        if(!prod.getEstado()){
            cout << "Producto inactivo.\n";
            system("pause");
            continue;
        }

        int idDetalle = getProximoId();

        detVen.cargar(idDetalle, idVenta, idProducto);

        if(!archStock.hayStockSuficiente(idProducto, detVen.getCantidad())){
            cout << "Stock insuficiente.\n";
            system("pause");
            continue;
        }

        int guardo = agregarRegistro(detVen);

        if(guardo == 1){

            cout << "Detalle de venta guardado con exito.\n";

            total += detVen.getSubtotal();

            archStock.restarStock(idProducto, detVen.getCantidad(), fechaVenta);
        }else{
            cout << "Error al guardar el detalle de venta.\n";
        }

        cout << "¿Agregar otro producto a la venta? 1. Si / 2. No: ";
        cin >> continuar;
        cin.ignore();
    }

    return total;
}

DetalleVenta ArchivoDetalleVenta::leerRegistro(int pos){

    DetalleVenta obj;
    FILE* p = fopen(_nombreArchivo, "rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

int ArchivoDetalleVenta::contarRegistros() {

    FILE* p = fopen(_nombreArchivo, "rb");
    DetalleVenta aux;

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

int ArchivoDetalleVenta::contarRegistrosXVenta(int idVenta){

    int cantidad = 0;
    int tam = contarRegistros();

    for(int i = 0; i < tam; i++){

        DetalleVenta detVen = leerRegistro(i);

        if(detVen.getIdTransaccion() == idVenta){
            cantidad++;
        }
    }

    return cantidad;
}

int ArchivoDetalleVenta::getProximoId(){
    return contarRegistros() + 1;
}

int ArchivoDetalleVenta::agregarRegistro(DetalleVenta reg){

    FILE* p = fopen(_nombreArchivo, "ab");

    if(p == nullptr){
        cout << "ERROR DE ARCHIVO\n";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);

    fclose(p);
    return escribio;
}

int ArchivoDetalleVenta::listarPorVenta(int idVenta) {

    int tam = contarRegistros();
    bool encontro = false;

    ArchivoProducto archProd;

    for(int i = 0; i < tam; i++){

        DetalleVenta d = leerRegistro(i);

        if(d.getEstado() && d.getIdTransaccion() == idVenta){

            encontro = true;

            int pos = archProd.buscarPorId(d.getIdProducto());

            if(pos >= 0){

                Producto prod = archProd.leerRegistro(pos);

                cout << prod.getIdProducto() << " - " << prod.getDescripcion() << endl;
            }else{

                cout << "Producto ID: " << d.getIdProducto() << " (No encontrado)" << endl;
            }

            cout << "  | Cantidad: " << d.getCantidad() << endl;

            cout << "  | Precio Unitario: " << d.getPrecioUnitario() << endl;

            cout << "  | Subtotal: " << d.getSubtotal() << endl;

            cout << "---------------------------------------" << endl;
        }
    }

    if(!encontro){
        cout << "No hay registros para la venta " << idVenta << endl;
        return 0;
    }

    return 1;
}

float ArchivoDetalleVenta::totalPorVenta(int idVenta){

    float total = 0.0f;

    int tam = contarRegistros();

    for(int i=0; i<tam; i++){

        DetalleVenta detVen = leerRegistro(i);

        if(detVen.getIdTransaccion() == idVenta){

            total += detVen.getSubtotal();
        }
    }

    return total;
}
