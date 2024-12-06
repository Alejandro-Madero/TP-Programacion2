#pragma once
#include <iostream>
#include "persona.h"

 
class Usuario : public Persona {
  public:
   Usuario();
   Usuario(char rol, std::string pass, std::string nombreUsuario, Fecha fecha, int id, int telefono, char tipoFJ, std::string nombre,
           std::string direccion, std::string email);

   std::string getPassword();
   void setPassword(std::string password);
   char getRol();
   void setRol(char rol);
   std::string getNombreUsuario();
   void setNombreUsuario(std::string nombreUsuario);
   static bool validarUsuario(std::string usuario);
   static bool validarContrasenia(std::string contrasenia);   
   static bool validarRol(std::string rol);   
   bool modificarContrasenia(); 
   bool getEstadoUsuario();
   void setEstadoUsuario(bool estado); 

  private:
   char _rol; // a = administrador, v = vendedor, u = usuario, c = comprador
   char _password[21];
   char _nombreUsuario[21];  
   bool _usuarioActivo; 
};