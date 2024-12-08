#pragma once
#include <iostream>
#include "fecha.h"

//declaracion anticipada para evitar errores en compilacion y referencias circulares. 
class Manager;

class Persona{
  public:
   Persona();
   Persona(int id, std::string telefono,
               char tipoFJ, std::string nombre, std::string direccion, std::string email);
   Fecha getFecha();
   void setFecha(Fecha f);
   char getTipoFJ();
   void setTipoFJ(char tipoFJ);
   int getId();
   std::string getTelefono(); 
   void setTelefono(std::string telefono);
   void setId(int id);
   std::string getNombre();
   void setNombre(std::string nombre);
   std::string getDireccion();
   void setDireccion(std::string direccion);
   std::string getEmail();
   void setEmail(std::string email);
   static bool validarNombreCompleto(std::string nombreCompleto);
   static bool validarEmail(std::string email);
   static bool validarDireccion(std::string direccion);
   static bool validarTelefono(std::string telefono);
   bool actualizarNombre();   
   bool actualizarEmail(Manager& manager);
   bool actualizarDireccion(); 
   bool actualizarTelefono(Manager& manager); 

  protected:
   int _id;
   char _telefono[25];
   char tipoFJ; //fisica F , juridica J
   char _nombre[51];
   char _direccion[51];
   char _email[100];
   bool _activo;
   Fecha _fechaIngreso;
};