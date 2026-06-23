#include "ArchivoDetalleCompra.h"
#include "detalleCompra.h"
#include "ArchivoProducto.h"
#include "Producto.h"
#include "ArchivoStock.h"
#include "MovimientoStock.h"
#include "ArchivoMovimientoStock.h"
#include "FuncionesGenerales.h"

using namespace std;

float ArchivoDetalleCompra::altaDetalle(int idCompra, Fecha fechaCompra) {
    ArchivoProducto archProducto;
    ArchivoStock stockArch;
    DetalleCompra   det;
    float total = 0.0f;
    int   continuar = 1;


    while (continuar == 1) {
        int idProducto = PedirEnteroValido("ID PRODUCTO: ");
        int posProd = archProducto.buscarPorId(idProducto);

        if (posProd < 0) {
            cout << "Producto no encontrado.\n";
            system("pause");
            continue;
        }

        Producto prod = archProducto.leerRegistro(posProd);
        if (!prod.getEstado()) {
            cout << "Producto inactivo.\n";
            system("pause");
            continue;
        }

        int idDetalle = getProximoId();

        det.cargar(idDetalle, idCompra, idProducto);

        int guardo = agregarRegistro(det);
        if (guardo == 1) {
            cout << "Detalle de compra guardado con exito.\n";
            total += det.getSubtotal();
            stockArch.sumarStock(idProducto, det.getCantidad(), fechaCompra);
        } else {
            cout << "Error al guardar el detalle de compra.\n";
        }

        cout << "¿Agregar otro producto a la compra? 1. Si / 2. No: ";
        cin >> continuar;
        cin.ignore();
    }

    return total;
}

DetalleCompra ArchivoDetalleCompra::leerRegistro(int pos){
    DetalleCompra obj;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, p);
    fclose(p);

    return obj;
}

int ArchivoDetalleCompra::contarRegistros() {
    FILE*  p   = fopen(_nombreArchivo, "rb");
    DetalleCompra aux;
    if (p == nullptr) return 0;

    int cont = 0;
    while (fread(&aux, tamanioRegistro, 1, p) == 1) {
        cont++;
    }
    fclose(p);
    return cont;
}

int ArchivoDetalleCompra::getProximoId() {
    return contarRegistros() + 1;
}

int ArchivoDetalleCompra::agregarRegistro(DetalleCompra reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        std::cout << "ERROR DE ARCHIVO\n";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}

int ArchivoDetalleCompra::listarPorCompra(int idCompra) {
    int tam = contarRegistros();
    bool encontroAlMenosUno = false;

    ArchivoProducto archProducto;

    for (int i = 0; i < tam; i++) {
        DetalleCompra d = leerRegistro(i);
        if (d.getEstado() && d.getIdTransaccion() == idCompra) {
            encontroAlMenosUno = true;
            int pos = archProducto.buscarPorId(d.getIdProducto());

            if (pos != -1) {
                Producto prod = archProducto.leerRegistro(pos);
                std::cout << prod.getIdProducto() << " - " << prod.getDescripcion() << std::endl;
            } else {
                std::cout << "Producto ID: " << d.getIdProducto() << " (No encontrado)" << std::endl;
            }

            // Mostramos los datos del detalle
            std::cout << "  | Cant: "      << d.getCantidad() << std::endl;
            std::cout << "  | P.U.: "      << d.getPrecioUnitario() << std::endl;
            std::cout << "  | Subtotal: "  << d.getSubtotal() << std::endl;
            std::cout << "---------------------------------------" << std::endl;
        }
    }

    if (!encontroAlMenosUno) {
        std::cout << "No hay registros para la compra " << idCompra << std::endl;
        return 0;
    }

    return 1;
}

float ArchivoDetalleCompra::totalPorCompra(int idCompra) {
    DetalleCompra d;
    int tam = contarRegistros();
    float total = 0.0f;

    for(int i = 0; i <= tam; i++) {
        if (d.getIdTransaccion() == idCompra) {
            total += d.getCantidad() * d.getPrecioUnitario();
        }
    }
    return total;
}

int ArchivoDetalleCompra::puedeAnularCompra(int idCompra) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) return -1;

    DetalleCompra det;
    ArchivoStock stockArch;

    while (fread(&det, sizeof(DetalleCompra), 1, p) == 1) {
        if (det.getIdTransaccion() == idCompra) {
            int stockActual = stockArch.getStock(det.getIdProducto());
            if (stockActual < det.getCantidad()) {
                fclose(p);
                return 0;
            }
        }
    }

    fclose(p);
    return 1;
}

int ArchivoDetalleCompra::revertirCompra(int idCompra, Fecha fecha) {
    int cant = contarRegistros();
    if (cant == 0) return 0;

    int* ids = new int[cant];
    int* cants = new int[cant];

    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) {
        delete[] ids;
        delete[] cants;
        return -1;
    }

    DetalleCompra det;
    int i = 0;

    while (fread(&det, sizeof(DetalleCompra), 1, p) == 1) {
        if (det.getIdTransaccion() == idCompra) {
            ids[i] = det.getIdProducto();
            cants[i] = det.getCantidad();
            i++;
        }
    }
    fclose(p);

    ArchivoStock stockArch;
    for (int j = 0; j < cant; j++) {
        if (!stockArch.hayStockSuficiente(ids[j], cants[j])) {
            delete[] ids;
            delete[] cants;
            return -2;
        }
    }

    ArchivoMovimientoStock movArch;
    for (int j = 0; j < cant; j++) {
        stockArch.restarStock(ids[j], cants[j], fecha);

        MovimientoStock mov;
        mov.cargar(ids[j], cants[j], "EGRESO", fecha);
        movArch.agregarRegistro(mov);
    }

    delete[] ids;
    delete[] cants;
    return 1;
}
