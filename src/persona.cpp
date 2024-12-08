#include "../include/persona.h"
#include "../include/ui-console.h"
#include "../include/manager.h"
#include <cstring>
#include <regex>

Persona::Persona() {
   this->_id = 0;  
   this->tipoFJ = ' ';
   strcpy(this->_nombre, " ");
   strcpy(this->_direccion, " ");
   strcpy(this->_email, " ");
   this->_fechaIngreso = Fecha();
   this->_activo = true;
}

Persona::Persona(int id, std::string telefono,
                 char tipoFJ, std::string nombre, std::string direccion, std::string email) {
   this->_id = id;  
   this->setTelefono(telefono);
   this->tipoFJ = tipoFJ;
   strcpy(this->_nombre, nombre.c_str());
   strcpy(this->_direccion, direccion.c_str());
   strcpy(this->_email, email.c_str());
   this->_fechaIngreso = Fecha();
}

Fecha Persona::getFecha() {
   return this->_fechaIngreso;
}

void Persona::setFecha(Fecha f) {
   this->_fechaIngreso = f;
}

char Persona::getTipoFJ() {
   return this->tipoFJ;
}

void Persona::setTipoFJ(char tipoFJ) {
   this->tipoFJ = tipoFJ;
}

int Persona::getId() {
   return this->_id;
}

void Persona::setId(int id) {
   this->_id = id;
}

std::string Persona::getNombre() {
   return this->_nombre;
}

void Persona::setNombre(std::string nombre) {
   strcpy(this->_nombre, nombre.c_str());
}

std::string Persona::getDireccion() {
   return this->_direccion;
}

void Persona::setDireccion(std::string direccion) {
   strcpy(this->_direccion, direccion.c_str());
}

std::string Persona::getEmail() {
   return this->_email;
}

void Persona::setEmail(std::string email) {
   strcpy(this->_email, email.c_str());
}

std::string Persona::getTelefono() {
    return this->_telefono; 
}

void Persona::setTelefono(std::string telefono) {
    strcpy(this->_telefono, telefono.c_str());
}

bool Persona::validarNombreCompleto(std::string nombreCompleto) {
    std::regex regex("[a-zA-Z]{2,} [a-zA-Z]{2,}");
    return std::regex_match(nombreCompleto, regex);
}

bool Persona::validarEmail(std::string email) {
    std::regex regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$");
    return std::regex_match(email, regex);
}

bool Persona::validarDireccion(std::string direccion) {
    return direccion.length() >= 4 && direccion.length() < 51;
}

bool Persona::validarTelefono(std::string telefono) {
    if (telefono.size() < 8) return false;

    return std::all_of(telefono.begin(), telefono.end(), ::isdigit);
}

bool Persona::actualizarNombre() {
    //NOMBRE:
    std::string nombre;
    std::cout << "Ingrese el nombre o 'Q' para salir de este menu: ";
    std::getline(std::cin, nombre);
    //Validación del nombre completo: 
    bool nombreEsCorrecto = Persona::validarNombreCompleto(nombre);

    if (nombre == "q" || nombre == "Q") return false; 

    while (!nombreEsCorrecto) {
        std::cout << UiConsole::ROJO << "El valor ingresado no es un nombre correcto. Formato correcto: 'Nombre Apellido'. Ingreselo nuevamente." << UiConsole::RESET << std::endl;
        std::cout << "Nombre completo:";
        std::getline(std::cin, nombre);
        nombreEsCorrecto = Persona::validarNombreCompleto(nombre);
    }

    this->setNombre(nombre); 

    return true; 
};

bool Persona::actualizarEmail(Manager& manager) {

    //EMAIL:
    std::string email; 
    std::cout << "Ingrese el nuevo email o 'Q' para salir de este menu: ";
    std::getline(std::cin, email);

    if (email == "q" || email == "Q") return false; 

    //Validacion del formato del email: 
    bool formatoCorrectoEmail = Persona::validarEmail(email);

    while (!formatoCorrectoEmail) {
        std::cout << UiConsole::ROJO << "El valor ingresado no tiene un formato correcto (ejemplo: mimail@mailito.com). Ingrese nuevamente un valor." <<UiConsole::RESET << std::endl;
        std::cout << "Email: ";
        std::getline(std::cin, email);
        formatoCorrectoEmail = Persona::validarEmail(email);
    }
    int mailExiste = manager.buscarEmail(email, true);

    // Validación de la existencia del email en la base de datos:
    while (mailExiste >= 0)
    {
        std::cout << UiConsole::ROJO << "El mail ingresado " << UiConsole::VERDE << "'" << email << "'" << UiConsole::ROJO
            << " ya está registrado para otro usuario. Ingrese otro email." << UiConsole::RESET << std::endl;
        std::cout << "Email: ";
        std::getline(std::cin, email);
        mailExiste = manager.buscarEmail(email, true);
    }

    this->setEmail(email); 

    return true; 
};

bool Persona::actualizarDireccion() {
    std::string direccion; 
   
    std::cout << "Ingrese la nueva direccion o 'Q' para salir de este menu: ";
    std::getline(std::cin, direccion);

    if (direccion == "q" || direccion == "Q") return false; 

    bool direccionValida = Persona::validarDireccion(direccion);

    while (!direccionValida) {
        std::cout << UiConsole::ROJO << "La dirección debe tener minimo 4 caracteres y maximo 50. Ingrese un valor válido" <<UiConsole::RESET << std::endl;
        std::cout << "Direccion: ";
        std::getline(std::cin, direccion);
        direccionValida = Usuario::validarDireccion(direccion);
    }

    this->setDireccion(direccion);

    return true; 

};

bool Persona::actualizarTelefono(Manager& manager) {

    std::string telefono;
    bool salirDelMenu = false;

    std::cout << "Ingrese el nuevo numero de telefono o 'Q' para salir de este menu: ";
    std::getline(std::cin, telefono);

    salirDelMenu = UiConsole::volverAlMenuAnterior(telefono);
    if (salirDelMenu) return false;

    // Validación formato del numero de telefono: 

    bool telefonoValido = Usuario::validarTelefono(telefono);
    while (!telefonoValido)
    {
        std::cout << UiConsole::ROJO << "El valor ingresado no es un número. Ingreselo nuevamente." << UiConsole::RESET << std::endl;
        std::cout << "Telefono o 'Q' para salir: ";
        std::getline(std::cin, telefono);

        salirDelMenu = UiConsole::volverAlMenuAnterior(telefono);
        if (salirDelMenu) return false;

        telefonoValido = Usuario::validarTelefono(telefono);
    }

    //Validación de la existencia del numero de telefono en la base de datos : 
    int telefonoYaRegistrado = manager.buscarTelefono(telefono, true);

    while (telefonoYaRegistrado >= 0)
    {
        std::cout << UiConsole::ROJO << "El telefono ingresado " << UiConsole::VERDE << "'" << telefono << "'" << UiConsole::ROJO
            << " ya está registrado para otro usuario. Ingrese otro telefono." << UiConsole::RESET << std::endl;
        std::cout << "Telefono o 'Q' para salir: ";
        std::getline(std::cin, telefono);

        salirDelMenu = UiConsole::volverAlMenuAnterior(telefono);
        if (salirDelMenu) return false;

        telefonoYaRegistrado = manager.buscarTelefono(telefono, true);
    }

   
       this->setTelefono(telefono);
       return true; 
}

