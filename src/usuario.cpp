#include "../include/usuario.h"
#include "../include/persona.h"
#include "../include/ui-console.h"
#include <cstring>


Usuario::Usuario() {
}


Usuario::Usuario(char rol, std::string pass, std::string nombreUsuario, Fecha fecha, int id, int telefono, char tipoFJ,
                 std::string nombre, std::string direccion, std::string email)
    : Persona(id, telefono, tipoFJ, nombre, direccion, email){

   this->setRol(rol);
   strcpy(this->_nombreUsuario, nombreUsuario.c_str());
   strcpy(this->_password, pass.c_str());
   this->_id = id;
   this->_telefono = telefono;
   this->tipoFJ = tipoFJ;
   strcpy(this->_nombre, nombre.c_str());
   strcpy(this->_direccion, direccion.c_str());
   strcpy(this->_email, email.c_str());
   this->_fechaIngreso = Fecha();
   this->setEstadoUsuario(true); 
}

void Usuario::setPassword(std::string password) {
   strcpy(this->_password, password.c_str());
}

std::string Usuario::getPassword() {
   return std::string(this->_password);
}

char Usuario::getRol() {
   return this->_rol;
}

void Usuario::setRol(char rol) {
   this->_rol = rol;
}

std::string Usuario::getNombreUsuario() {
   std::string nombre = std::string(this->_nombreUsuario);
   return nombre;
}

void Usuario::setNombreUsuario(std::string nombreUsuario) {    
   strcpy(this->_nombreUsuario, nombreUsuario.c_str());
}


bool Usuario::getEstadoUsuario() {
    return this->_usuarioActivo; 
}

void Usuario::setEstadoUsuario(bool estado) {
    this->_usuarioActivo = estado; 
}


bool Usuario::validarUsuario(std::string usuario) {
    return usuario.size() > 3 && usuario.size() < 21;
};

bool Usuario::validarContrasenia(std::string contrasenia) {
    return contrasenia.size() > 3 && contrasenia.size() < 21;
};

bool Usuario::validarRol(std::string rol) {
    if (rol == "a" || rol == "A") return true;
    else if (rol == "u" || rol == "U") return true;
    else if (rol == "v" || rol == "V") return true;
    else if (rol == "c" || rol == "C") return true;
    else return false;
}


bool Usuario::modificarContrasenia() {
    bool modificandoContrasenia = true;
    std::string nuevaContrasenia;
    std::string nuevaContraseniaCheck;

    while (modificandoContrasenia) {

        std::cout << "Ingrese la nueva contraseña o presione 'Q' para volver al menú anterior: ";
        std::getline(std::cin, nuevaContrasenia);

        bool contraseniaValida = Usuario::validarContrasenia(nuevaContrasenia);

        if (nuevaContrasenia == "q" || nuevaContrasenia == "Q") return false;

        if (nuevaContrasenia == this->getPassword()) {
            std::cout << UiConsole::ROJO << "La nueva contraseña no puede ser igual a la actual." << UiConsole::RESET << std::endl;
            continue;
        }
        if (!contraseniaValida) {
            std::cout << UiConsole::ROJO << "La contraseña debe tener como mínimo 4 caracteres y como máximo 20." << UiConsole::RESET << std::endl;
            continue;
        }


        std::cout << "Ingrese la nueva contraseña nuevamente: ";
        std::getline(std::cin, nuevaContraseniaCheck);

        if (nuevaContrasenia == nuevaContraseniaCheck) {
            this->setPassword(nuevaContrasenia);
            modificandoContrasenia = false;
            return true;
        }
        else {
            std::cout << UiConsole::ROJO << "Las contraseñas ingresadas no coinciden. Vuelva a ingresarlas." << UiConsole::RESET << std::endl;
        }               
    }
}