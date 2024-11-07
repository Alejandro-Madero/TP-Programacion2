#include "../include/manager.h"

#include <direct.h>

Manager::Manager() {
   this->archivoCliente = ArchivoCliente();
   this->archivoComposicionFactura = ArchivoComposicionFactura();
   this->archivoComposicionMovimientos = ArchivoComposicionMovimientos();
   this->archivoComposicionOrden = ArchivoComposicionOrden();
   this->archivoComposicionProducto = ArchivoComposicionProducto();
   this->archivoFactura = ArchivoFactura();
   this->archivoMovimientos = ArchivoMovimientos();
   this->archivoOrdenCompra = ArchivoOrdenCompra();
   this->archivoOrdenProduccion = ArchivoOrdenProduccion();
   this->archivoOrdenVenta = ArchivoOrdenVenta();
   this->archivoProveedor = ArchivoProveedor();
   this->archivoRecurso = ArchivoRecurso();
   this->archivoUsuario = ArchivoUsuario();
   if (archivoUsuario.CantidadRegistros() == 0) {
      if (_mkdir("db") != 0) {
         return;  // Directorio creado exitosamente
      }
      this->archivoCliente.Crear();
      this->archivoComposicionFactura.Crear();
      this->archivoComposicionMovimientos.Crear();
      this->archivoComposicionOrden.Crear();
      this->archivoComposicionProducto.Crear();
      this->archivoFactura.Crear();
      this->archivoMovimientos.Crear();
      this->archivoOrdenCompra.Crear();
      this->archivoOrdenProduccion.Crear();
      this->archivoOrdenVenta.Crear();
      this->archivoProveedor.Crear();
      this->archivoRecurso.Crear();
      this->archivoUsuario.Crear();
      this->archivoUsuario.Guardar(Usuario('a', "pass", "root", Fecha(1, 1, 2000), 0, 0, 'F', "root", "root", "root"));
   }
}

bool Manager::login(std::string user, std::string pass) {
   int pos = this->archivoUsuario.Buscar(user);
   if (pos == -1) {
      return false;
   }
   if (this->archivoUsuario.Leer(pos).getPassword() != pass) {
      return false;
   }
   this->_nombreUsuario = this->archivoUsuario.Leer(pos).getNombreUsuario();
   this->_tipoUsuario = this->archivoUsuario.Leer(pos).getTipo();
   return true;
}


std::string Manager::getNombreUsuario() {
   return this->_nombreUsuario;
}
int Manager::buscarUsuario(std::string nombreUsuario) {
   return this->archivoUsuario.Buscar(nombreUsuario);
}

bool Manager::agregarUsuario(Usuario usuario) {
   return this->archivoUsuario.Guardar(usuario);
}

Usuario* Manager::listaUsuarios() {
   return this->archivoUsuario.LeerTodos();
}

int Manager::cantidadUsuarios() {
   return this->archivoUsuario.CantidadRegistros();
}

bool Manager::esAdmin() {
   if (this->_tipoUsuario == 'A' || this->_tipoUsuario == 'a') {
      return true;
   }
   return false;
}

bool Manager::esComprador() {
   if (this->_tipoUsuario == 'C' || this->_tipoUsuario == 'c') {
      return true;
   }
   return false;
}

bool Manager::esVendedor() {
   if (this->_tipoUsuario == 'V' || this->_tipoUsuario == 'v') {
      return true;
   }
   return false;
}

// funcionalidades insumos
int Manager::agregarInsumo(Recurso recurso) {
   recurso.setOrigen(false);
   return this->archivoRecurso.Guardar(recurso);
}

bool Manager::borrarInsumo(int pos) {

   Recurso rs = this->archivoRecurso.Leer(pos);
   rs.setEstaBorrado(true);
   return this->archivoRecurso.Guardar(rs, pos);
}
int Manager::buscarInsumo(std::string codigo) {
   if (codigo.length() > 20 || codigo.length() == 0) {
      return -2;
   }
   int pos = this->archivoRecurso.Buscar(codigo);
   if (this->archivoRecurso.Leer(pos).getOrigen()) {
      return -3;//codigo que existe pero es otra categoria
   }
   if(this->archivoRecurso.Leer(pos).getEstaBorrado()){
      return -4;//el recurso esta borrado
   }
   return pos;
}
bool Manager::estaBorrado(int pos) {
   return this->archivoRecurso.Leer(pos).getEstaBorrado();
}
bool Manager::modificarInsumo(Recurso insumo, int pos) {
   return this->archivoRecurso.Guardar(insumo, pos);
}

