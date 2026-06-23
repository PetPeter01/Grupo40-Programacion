#ifndef DETALLETRANSACCION_H_INCLUDED
#define DETALLETRANSACCION_H_INCLUDED

class DetalleTransaccion {
    private:
        int _idDetalleTransaccion;
        int _idTransaccion;
        int _idProducto;
        int _cantidad;
        float _precioUnitario;
        float _subtotal;
        bool _estado;

    public:
        void cargar(int idDetalle, int idTransaccion, int idProducto, float PrecioUnitario);
        void mostrar();
        float calcularSubtotal(float precioUnitario, int cantidad);

        bool setIdDetalleTransaccion(int idDetalleTransaccion);
        void setIdTransaccion(int idTransaccion);
        bool setSubtotal(float subtotal);
        void setIdProducto(int idProducto);
        bool setCantidad(int cantidad);
        bool setPrecioUnitario(float precioUnitario);

        int getIdDetalleTransaccion();
        int getIdTransaccion();
        int getIdProducto();
        int getCantidad();
        float getPrecioUnitario();
        float getSubtotal();
        bool getEstado();

};

#endif // DETALLETRANSACCION_H_INCLUDED
