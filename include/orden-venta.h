#pragma once
#include <iostream>
#include "orden.h"


class OrdenVenta:Orden{
  public:
   OrdenVenta();
   OrdenVenta(int idCliente);
   
   
   int getIdCliente();
   void setIdCliente(int id);


  private:
   int _idCliente;

};