bool Manager::listaRecursos(int pos, int cant, bool interno, bool borrado, Recurso*& vector, int &vectorSize) {
   
   int cantRegistros = this->archivoRecurso.CantidadRegistros();
   if(cantRegistros == 0){
      return false;
   }
   if(cant == 0){
      cant = cantRegistros;
   }
   Recurso* vectorTemp = new Recurso[cantRegistros];
   this->archivoRecurso.Leer(cant, vectorTemp);
   if (vectorTemp == nullptr) {
      return false;
   }
   int counter = 0;
   if(interno && !borrado){//producto no borrado
      for (int i = 0; i<cantRegistros; i++){
         if(vectorTemp[i].getOrigen() && !vectorTemp[i].getEstaBorrado()){
            counter++;
         }
      }
      vector = new Recurso[counter];
      if(vector == nullptr){
         vectorSize = 0;
         delete[] vectorTemp;
         return false;
      }
      vectorSize = counter;
      counter = 0;
      for(int i = 0; i < cantRegistros; i++){
         if(vectorTemp[i].getOrigen() && !vectorTemp[i].getEstaBorrado()){
            vector[counter] = vectorTemp[i];
            counter++;
         }
      }
   } 
   else if (interno && borrado) {//producto borrado
      for (int i = 0; i<cantRegistros; i++){
         if(vectorTemp[i].getOrigen() && vectorTemp[i].getEstaBorrado()){
            counter++;
         }
      }
      vector = new Recurso[counter];
      if(vector == nullptr){
         vectorSize = 0;
         delete[] vectorTemp;
         return false;
      }
      vectorSize = counter;
      counter = 0;
      for(int i = 0; i < cantRegistros; i++){
         if(vectorTemp[i].getOrigen() && vectorTemp[i].getEstaBorrado()){
            vector[counter] = vectorTemp[i];
            counter++;
         }
      }
   }
   else if(!interno && !borrado){//insumo no borrado
      for (int i = 0; i<cantRegistros; i++){
         if(!vectorTemp[i].getOrigen() && !vectorTemp[i].getEstaBorrado()){
            counter++;
         }
      }
      vector = new Recurso[counter];
      if(vector == nullptr){
         vectorSize = 0;
         delete[] vectorTemp;
         return false;
      }
      vectorSize = counter;
      counter = 0;
      for(int i = 0; i < cantRegistros; i++){
         if(!vectorTemp[i].getOrigen() && !vectorTemp[i].getEstaBorrado()){
            vector[counter] = vectorTemp[i];
            counter++;
         }
      }
   }
   else if(!interno && borrado){//insumo borrado
      for (int i = 0; i<cantRegistros; i++){
         if(!vectorTemp[i].getOrigen() && vectorTemp[i].getEstaBorrado()){
            counter++;
         }
      }
      vector = new Recurso[counter];
      if(vector == nullptr){
         vectorSize = 0;
         delete[] vectorTemp;
         return false;
      }
      vectorSize = counter;
      counter = 0;
      for(int i = 0; i < cantRegistros; i++){
         if(!vectorTemp[i].getOrigen() && vectorTemp[i].getEstaBorrado()){
            vector[counter] = vectorTemp[i];
            counter++;
         }
      }
   }
   delete[] vectorTemp;
   return true;
}

Recurso Manager::getRecurso(int pos) {
   return this->archivoRecurso.Leer(pos);
}

bool Manager::modificarStockInsumo(int stock, int pos) {
   Recurso recurso = this->archivoRecurso.Leer(pos);
   recurso.setStock(stock);
   return this->archivoRecurso.Guardar(recurso, pos);
}

// funcionalidades productos

int Manager::buscarProducto(std::string codigo) {
   if (codigo.length() > 20 || codigo.length() == 0) {
      return -2;
   }
   int pos = this->archivoRecurso.Buscar(codigo);
   if (!this->archivoRecurso.Leer(pos).getOrigen()) {
      return -3;//codigo que existe pero es otra categoria
   }
   return pos;
}

int Manager::agregarProducto(Recurso producto) {
   producto.setOrigen(true);
   std::cout << producto.getOrigen() << std::endl;
   return this->archivoRecurso.Guardar(producto);
}

bool Manager::borrarProducto(int pos) {
   return this->borrarInsumo(pos);
}
bool Manager::modificarStockRecurso(int stock, int pos) {
   return this->modificarStockInsumo(stock, pos);
}

bool Manager::getComposicionProducto(int pos,Recurso*& vector,int& composicionSize,std::string codigo) {
   ComposicionProducto* allComposicion = nullptr;
   int totalSize = 0;
   this->archivoComposicionProducto.LeerTodo(allComposicion,totalSize);
   if(totalSize == 0 || allComposicion == nullptr){
      return false;
   }
   int counter = 0;
   for(int i = 0; i < totalSize; i++){
      if(allComposicion[i].getIdProducto()== codigo){
         counter++;
      }
   }
   std::string* codigos = new std::string[counter];
   if(codigos == nullptr){
      composicionSize = 0;
      delete[] allComposicion;
      return false;
   }
   composicionSize = counter;
   counter = 0;
   for(int i = 0; i < totalSize; i++){
      if(allComposicion[i].getIdProducto()== codigo){
         codigos[counter] = allComposicion[i].getIdInsumo();
         counter++;
      }
   }

   vector = new Recurso[counter];
   if(vector == nullptr){
      composicionSize = 0;
      delete[] allComposicion;
      delete[] codigos;
      return false;
   }
   composicionSize = counter;
   counter = 0;
   int posTemp = 0;
   for(int i = 0; i < composicionSize; i++){
      posTemp = this->buscarInsumo(codigos[i]);
      vector[i] = this->getRecurso(pos);
      vector[i].setStock(allComposicion[pos].getCantidad());
   }
   delete[] codigos;
   delete[] allComposicion;
   return true;
}
bool Manager::setComposicionProducto(std::string idProducto, std::string idInsumo, int cantidad) {
   ComposicionProducto composicion(idInsumo,idProducto,cantidad);
   return this->archivoComposicionProducto.Guardar(composicion);
}
