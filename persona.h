#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include <iostream>

class persona {
    private:
        int _tipo;
        char _documento[13];
        char _nombre[20];
        char _apellido[20];
        char _numeroTelefono[20];
        char _correoElectronico[50];
        char _direccion[50];
        bool _estado;

    public:
        persona(char* documento, char* nombre, char* apellido, char* numeroTelefono, char* correo, char* direccion, bool estado);
        persona();
        int getTipo();
        char* getDocumento();
        char* getNombre();
        char* getApellido();
        char* getNumeroTelefono();
        char* getCorreoElectronico();
        char* getDireccion();
        bool getEstado();
        std::string getEstadoStr();

        bool setDni(char* documento);
        bool setCuit(char* documento);
        bool setNombre(char* nombre);
        bool setApellido(char* apellido);
        int setNumeroTelefono(char* numTelefono);
        bool setCorreoElectronico(char* correoElectronico);
        void setDireccion(char* correoElectronico);
        void setEstado(bool estado);

        void cargar(int tipoDocumento);
        void cargarDocumento(int tipoDocumento);
        void cargarTelefono();
        void mostrar();
};

#endif // PERSONA_H_INCLUDED
