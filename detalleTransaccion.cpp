#include "DetalleTransaccion.h"
#include "FuncionesGenerales.h"

void DetalleTransaccion::cargar(int idDetalle, int idTransaccion, int idProducto, float precioUnitario){
    int cant;
    setPrecioUnitario(precioUnitario);
    setIdProducto(idProducto);
    while (true) {
        cant = PedirEnteroValido("CANTIDAD COMPRADA: ");
        if (setCantidad(cant)) break;
        cout << "Cantidad invalida (debe ser > 0).\n";
    }

    setSubtotal(calcularSubtotal(precioUnitario, cant));

}

void DetalleTransaccion::mostrar() {
    cout << "ID Producto: "      << getIdProducto() << endl;
    cout << "Cantidad: "         << getCantidad() << endl;
    cout << "Costo Unitario: $"  << getPrecioUnitario() << endl;
    cout << "Subtotal: $"        << getSubtotal() << endl;
    cout << "--------------------------------\n";
}

float DetalleTransaccion::calcularSubtotal(float precioUnitario, int cantidad){
    return precioUnitario * cantidad;
}

bool DetalleTransaccion::setIdDetalleTransaccion(int idDetalleTransaccion){
    if(idDetalleTransaccion<0){
        return false;
    }
    _idDetalleTransaccion = idDetalleTransaccion;
    return true;
}

void DetalleTransaccion::setIdTransaccion(int idTransaccion){
    _idTransaccion = idTransaccion;
}

bool DetalleTransaccion::setSubtotal(float subtotal){
    if(subtotal>0){
        _subtotal = subtotal;
        return true;
    }
    return false;
}

void DetalleTransaccion::setIdProducto(int idProducto){
    _idProducto = idProducto;
}

bool DetalleTransaccion::setCantidad(int cantidad){
    if(cantidad>0){
        _cantidad = cantidad;
        return true;
    }
    return false;
}

bool DetalleTransaccion::setPrecioUnitario(float precioUnitario){
    if(precioUnitario>0){
        _precioUnitario = precioUnitario;
        return true;
    }
    return false;
}

int DetalleTransaccion::getIdDetalleTransaccion(){
    return _idDetalleTransaccion;
}

int DetalleTransaccion::getIdTransaccion(){
    return _idTransaccion;
}

int DetalleTransaccion::getIdProducto(){
    return _idProducto;
}

int DetalleTransaccion::getCantidad(){
    return _cantidad;
}

float DetalleTransaccion::getPrecioUnitario(){
    return _precioUnitario;
}

float DetalleTransaccion::getSubtotal(){
    return _subtotal;
}

bool DetalleTransaccion::getEstado(){
    return _subtotal;
}
