#include "persona.h"
#include "cliente.h"
#include "FuncionesGenerales.h"

void cliente::cargar(int id){
    int tipo;

    while(true){
        tipo = PedirEnteroValido("INGRESE EL TIPO CLIENTE: 1. CONSUMIDOR FINAL. / 2. MAYORISTA: ");
        if(setTipoCliente(tipo)) break;
        cout << "ERROR: INGRESE 1 o 2";
    }
    persona::cargar(tipo);

    setIdCliente(id);
}

void cliente::mostrar(){
    std::cout<< "ID: " << getIdCliente() << std::endl;
    std::cout<< "tipo cliente: " << getTipoClienteStr(getTipoCliente()) << std::endl;
    persona::mostrar();

    std::cout << "--------------------------------"<< std::endl;
}

bool cliente::setTipoCliente(int tipo){
    if(tipo==1||tipo==2){
        _tipoCliente = tipo;
        return true;
    }
    return false;
}

void cliente::setIdCliente(int id){
    _idCliente = id;
}

int cliente::getIdCliente(){
    return _idCliente;
}

int cliente::getTipoCliente(){
    return _tipoCliente;
}

std::string cliente::getTipoClienteStr(int tipo){
    switch(tipo){
        case 1: return "PARTICULAR";
        case 2: return "MAYORISTA";
    }
}
