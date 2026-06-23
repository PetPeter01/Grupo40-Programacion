#include <iostream>
#include "Transaccion.h"
#include "Fecha.h"
#include "FuncionesGenerales.h"

void Transaccion::cargar(int id, float importe) {
    setId(id);

    Fecha fecha;
    fecha.cargar();
    setFecha(fecha);

    while (true) {
        int formaPago = PedirEnteroValido("FORMA DE PAGO: 1. EFECTIVO / 2. TRANSFERENCIA / 3. TARJETA DE DEBITO / 4. TARJETA DE CREDITO: ");
        if (setFormaDePago(formaPago)) {
            break;
        }
        std::cout << "ERROR: ingrese una forma de pago valida.\n";
    }

    setImporteTotal(importe);
    setEstado(true);
}

void Transaccion::mostrar() {
    std::cout << "FECHA: " << getFecha().toString() << std::endl;
    std::cout << "FORMA DE PAGO: " << getFormaDePagoStr(getFormaDePago()) << std::endl;
    std::cout << "IMPORTE TOTAL: " << getImporte() << std::endl;
    std::cout << "ESTADO: " << getEstado() << std::endl;
}

int Transaccion::getId() {
    return _idTransaccion;
}

Fecha Transaccion::getFecha() {
    return _fecha;
}

float Transaccion::getImporte() {
    return _importe;
}

int Transaccion::getFormaDePago() {
    return _formaDePago;
}

bool Transaccion::getEstado() {
    return _estado;
}

std::string Transaccion::getFormaDePagoStr(int formaPago) {
    switch (formaPago) {
        case 1: return "EFECTIVO";
        case 2: return "TRANSFERENCIA";
        case 3: return "TARJETA DE DEBITO";
        case 4: return "TARJETA DE CREDITO";
    }
    return "DESCONOCIDO";
}

bool Transaccion::setId(int idTransaccion) {
    if (idTransaccion < 0) {
        return false;
    }
    _idTransaccion = idTransaccion;
    return true;
}

void Transaccion::setFecha(Fecha fecha) {
    _fecha = fecha;
}

void Transaccion::setImporteTotal(float ImporteTotal) {
    _importe = ImporteTotal;
}

bool Transaccion::setFormaDePago(int formaPago) {
    if (formaPago > 0 && formaPago < 5) {
        _formaDePago = formaPago;
        return true;
    }
    return false;
}

void Transaccion::setEstado(bool estado) {
    _estado = estado;
}

