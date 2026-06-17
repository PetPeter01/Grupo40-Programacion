#include <iostream>

#include "compra.h"
#include "venta.h"
#include "detalleCompra.h"
#include "detalleVenta.h"

using namespace std;

int main(){

    int opcion;

    do{

        cout << "\n=====================================\n";
        cout << "      MENU DE PRUEBAS\n";
        cout << "=====================================\n";
        cout << "1 - Probar Compra\n";
        cout << "2 - Probar Venta\n";
        cout << "3 - Probar Detalle Compra\n";
        cout << "4 - Probar Detalle Venta\n";
        cout << "0 - Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion){

        case 1:{
            compra compra;

            int idCompra;
            int idProveedor;
            float importe;

            cout << "\nID COMPRA: ";
            cin >> idCompra;

            cout << "ID PROVEEDOR: ";
            cin >> idProveedor;

            cout << "IMPORTE TOTAL: ";
            cin >> importe;

            compra.cargar(idCompra,idProveedor,importe);

            cout << "\nDATOS INGRESADOS\n";
            compra.mostrar();

            break;
        }

        case 2:{
            Venta venta;

            int idVenta;
            int idCliente;
            float importe;

            cout << "\nID VENTA: ";
            cin >> idVenta;

            cout << "ID CLIENTE: ";
            cin >> idCliente;

            cout << "IMPORTE TOTAL: ";
            cin >> importe;

            venta.cargar(idVenta,idCliente,importe);

            cout << "\nDATOS INGRESADOS\n";
            venta.mostrar();

            break;
        }

        case 3:{
            DetalleCompra detalle;

            int idDetalle;
            int idCompra;
            int idProducto;

            cout << "\nID DETALLE COMPRA: ";
            cin >> idDetalle;

            cout << "ID COMPRA: ";
            cin >> idCompra;

            cout << "ID PRODUCTO: ";
            cin >> idProducto;

            detalle.cargar(idDetalle,idCompra,idProducto);

            cout << "\nDATOS INGRESADOS\n";
            detalle.mostrar();

            break;
        }

        case 4:{
            DetalleVenta detalle;

            int idDetalle;
            int idVenta;
            int idProducto;

            cout << "\nID DETALLE VENTA: ";
            cin >> idDetalle;

            cout << "ID VENTA: ";
            cin >> idVenta;

            cout << "ID PRODUCTO: ";
            cin >> idProducto;

            detalle.cargar(idDetalle,idVenta,idProducto);

            cout << "\nDATOS INGRESADOS\n";
            detalle.mostrar();

            break;
        }

        case 0:
            cout << "\nFin del programa.\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    }while(opcion != 0);

    return 0;
}
