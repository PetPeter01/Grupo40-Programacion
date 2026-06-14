#include "persona.h"
#include "FuncionesGenerales.h"
#include <cstring>

persona::persona(char* documento, char* nombre, char* apellido, char* numeroTelefono, char* correo, char* direccion, bool estado){
    strcpy(_documento, documento);
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_numeroTelefono, numeroTelefono);
    strcpy(_correoElectronico, correo);
    strcpy(_direccion, direccion);
    _estado = estado;
}

persona::persona() {
    strcpy(_documento, "");
    std::strcpy(_nombre, "");
    std::strcpy(_apellido, "");
    std::strcpy(_numeroTelefono, "");
    std::strcpy(_correoElectronico, "");
    std::strcpy(_direccion, "");
    _estado = false;
}
void persona::cargarDocumento(int tipoDocumento) {
    char documento[20];
    const char* etiqueta = (tipoDocumento == 1) ? "DNI: " : (tipoDocumento == 2) ? "CUIT: " : "CUIL: ";

    while (true) {
        std::cout << etiqueta;
        std::cin >> documento;

        if (tipoDocumento == 1) {
            if (setDni(documento)) break;
        } else {
            if (setCuit(documento)) break;
        }
        std::cout << "ERROR: Documento invalido.\n";
    }
}

void persona::cargarTelefono() {
    char numeroTelefono[20];
    while (true) {
        std::cout << "TELEFONO: ";
        std::cin >> numeroTelefono;

        int resultado = setNumeroTelefono(numeroTelefono);
        if (resultado == 1) break;

        if (resultado == -1) std::cout << "ERROR: solo numeros.\n";
        else if (resultado == -2) std::cout << "ERROR: ingrese cantidad de digitos valida (10).\n";
    }
}

void persona::cargar(int tipoDocumento) {

    cargarDocumento(tipoDocumento);

    while (true) {
        char nombre[20];
        std::cout << "NOMBRE: ";
        std::cin >> nombre;
        if (setNombre(nombre)) break;
        std::cout << "ERROR: nombre invalido, solo letras.\n";
    }

    while (true) {
        char apellido[20];
        std::cout << "APELLIDO: ";
        std::cin >> apellido;
        if (setApellido(apellido)) break;
        std::cout << "ERROR: apellido invalido, solo letras.\n";
    }

    cargarTelefono();

    while (true) {
        char correoEletronico[50];
        std::cout << "CORREO ELECTRONICO: ";
        std::cin >> correoEletronico;
        if (setCorreoElectronico(correoEletronico)) break;
        std::cout << "ERROR: ingrese un correo valido.\n";
    }

    std::cout << "DIRECCION: ";
    char direccion[20];
    std::cin >> direccion;
    setDireccion(direccion);

    setEstado(true);
    std::cout << "\nCARGA EXITOSA\n" << std::endl;
}

void persona::mostrar(){
    std::cout<< "Documento: " << getDocumento() << std::endl;
    std::cout<< "Nombre: " << getNombre() << " " << getApellido() << std::endl;
    std::cout<< "Telefono: " << getNumeroTelefono() << std::endl;
    std::cout<< "Correo Electronico: " << getCorreoElectronico() << std::endl;
    std::cout<< "Direccion: " << getDireccion() << std::endl;
    std::cout << "Estado: " << getEstadoStr() << std::endl;

    std::cout << "--------------------------------"<< std::endl;
}
// getters

char* persona::getDocumento(){
return _documento;
}
char* persona::getNombre(){
    return _nombre;
}
char* persona::getApellido(){
    return _apellido;
}
char* persona::getNumeroTelefono(){
    return _numeroTelefono;
}
char* persona::getCorreoElectronico(){
    return _correoElectronico;
}
char* persona::getDireccion(){
    return _direccion;
}
bool persona::getEstado(){
    return _estado;
}
string persona::getEstadoStr(){
    if(_estado ==1){
        return "activo";
    }
    return "inactivo";
}
// setters

bool persona::setDni(char* documento){
    int len = strlen(documento);
    if (len==8){
        strcpy(_documento, documento);
        return true;
    }
    return false;
}

bool persona::setCuit(char* documento){
    int len = strlen(documento);
    if(len==11){
        strcpy(_documento, documento);
        return true;
    }
    return false;
}

bool persona::setNombre(char* nombre){
    if(esTextoValido(nombre)){
        strcpy(_nombre, nombre);
        return true;
    }
    return false;
}

bool persona::setApellido(char* apellido){
    if(esTextoValido(apellido)){
        strcpy(_apellido, apellido);
        return true;
    }
    return false;
}

int persona::setNumeroTelefono(char *telefono){
    int len = strlen(telefono);
    int num;

    if (!esEnteroValido(telefono, num)) {
        return -1;
    }

    if (len != 10) {
        return -2;
    }

    strcpy(_numeroTelefono, telefono);
    return 1;
}

bool persona::setCorreoElectronico(char* correoElectronico){
    bool tieneArroba = false;

    for(int i = 0; correoElectronico[i] != '\0'; i++){
        if(correoElectronico[i] == '@'){
            tieneArroba = true;
            break;
        }
    }

    if(!tieneArroba){
        return false;
    }

    strcpy(_correoElectronico, correoElectronico);
    return true;
}

void persona::setDireccion(char* direccion){
    strcpy(_direccion, direccion);
}

void persona::setEstado(bool estado){
    _estado = estado;
}

