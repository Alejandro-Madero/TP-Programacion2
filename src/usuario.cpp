#include "../include/usuario.h"
#include "../include/persona.h"
#include "../include/ui-console.h"
#include <cstring>


Usuario::Usuario() {
}


Usuario::Usuario(char rol, std::string pass, std::string nombreUsuario, Fecha fecha, int id, std::string telefono, char tipoFJ,
	std::string nombre, std::string direccion, std::string email)
	: Persona(id, telefono, tipoFJ, nombre, direccion, email) {

	this->setRol(rol);
	strcpy(this->_nombreUsuario, nombreUsuario.c_str());
	strcpy(this->_password, pass.c_str());
	this->_id = id;
	this->setTelefono(telefono);
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


bool Usuario::modificarContrasenia(bool modificacionRoot) {
	bool modificandoContrasenia = true;
	std::string contraseniaActual;
	std::string nuevaContrasenia;
	std::string nuevaContraseniaCheck;
	bool volverAlMenuAnterior = false;

	while (modificandoContrasenia) {

		if (!modificacionRoot) {
			std::cout << "Ingrese la contraseña actual o presione 'Q' para volver al menú anterior: ";
			std::getline(std::cin, contraseniaActual);
			volverAlMenuAnterior = UiConsole::volverAlMenuAnterior(contraseniaActual);
			if (volverAlMenuAnterior) return false;
			if (contraseniaActual != this->getPassword()) {
				std::cout << UiConsole::ROJO << "La contraseña ingresada no coincide con la contraseña actual." << UiConsole::RESET << std::endl;
				continue;
			};
		}


		std::cout << "Ingrese la nueva contraseña: ";
		std::getline(std::cin, nuevaContrasenia);

		bool contraseniaValida = Usuario::validarContrasenia(nuevaContrasenia);


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

bool Usuario::actualizarNombreUsuario(Manager& manager) {
	std::string nuevoNombreUsuario;
	bool salirDelMenu = false;
	bool modificandoNombreUsuario = true;

	while (modificandoNombreUsuario) {
		std::cout << "Ingrese el nuevo nombre de usuario o 'Q' para salir de este menu: ";
		std::getline(std::cin, nuevoNombreUsuario);
		salirDelMenu = UiConsole::volverAlMenuAnterior(nuevoNombreUsuario);

		if (salirDelMenu) return false;

		int existeUsuario = manager.buscarUsuario(nuevoNombreUsuario, true);


		if (existeUsuario > 0) {
			std::cout << UiConsole::ROJO << "El nombre de usuario " << UiConsole::VERDE << "'" << nuevoNombreUsuario << "'" << UiConsole::ROJO << " ya esta siendo utilizado por otro usuario. Ingrese otro nombre de usuario." << std::endl;
			continue;
		}

		std::cout << "Nombre de usuario anterior: " << UiConsole::VERDE << this->getNombreUsuario() << UiConsole::RESET << std::endl;
		std::cout << "Nuevo nombre de usuario: " << UiConsole::VERDE << nuevoNombreUsuario << UiConsole::RESET << std::endl;

		this->setNombreUsuario(nuevoNombreUsuario);

		return true;
	}
}

bool Usuario::actualizarRol() {
	//ROL: 	
	std::cout << UiConsole::BOLD << R"(
 Roles
 a: administrador
 u: usuario
 v: vendedor
 c: comprador: )"
		<< UiConsole::RESET << std::endl
		<< std::endl;

	std::string nuevoRol;
	std::cout << "Ingrese el nuevo rol o 'Q' para salir de este menu: ";
	std::getline(std::cin, nuevoRol);

	bool salirDelMenu = UiConsole::volverAlMenuAnterior(nuevoRol); 

	if (salirDelMenu) return false; 

	bool rolValido = Usuario::validarRol(nuevoRol);
	// Validación del rol:
	while (!rolValido)
	{
		std::cout << UiConsole::ROJO << "El rol ingresado no es correcto, ingreselo nuevamente." << UiConsole::RESET << std::endl;
		std::cout << "Ingrese el rol: ";
		std::getline(std::cin, nuevoRol);
		rolValido = Usuario::validarRol(nuevoRol);
	}

	this->setRol(nuevoRol[0]);

	return true; 
}