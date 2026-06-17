#include "Persona.h"
#include "Cliente.h"
#include "FuncionesGenerales.h"

void Cliente::cargar(char* documento, int id, int tipo){
    Persona::cargar();
    setTipoCliente(tipo);
    setIdCliente(id);
}

void Cliente::mostrar(){
    std::cout<< "ID: " << getIdCliente() << std::endl;
    std::cout<< "tipo cliente: " << getTipoClienteStr(getTipoCliente()) << std::endl;
    Persona::mostrar();
}

bool Cliente::setTipoCliente(int tipo){
    if(tipo==1||tipo==2){
        _tipoCliente = tipo;
        return true;
    }
    return false;
}

void Cliente::setIdCliente(int id){
    _idCliente = id;
}

int Cliente::getIdCliente(){
    return _idCliente;
}

int Cliente::getTipoCliente(){
    return _tipoCliente;
}

std::string Cliente::getTipoClienteStr(int tipo){
    switch(tipo){
        case 1: return "PARTICULAR";
        case 2: return "MAYORISTA";
    }
    return "desconocido";
}
