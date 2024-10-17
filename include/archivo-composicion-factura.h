#pragma once
#include <string>
#include "composicion-factura.h"

class ArchivoComposicionFactura{
    private:
        const char * _nombreArchivo  = "composicion-factura.dat";
        
    public:
        ArchivoComposicionFactura();
        bool Guardar(ComposicionFactura composicion);
        bool Guardar(ComposicionFactura composicion, int posicion);
        int Buscar(int nroFactura, char tipo);
        ComposicionFactura Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, ComposicionFactura *vector);
};