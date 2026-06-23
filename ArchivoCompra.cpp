#include "ArchivoCompra.h"
#include "compra.h"
#include "ArchivoProveedor.h"
#include "ArchivoDetalleCompra.h"
#include "FuncionesGenerales.h"

int ArchivoCompra::altaCompra() {
    ArchivoProveedor archProv;
    ArchivoDetalleCompra archDet;

    cout << "COMPRA\n";
    cout << "-------------------------\n";
    int idProveedor = PedirEnteroValido("ID PROVEEDOR: ");
    int posProv = archProv.buscarPorId(idProveedor);
    if (posProv < 0) return -1;
    Proveedor p = archProv.leerRegistro(posProv);
    if (!p.getEstado()) return -2;

    int idCompra = getProximoId();

    Compra c;
    c.cargar(idCompra, idProveedor, 0.0f);

    if (!agregarRegistro(c)) return -6;

    int posCompra = contarRegistros() - 1;

    float total = archDet.altaDetalle(idCompra, c.getFecha());
    if (total <= 0) return -7;

    c.setImporteTotal(total);
    modificarRegistro(c, posCompra);

    return 1;
}

bool ArchivoCompra::agregarRegistro(Compra reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        cout << "ERROR DE ARCHIVO\n";
        return false;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return (escribio == 1);
}

Compra ArchivoCompra::leerRegistro(int pos) {
    Compra obj;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, p);
    fclose(p);

    return obj;
}

int ArchivoCompra::contarRegistros() {
    FILE*  p   = fopen(_nombreArchivo, "rb");
    Compra aux;
    if (p == nullptr) return 0;

    int cont = 0;
    while (fread(&aux, tamanioRegistro, 1, p) == 1) {
        cont++;
    }
    fclose(p);
    return cont;
}

int ArchivoCompra::getProximoId(){
    return contarRegistros() + 1;
}

bool ArchivoCompra::listarRegistros() {
    ArchivoProveedor archiProv;
    ArchivoDetalleCompra detArch;

    int cant = contarRegistros();
    if (cant == 0) {
        std::cout << "No hay compras registradas.\n";
        return false;
    }

    for(int i = 0; i < cant; i++){
        Compra c = leerRegistro(i);

        if(c.getEstado()){

            int posProv = archiProv.buscarPorId(c.getIdProveedor());
            Proveedor prov = archiProv.leerRegistro(posProv);

            std::cout << "Proveedor: " << prov.getNombre() << std::endl;
            std::cout << "id proveedor " << c.getIdProveedor() << std::endl;
            c.mostrar(prov.getNombre(), prov.getApellido());
            std::cout << "Detalles:\n";

            int cantDetalles = detArch.listarPorCompra(c.getId());
            if (cantDetalles == 0) {
                std::cout << "   (Sin ítems)\n";
            }
            std::cout << "------------------------------\n\n";
        }
    }
    return true;
}

int ArchivoCompra::modificarRegistro(Compra reg, int pos) {
    FILE* pCompra = fopen(_nombreArchivo, "rb+");

    if (pCompra == nullptr) {
        return -1;
    }

    fseek(pCompra, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCompra);
    fclose(pCompra);

    if (escribio != 1) {
        return -2;
    }

    return 1;
}

int ArchivoCompra::buscarPorId(int idBuscado){
    int tam = contarRegistros();
    for(int i=0; i<tam; i++){
        Compra reg = leerRegistro(i);
        if(reg.getId()==idBuscado){
            return i;
        }
    }
    return -1;
}

int ArchivoCompra::bajaLogica(int id){
    int pos = buscarPorId(id);
    if (pos < 0) return -1;

    Compra compra = leerRegistro(pos);
    if (!compra.getEstado()) return -2;

    Fecha fecha;
    fecha.cargar();

    ArchivoDetalleCompra detArch;

    int puede = detArch.puedeAnularCompra(id);
    if (puede == -1) return -4;
    if (puede == 0) return -3;

    int res = detArch.revertirCompra(id, fecha);
    if(res !=1) return -5;
    compra.setEstado(false);
    modificarRegistro(compra, pos);

    return 1;
}

float ArchivoCompra::gastoAnual(int anio) {
    Compra compra;
    float total = 0.0f;
    int tam = contarRegistros();
    for(int i=0; i <=tam; i++){
        if (compra.getEstado() && compra.getFecha().getAnio() == anio) {
            total += compra.getImporte();
        }
    }
    return total;
}

