/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha: 
Problema: 
Versión: 1.0*/

//Bibliotecas utilizadas
#include <iostream> //Librería Estandar de Input y Output
#include <stdlib.h> //Librería Estandar para Funciones Específicas
#include <vector> //Librería de Vectores para el Manejo de Memoría y Arreglos Dinámicos
#include <ctime> //Librería para Obtener la Hora y Fecha del Sistema
//Librería para la Escritura y Lectura de Archivos (En este caso .CSV)
#include <fstream>
#include <sstream>

using namespace std;
class Mantenimiento;
class Vehiculo;
class GIVAM;

//------------------------------------------Clase Gestor de Seguridad ----------------------------------------------------------
/*
Clase Estática Encargada de Encriptar la Contraseña y verificarla.
Utiliza un Hash sencillo para su encriptación.
De esta manera, en los registros, a pesar de aparecer los usuarios, aparece la contraseña encriptada en forma de números.
El programa NO DESENCRIPTA la contraseña, sino lo que hace es encriptar el intento de contraseña y compara los hashes, por lo que la contraseña real
solo aparace cuando el usuario la pone.
*/

class GestorSeguridad{
    public:
        static string generarHash(const string); //Encripta la Contraseña
        static bool verificarHash(const string, const string); //Verifica la contraseña encriptada guardada, con la encriptacion de la contraseña ingresada
};

//Generar un Hash de Seguridad
string GestorSeguridad::generarHash(const string contrasena){
    hash<string> hash;
    size_t valor = hash(contrasena);
    return to_string(valor);
}

//Verificar si La Contraseña Ingresada es Correcta
bool GestorSeguridad::verificarHash(const string contrasena, const string contrasenaGuardada){
    if(GestorSeguridad::generarHash(contrasena) == contrasenaGuardada)
        return true;
    return false;
}

//------------------------------------------Clase Usuario ----------------------------------------------------------

class Usuario{
    protected:
        //Atributos que también se almacenan en Usuarios.CSV
        string nombreDeUsuario;
        string contrasena;
        string nombre;
        int edad;

    public:
        Usuario(string, string, string, int);
        virtual ~Usuario(); //Destructor Virtual
        virtual string getTipoUsuario() = 0; //Método Abstracto Puro que Será Muy Útil con el Polimorfismo Dinámico
        void mostrarInformacion(); //Imprime la Información de la Clase Padre; se utilizará posteriormente con Polimorfismo Dinámico

        //Getter's
        string getNombreUsuario();
        string getContrasena();
        string getNombre();
        int getEdad();

        //Setter's
        void setNombreUsuario(string);
        void setContrasena(string);
        void setNombre(string);
        void setEdad(int);
};


Usuario::Usuario(string nombreDeUsuario, string contrasena, string nombre, int edad){
    this->nombreDeUsuario = nombreDeUsuario;
    this->contrasena = contrasena; //Se le pasa como atributo la contraseña ya encriptada
    this->nombre = nombre;
    this->edad = edad;
}

Usuario::~Usuario(){}

//Setter's
void Usuario::setNombreUsuario(string nombreDeUsuario){this->nombreDeUsuario = nombreDeUsuario;}
void Usuario::setContrasena(string contrasena){this->contrasena = contrasena;}
void Usuario::setNombre(string nombre){this->nombre = nombre;}
void Usuario::setEdad(int edad){this->edad = edad;}

void Usuario::mostrarInformacion(){
    cout<<"Usuario del Tipo "<<getTipoUsuario()<<":"<<endl;
    cout<<"Nombre del "<<getTipoUsuario()<<":"<<nombreDeUsuario<<endl;
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}

//Getter's
string Usuario::getNombreUsuario(){return nombreDeUsuario;}
string Usuario::getContrasena(){return contrasena;}
string Usuario::getNombre(){return nombre;}
int Usuario::getEdad(){return edad;}

//------------------------------------------Clase Administrador ----------------------------------------------------------
//------------------------------------------Clase Hija de Usuario ----------------------------------------------------------

class Administrador : public Usuario{
    public:
        Administrador(string, string, string, int);
        string getTipoUsuario() override; //Sobreescritura del Método Abstracto
};

Administrador::Administrador(string nombreDeUsuario, string contrasena, string nombre, int edad) : Usuario(nombreDeUsuario, contrasena, nombre, edad){}

//Sobreescritura del Método Abstracto
string Administrador::getTipoUsuario(){return "Administrador";}

//------------------------------------------Clase Mecánico ----------------------------------------------------------
//------------------------------------------Clase Hija de Usuario ----------------------------------------------------------

class Mecanico: public Usuario{
    public:
        Mecanico(string,string,string,int);
        string getTipoUsuario() override; //Sobreescitura del Método Abstracto Puro
};

Mecanico::Mecanico(string nombreDeUsuario, string contrasena, string nombre, int edad) : Usuario(nombreDeUsuario, contrasena, nombre, edad){}

string Mecanico::getTipoUsuario(){
    return "Mecanico"; //Sobreescritura del Método Abstracto Puro
}

//------------------------------------------Clase Fecha ----------------------------------------------------------
class Fecha{
    private:
        int dia;
        int mes;
        int anio;

    public:
        Fecha(); //Constructor por Defecto. Pone los atributos en base del día del sistema
        Fecha(int,int,int); //Sobrecarga del Constructor de Fecha, se le ponen manualmente valores a los atributos
        void mostrarFecha(); 
       //Gette's
        int getDia();
        int getMes();
        int getAnio();
        //Sobreescritura de los operadores de Comparación
        //Súmante útiles para comparar Fechas y determinar si son iguales, menores, iguales, etc.
        bool operator<(const Fecha&) const;
        bool operator>(const Fecha&) const;
        bool operator==(const Fecha&) const;
        bool operator<=(const Fecha&) const;
        bool operator>=(const Fecha&) const;
};

//Constructor por Defecto.
Fecha::Fecha(){
    //Settea los atributos de la Fecha a los valores actuales del Sistema
    time_t tiempoActual = time(0);
    tm* tiempoLocal = localtime(&tiempoActual);

    dia = tiempoLocal->tm_mday;
    mes = tiempoLocal->tm_mon + 1;
    anio = tiempoLocal->tm_year + 1900;
}

//Constructor Manual
Fecha::Fecha(int dia, int mes, int anio){
    //Settea los atributos del Sistema a Valores dados
    this->dia = dia;
    this-> mes = mes;
    this-> anio = anio;
}

void Fecha::mostrarFecha(){cout<<dia<<"/"<<mes<<"/"<<anio;}

//Gette's
int Fecha::getDia(){return dia;}
int Fecha::getMes(){return mes;}
int Fecha::getAnio(){return anio;}

//Sobreescritura de los Operadores Comparativos
bool Fecha::operator<(const Fecha &otraFecha) const{
    if(anio != otraFecha.anio)
        return anio<otraFecha.anio;
    else if(mes != otraFecha.mes)
        return mes < otraFecha.mes;
    else
        return dia < otraFecha.dia;
}

bool Fecha::operator>(const Fecha &otraFecha) const{
    return otraFecha < *this;
}

bool Fecha::operator==(const Fecha &otraFecha) const{
    return dia==otraFecha.dia && mes==otraFecha.mes && anio == otraFecha.anio;
}

bool Fecha::operator<=(const Fecha &otraFecha) const{
    if(*this < otraFecha || *this==otraFecha){
        return true;
    } 
    else
        return false;
}

bool Fecha::operator>=(const Fecha &otraFecha) const{
    if(*this > otraFecha || *this == otraFecha){
        return true;
    }
    else
        return false;
}

//------------------------------------------Clase Mantenimientos ----------------------------------------------------------
class Mantenimiento{
    protected:
        int id;
        Vehiculo* vehiculo; //Apuntador a Vehiculo
        Mecanico* responsable; //Apuntador al Mecanico responsable
        Fecha fechaRealizacion;
        string descripcion;
        float costo;
    public:
        Mantenimiento(int, Vehiculo*, Mecanico*, Fecha, string, float);
        virtual ~Mantenimiento(); //Destructor Virtual
        virtual void mostrarInformacion();
        virtual string getTipo() = 0; //Método Abstracto Puro Útil para el Polimorfismo Dinámico
        
        //Gette's
        int getId();
        Fecha getFecha();
        Vehiculo* getVehiculo();
        Mecanico* getResponsable();
        string getDescripcion();
        float getCosto();

        //Setter's
        void setId(int);
        void setResponsable(Mecanico*);
        void setFechaRealizacion(Fecha);
        void setDescripcion(string);
        void setCosto(float);
};

//------------------------------------------Clase Padre Vehículo ----------------------------------------------------------
class Vehiculo{
    protected:
        string placas;
        string marca;
        string modelo;
        int anio;
        float kilometraje;
        vector<Mantenimiento*> historial; //Vector de Apuntadores a los Mantenimientos realizados a Este Vehículo
        Fecha ultimoMantenimiento;

    public:
        Vehiculo(string, string, string, int, float, Fecha);
        virtual  ~Vehiculo(); //Destructor Virtual
        virtual string getTipoVehiculo() = 0; //Método Abstracto Puro Útil para el Polimorfsimos Dinámico Posterior
        virtual void mostrarInformacion();
        void agregarMantenimiento(Mantenimiento*);
        void mostrarHistorial();
        bool eliminarMantenimiento(int);


        //Getter's
        string getPlacas();
        string getMarca();
        string getModelo();
        int getAnio();
        float getKilometraje();
        Fecha getFechaUltimoMantenimiento();
        vector<Mantenimiento*> getHistorial();

        //Setter's
        void setPlacas(string);
        void setMarca(string);
        void setModelo(string);
        void setAnio(int);
        void setKilometraje(float);
        void actualizarUltimoMantenimiento();

};

//Constructor de Vehículo
Vehiculo::Vehiculo(string placas, string marca, string modelo, int anio, float kilometraje, Fecha ultimoMantenimiento){
    this->placas = placas;
    this->marca = marca;
    this->modelo = modelo;
    this->anio = anio;
    this->kilometraje = kilometraje;
    this->ultimoMantenimiento = ultimoMantenimiento;    
}

//Destructor Virtual
Vehiculo::~Vehiculo(){}

//Setter's
void Vehiculo::setPlacas(string placas){this->placas = placas;}
void Vehiculo::setKilometraje(float kilometraje){this->kilometraje = kilometraje;}
void Vehiculo::setMarca(string marca){this->marca = marca;}
void Vehiculo::setModelo(string modelo){this->modelo = modelo;}
void Vehiculo::setAnio(int anio){this->anio = anio;}


//Imprimir los Mantenimientos a los que Apunta
void Vehiculo::mostrarHistorial(){
    if(historial.size() == 0){
        cout<<getTipoVehiculo()<<" de placas "<<placas<<" aun no se le han realizado mantenimientos."<<endl;
        return;
    }

    cout<<"Registro de Mantenimientos a "<<getTipoVehiculo()<<" de placas "<<placas<<":"<<endl;
    for(auto mantenimiento : historial){
        mantenimiento->mostrarInformacion();
        cout<<endl<<endl;        
    }
}

//Mostrar Características
void Vehiculo::mostrarInformacion(){
    cout<<"Tipo De Vehiculo: "<<getTipoVehiculo()<<endl;
    cout<<"Placas: "<<placas<<endl;
    cout<<"Marca: "<<marca<<endl;
    cout<<"Modelo: "<<modelo<<endl;
    cout<<"Anio: "<<anio<<endl;
    cout<<"Kilometraje: "<<kilometraje<<endl;
    if(ultimoMantenimiento.getDia() == 0){
        cout<<"No se tiene registrado el ultimo mantenimiento."<<endl;
    }
    else{
        cout<<"Fecha del Ultimo Mantenimiento: ";
        ultimoMantenimiento.mostrarFecha();
        cout<<endl;        
    }

}

//Eliminar Mantenimiento
bool Vehiculo::eliminarMantenimiento(int id){
    if(historial.size() == 0) //Retorna un False si no hay Mantenimientos a los que apune
        return false;
    //Utlizando las utilidades de la biblioteca Vector, recorremos el historial de vehículos con iteradores
    for(auto iterador = historial.begin(); iterador != historial.end(); iterador++){
        //Si el Iterador tiene el mismo ID que se pasó como parámetro
        if((*iterador)->getId() == id){
            delete (*iterador); //Se elimina el Objeto Mantenimiento para no tener fugas de memoria
            historial.erase(iterador); //Se libera el Apuntador y el vector se reacomoda
            return true; //Retornamos True si se eliminó
        }
    }
    return false; //Falso si no se encontró el ID
}



void Vehiculo::agregarMantenimiento(Mantenimiento* mantenimiento){
    historial.push_back(mantenimiento);
    actualizarUltimoMantenimiento();
}

void Vehiculo::actualizarUltimoMantenimiento(){
    //Si no hay fechas, regresar
    if(historial.size() == 0)
        return;
    //Si solo hay una, tomamos ese valor
    if(historial.size() == 1){
        ultimoMantenimiento = historial.back()->getFecha();
        return;
    }
    //Si hay más de una, las comparamos y nos quedamos con la más reciente
    //Ejecutándose esta función, el Vehiculo deberá tener como FEcha del Ultimo mantenimiento aquella donde el mantenimiento sea más reciente
    for(auto mantenimiento : historial)
        if(mantenimiento->getFecha() > ultimoMantenimiento)
            ultimoMantenimiento = mantenimiento->getFecha();
}

//Getter's
string Vehiculo::getPlacas(){return placas;}
string Vehiculo::getMarca(){return marca;}
string Vehiculo::getModelo(){return modelo;}
float Vehiculo::getKilometraje(){return kilometraje;}
Fecha Vehiculo::getFechaUltimoMantenimiento(){return ultimoMantenimiento;}
int Vehiculo::getAnio(){return anio;}
vector<Mantenimiento*> Vehiculo::getHistorial(){return historial;}


//------------------------------------------Clase Carro ----------------------------------------------------------
//------------------------------------------Clase Hija de Vehículo ----------------------------------------------------------

class Carro : public Vehiculo{
    private:
        int cantidadPuertas;
        bool esAutomatico;
    public:
        Carro(string, string, string, int, float, Fecha, int, bool);
        string getTipoVehiculo() override; //Sobreescritura del Método abstracto Puro
        void mostrarInformacion() override; //Sobreescritura del Método Mostrar Información

        //Getter's
        int getCantidadPuertas();
        bool getEsAutomatico();

        //Setter's
        void setCantidadPuertas(int);
        void setEsAtuomatico(bool);
};

//Constructor
Carro::Carro(string placas, string marca, string modelo, int anio, float kilometraje, Fecha ultimoMantenimiento, int cantidadPuertas, bool esAutomatico) : Vehiculo(placas, marca, modelo, anio, kilometraje, ultimoMantenimiento){
    this->cantidadPuertas = cantidadPuertas;
    this->esAutomatico = esAutomatico;
}

//Setter's
void Carro::setCantidadPuertas(int cantidadPuertas){this->cantidadPuertas = cantidadPuertas;}
void Carro::setEsAtuomatico(bool esAutomatico){this->esAutomatico = esAutomatico;}

//Getter's
string Carro::getTipoVehiculo(){return "Carro";}
int Carro::getCantidadPuertas(){return cantidadPuertas;}
bool Carro::getEsAutomatico(){return esAutomatico;}

//Además de mostrar lo ya escrito de la clase Padre Vehículo
//Mostramos las características Adicionales
void Carro::mostrarInformacion(){
    cout<<"Registro del Carro: "<<endl;
    Vehiculo::mostrarInformacion();
    cout<<"cantidad de Puertas: "<<cantidadPuertas<<endl;
    cout<<"Tipo de Manejo: ";
    if(esAutomatico)
        cout<<"Automatico"<<endl;
    else
        cout<<"Manual"<<endl;
}

//------------------------------------------Clase Moto ----------------------------------------------------------
//------------------------------------------Clase Hija de Vehículo ----------------------------------------------------------
class Moto : public Vehiculo{
    private:
        string tipoMoto;
    public:
        Moto(string, string, string, int, float, Fecha, string);
        string getTipoVehiculo() override; //SObreescritura del Método Abstracto Puro
        void mostrarInformacion() override; //Sobreescritura del Método mostrar Información
        
        //Gette's
        string getTipoMoto(); 
        
        //Setter's
        void setTipoMoto(string);
};

//Constructor
Moto::Moto(string placas, string marca, string modelo, int anio, float kilometraje, Fecha ultimoMantenimiento, string tipoMoto) : Vehiculo(placas, marca, modelo, anio, kilometraje, ultimoMantenimiento){
    this->tipoMoto = tipoMoto;
}

//Setter
void Moto::setTipoMoto(string tipoMoto){this->tipoMoto = tipoMoto;}

//Getter's
string Moto::getTipoVehiculo(){return "Moto";}
string Moto::getTipoMoto(){return tipoMoto;}

//Mostrar Información Adicional
void Moto::mostrarInformacion(){
    cout<<"Registro de la Moto:"<<endl;
    Vehiculo::mostrarInformacion();
    cout<<"Tipo de Moto: "<<tipoMoto<<endl;
}

//------------------------------------------Clase Vehículo ----------------------------------------------------------
//------------------------------------------Clase Hija de Vehículo----------------------------------------------------------
class Camioneta : public Vehiculo{
    private:
        string tipoTraccion;
        bool tieneCaja;
    public:
        Camioneta(string, string, string, int, float, Fecha, string, bool);
        void mostrarInformacion() override;

        //Getter's
        string getTipoVehiculo() override;
        string getTipoTraccion();
        bool getTieneCaja();

        //Setter's
        void setTipoTraccion(string);
        void setTieneCaja(bool);
};

Camioneta::Camioneta(string placas, string marca, string modelo, int anio, float kilometraje, Fecha ultimoMantenimiento, string tipoTraccion, bool tieneCaja) : Vehiculo(placas, marca, modelo, anio, kilometraje, ultimoMantenimiento){
    this->tipoTraccion = tipoTraccion;
    this->tieneCaja = tieneCaja;
}

//Setter's
void Camioneta::setTipoTraccion(string tipoTraccion){this->tipoTraccion = tipoTraccion;}
void Camioneta::setTieneCaja(bool tieneCaja){this->tieneCaja = tieneCaja;}

//Getter's
string Camioneta::getTipoVehiculo(){return "Camioneta";}
string Camioneta::getTipoTraccion(){return tipoTraccion;}
bool Camioneta::getTieneCaja(){return tieneCaja;}

void Camioneta::mostrarInformacion(){
    cout<<"Registro de la Camioneta: "<<endl;
    Vehiculo::mostrarInformacion();
    cout<<"Tipo de Traccion: "<<tipoTraccion<<endl;
    if(tieneCaja)
        cout<<"Con Cajon"<<endl;
    else
        cout<<"Sin Cajon"<<endl;

}


//Setter's Mantenimiento:
void Mantenimiento::setId(int id){this->id = id;}
void Mantenimiento::setResponsable(Mecanico* responsable){this->responsable = responsable;}
void Mantenimiento::setFechaRealizacion(Fecha fechaRealizacion){this->fechaRealizacion = fechaRealizacion;}
void Mantenimiento::setDescripcion(string descripcion){this->descripcion = descripcion;}
void Mantenimiento::setCosto(float costo){this->costo = costo;}

//Constructor
Mantenimiento::Mantenimiento(int id, Vehiculo* vehiculo, Mecanico* responsable, Fecha fechaRealizacion, string descripcion, float costo){
    this-> id = id,
    this-> vehiculo = vehiculo;
    this->responsable = responsable;
    this->fechaRealizacion = fechaRealizacion;
    this->descripcion = descripcion;
    this->costo = costo;
}

//Destructor Vitual para aprovechas el Polimorfismo Dinámico
Mantenimiento::~Mantenimiento(){}

//Mostrar Información Relevante
void Mantenimiento::mostrarInformacion(){
    cout<<"Detalles del Mantenimineto con id "<<id<<endl;
    cout<<getTipo()<<endl;
    cout<<"Informacion del Vehiculo------------------------------"<<endl;
    cout<<vehiculo->getTipoVehiculo()<<" de placas "<<vehiculo->getPlacas()<<endl;

    cout<<"Responsable del Mantenimiento Mecanico: "<<responsable->getNombre()<<endl;
    cout<<"Fecha de Realizacion: "<<fechaRealizacion.getDia()<<"/"<<fechaRealizacion.getMes()<<"/"<<fechaRealizacion.getAnio()<<endl;
    cout<<"Descripcion del Proceso: "<<endl<<descripcion<<endl;
    cout<<"Costo Total: "<<costo<<endl;
}

//Getter's
int Mantenimiento::getId(){return id;}
Fecha Mantenimiento::getFecha(){return fechaRealizacion;}
Vehiculo* Mantenimiento::getVehiculo(){return vehiculo;}
Mecanico* Mantenimiento::getResponsable(){return responsable;}
string Mantenimiento::getDescripcion(){return descripcion;}
float Mantenimiento::getCosto(){return costo;}


//------------------------------------------Clase Mantenimiento Preventivo ----------------------------------------------------------
//------------------------------------------Clase Hija de Mantenimiento ----------------------------------------------------------
class MantenimientoPreventivo : public Mantenimiento{
    private:
        vector<string> tareasProgramadas; //Vector String para las Tareas Programadas
        float kilometrajeObjetivo;
        bool realizadoATiempo;
    public:
        MantenimientoPreventivo(int, Vehiculo*, Mecanico*, Fecha, string, float, float, bool); //Constructor *No Inicializa las tareas Programas*
        MantenimientoPreventivo(int, Vehiculo*, Mecanico*, Fecha, string, float, vector<string>, float, bool); //Sobreescritura del Constructor *Inicializa las Tareas Programas*
        void mostrarInformacion() override; //Sobreescritura de mostrarInformacion
        void agregarTarea(string); //Agregar Tarea al vector de Tareas Programadas
        
        //Getter's
        vector<string> getTareas();
        float getKilometrajeObjetivo();
        bool getRealizadoATiempo();
        string getTipo() override; //Sobreescritura del Método Abstracto Puro Útil para el Polimorfismo

        //Setter's
        void setKilometrajeObjetivo(float);
        void setRealizadoATiempo(bool);
};
//Constructor
MantenimientoPreventivo::MantenimientoPreventivo(int id, Vehiculo* vehiculo, Mecanico* responsable, Fecha fechaRealizacion, string descripcion, float costo, float kilometrajeObjetivo, bool realizadoATiempo) : Mantenimiento(id, vehiculo, responsable, fechaRealizacion, descripcion, costo){
    this->kilometrajeObjetivo = kilometrajeObjetivo;
    this->realizadoATiempo = realizadoATiempo;
}

//Sobreescritura del Constructor
MantenimientoPreventivo::MantenimientoPreventivo(int id, Vehiculo* vehiculo, Mecanico* responsable, Fecha fechaRealizacion, string descripcion, float costo, vector<string> tareasProgramadas, float kilometrajeObjetivo, bool realizadoATiempo) : Mantenimiento(id, vehiculo, responsable, fechaRealizacion, descripcion, costo){
    this->tareasProgramadas = tareasProgramadas;
    this->kilometrajeObjetivo = kilometrajeObjetivo;
    this->realizadoATiempo = realizadoATiempo;
}

//Setter's
void MantenimientoPreventivo::setKilometrajeObjetivo(float kilometrajeObjetivo){this->kilometrajeObjetivo = kilometrajeObjetivo;}
void MantenimientoPreventivo::setRealizadoATiempo(bool realizadoATiempo){this->realizadoATiempo = realizadoATiempo;}

void MantenimientoPreventivo::mostrarInformacion(){
    Mantenimiento::mostrarInformacion();
    if(tareasProgramadas.size() != 0){
        cout<<"Tareas Programadas para el Mantenimiento Preventivo: "<<endl;
        for(size_t i = 0; i < tareasProgramadas.size(); i++)
            cout<<i+1<<". "<<tareasProgramadas[i]<<endl;
    }
    cout<<"El proximo mantenimiento preventivo se recomienda al proximo kilometraje: "<<kilometrajeObjetivo<<endl;
    
    if(realizadoATiempo)
        cout<<"El mantenimiento fue realizado a tiempo recomendado.";
    else
        cout<<"El mantenimiento fue realizado despues del tiempo recomendado.";
}

//Getter's
string MantenimientoPreventivo::getTipo(){return "Mantenimiento Preventivo";}
void MantenimientoPreventivo::agregarTarea(const string tarea){tareasProgramadas.push_back(tarea);}
vector<string> MantenimientoPreventivo::getTareas(){return tareasProgramadas;}
float MantenimientoPreventivo::getKilometrajeObjetivo(){return kilometrajeObjetivo;}
bool MantenimientoPreventivo::getRealizadoATiempo(){return realizadoATiempo;}


//------------------------------------------Clase Mantenimiento Correctivo ----------------------------------------------------------
//------------------------------------------Clase Hija de Mantenimiento ----------------------------------------------------------
class MantenimientoCorrectivo : public Mantenimiento{
    private:
        string componenteAveriado;
        string causaFalla;
        bool requirioReemplazo;
    public:
        MantenimientoCorrectivo(int, Vehiculo*, Mecanico*, Fecha, string, float, string, string, bool);
        void mostrarInformacion() override; //Sobreescritura de mostrarInformacion
        
        //Getter's
        string getComponenteAveriado();
        string getCausaFalla();
        bool getRequirioReemplazo();
        string getTipo() override; //Sobreescritura del Método Abstracto Puro

        //Setter's
        void setComponenteAveriado(string);
        void setCausaFalla(string);
        void setRequirioReemplazo(bool);

};

//Setter's
void MantenimientoCorrectivo::setComponenteAveriado(string componenteAveriado){this->componenteAveriado = componenteAveriado;}
void MantenimientoCorrectivo::setCausaFalla(string causaFalla){this->causaFalla = causaFalla;}
void MantenimientoCorrectivo::setRequirioReemplazo(bool requirioReemplazo){this->requirioReemplazo = requirioReemplazo;}

//Constructor
MantenimientoCorrectivo::MantenimientoCorrectivo(int id, Vehiculo* vehiculo, Mecanico* responsable, Fecha fechaRealizacion, string descripcion, float costo, string componenteAveriado, string causaFalla, bool requirioReemplazo) : Mantenimiento(id, vehiculo, responsable, fechaRealizacion, descripcion, costo){
    this->componenteAveriado = componenteAveriado;
    this->causaFalla = causaFalla;
    this->requirioReemplazo = requirioReemplazo;
}

void MantenimientoCorrectivo::mostrarInformacion(){
    Mantenimiento::mostrarInformacion();
    cout<<"Componente Averiado: "<<componenteAveriado<<endl;
    cout<<"Causa Detectada de la Falla: "<<causaFalla<<endl;

    if(requirioReemplazo)
        cout<<"El mantenimiento requirio de un reemplazo de pieza."<<endl;
    else
        cout<<"No se requirio de un reemplazo de pieza."<<endl;
}

//Getter's
string MantenimientoCorrectivo::getTipo(){return "Mantenimiento Correctivo";}
string MantenimientoCorrectivo::getComponenteAveriado(){return componenteAveriado;}
string MantenimientoCorrectivo::getCausaFalla(){return causaFalla;}
bool MantenimientoCorrectivo::getRequirioReemplazo(){return requirioReemplazo;}

//------------------------------------------Clase Gestor Usuarios CSV ----------------------------------------------------------
/*
Esta Clase es Encargada de Manejar la Lógica del Almacenamiento de los Usuarios en formato CSV bajo el Archivo Usuarios.csv
*/
class GestorUsuariosCSV{
    private:
        string nombreArchivo = "Usuarios.csv"; //Nombre General del Archivo
    public:
        bool guardar(vector<Usuario*>);
        vector<Usuario*> cargar();
};

//Guarda un Vector de Apuntadores a Usuarios en el Archivo CSV
//Cabe destacar que sobreescribe el mismo archivo, evitando duplicaciones 
bool GestorUsuariosCSV::guardar(vector<Usuario*> registro){
    ofstream archivo(nombreArchivo); //Abrir el archivo con el nombre dado

    //Verificar que el archivo se abrio correctamente
    if(!archivo.is_open())
        return false;
    //Encabezados
    archivo<<"TipoDeUsuario,NombreUsuario,ContraseñaEncriptada,Nombre,Edad\n";

    //Recorremos el vector almacenando los datos correspondientes.
    //Utilizamos los Getter's determinados, de esta manera, conservamos el encapsulamiento
    for(auto usuario: registro){
        archivo<<usuario->getTipoUsuario()<<",";
        archivo<<usuario->getNombreUsuario()<<",";
        archivo<<usuario->getContrasena()<<",";
        archivo<<usuario->getNombre()<<",";
        archivo<<usuario->getEdad()<<",";
        archivo<<"\n";
    }
    archivo.close(); //Una vez recorrido el vector, cerramos el archivo
    return true; //Retornamos True si se guardaron correctamente..
}

//Funcion que Carga los Archivos.
//Dado un Archivo CSV de Usuarios, retorna un vector de Apuntadores a Usuarios
vector<Usuario*> GestorUsuariosCSV::cargar(){
    vector<Usuario*> registro; 
    ifstream archivo(nombreArchivo);

    if(!archivo.is_open())
        return registro;
    
    string linea;
    getline(archivo,linea); //Se salta el encabezado

    //Recorremos línea por línea, almacenando hasta la coma los strigs
    while(getline(archivo,linea)){
        stringstream ss(linea);
        string tipoUsuario, nombreUsuario, contrasenaEncriptada, nombre, edadStr;

        getline(ss,tipoUsuario,',');
        getline(ss,nombreUsuario,',');
        getline(ss,contrasenaEncriptada,',');
        getline(ss,nombre,',');
        getline(ss,edadStr,',');
        //Convertimos el string de edad a un int
        int edad = stoi(edadStr);

        //Dependiendo del Tipo de Usuario, creamos un objeto u otro
        if(tipoUsuario == "Administrador")
            registro.push_back(new Administrador(nombreUsuario, contrasenaEncriptada, nombre, edad));

        else if(tipoUsuario == "Mecanico")
            registro.push_back(new Mecanico(nombreUsuario, contrasenaEncriptada, nombre, edad));
    }     
    //Una vez cargados todos los registros, cerramos el archivo
    archivo.close();
    return registro; //Retornamos el Vector con los apuntadores
}
//------------------------------------------Clase Gestor Vehiculos CSV ----------------------------------------------------------
//Comportamiento y Lógica Similar a los gestores CSV
class GestorVehiculosCSV{
    private:
        string nombreArchivo = "Vehiculos.csv";
    public:
        bool guardar(vector<Vehiculo*>);
        vector<Vehiculo*> cargar();
};

bool GestorVehiculosCSV::guardar(vector<Vehiculo*> registro){
    ofstream archivo(nombreArchivo);

    if(!archivo.is_open())
        return false;
    
    archivo<<"TipoVehiculo,Placas,Marca,Modelo,Anio,Kilometraje,DiaUltMan,MesUltMan,AnioUltMan,Extra1,Extra2\n";

    for(auto vehiculo : registro){
        archivo<<vehiculo->getTipoVehiculo()<<",";
        archivo<<vehiculo->getPlacas()<<",";
        archivo<<vehiculo->getMarca()<<",";
        archivo<<vehiculo->getModelo()<<",";
        archivo<<vehiculo->getAnio()<<",";
        archivo<<vehiculo->getKilometraje()<<",";
        archivo<<vehiculo->getFechaUltimoMantenimiento().getDia()<<",";
        archivo<<vehiculo->getFechaUltimoMantenimiento().getMes()<<",";
        archivo<<vehiculo->getFechaUltimoMantenimiento().getAnio();

        if(vehiculo->getTipoVehiculo() == "Carro"){
            Carro* carro = dynamic_cast<Carro*>(vehiculo);
            archivo<<","<<carro->getCantidadPuertas();
            archivo<<","<<carro->getEsAutomatico();
        }
        else if(vehiculo->getTipoVehiculo() == "Camioneta"){
            Camioneta* camioneta = dynamic_cast<Camioneta*>(vehiculo);
            archivo<<","<<camioneta->getTipoTraccion();
            archivo<<","<<camioneta->getTieneCaja();
        }
        else if(vehiculo->getTipoVehiculo() == "Moto"){
            Moto* moto = dynamic_cast<Moto*>(vehiculo);
            archivo<<","<<moto->getTipoMoto();
            archivo<<",-";
        }
        archivo<<"\n";
    }
    archivo.close();
    return true;
}

vector<Vehiculo*> GestorVehiculosCSV::cargar(){
    vector<Vehiculo*> registro;
    ifstream archivo(nombreArchivo);

    if(!archivo.is_open())
        return registro;

    string linea;
    getline(archivo,linea); //Se salta el encabezado

    while(getline(archivo,linea)){
        stringstream ss(linea);
        string tipo, marca, placas, modelo, anioStr, KmStr;
        string diaStr, mesStr, anioUltStr, extra1, extra2;

        getline(ss,tipo,',');
        getline(ss,placas,',');
        getline(ss,marca,',');
        getline(ss,modelo,',');
        getline(ss,anioStr,',');
        getline(ss,KmStr,',');
        getline(ss,diaStr,',');
        getline(ss,mesStr,',');
        getline(ss,anioUltStr,',');
        getline(ss,extra1,',');
        getline(ss,extra2,',');

        int anio = stoi(anioStr);
        float km = stof(KmStr);
        int dia = stoi(diaStr);
        int mes = stoi(mesStr);
        int anioUlt = stoi(anioUltStr);
        Fecha fecha(dia,mes,anioUlt);

        if(tipo == "Carro"){
            int puertas = stoi(extra1);
            bool automatico = (extra2 == "1");
            registro.push_back(new Carro(placas, marca, modelo, anio, km, fecha, puertas, automatico));
        }
        else if(tipo == "Camioneta"){
            bool caja = (extra2 == "1");
            registro.push_back(new Camioneta(placas, marca, modelo, anio, km, fecha, extra1, caja));
        }
        else if(tipo == "Moto"){
            registro.push_back(new Moto(placas, marca, modelo, anio, km, fecha, extra1));
        }
    }
    archivo.close();
    return registro;
}

//------------------------------------------Clase GIVAM ----------------------------------------------------------
/*
GIVAM es la base de datos central, es el cerebro, quien se encarga de administrar y coordinar las demás clases para que su funcionamiento sea adecaudo
Al igual que el resto de clases, tiene funciones específicas que cumplen con objetivos especificos, por lo que directamente no purga los datos que se le pasan
(verificar que sean correctos antes de trabajarlos), esto lo harán los Menús.
*/
class GIVAM{
    private:
        //Vectores de Apuntadores, de esta manera, aprovechamos el Polimorfismo Dinámico en Múltiples Ocasiones.
        vector<Usuario*> usuarios; 
        vector<Vehiculo*> vehiculos;
        vector<Mantenimiento*> historialMantenimiento;

        //Funciones de Almacenamiento para Guardar los Registros
        void guardarUsuarios();
        void guardarVehiculos();
        void guardarHistorial();

        void limpiarMantenimientosDeMecanico(Mecanico*);
    public:
        GIVAM();
        ~GIVAM();

        //Agregadores: 
            //Agregar Elmentos Principales
        bool agregarUsuario(string,string,string,string, int);
        bool agregarVehiculo(string,string, string, string, int, float, Fecha,int, string, bool);
        bool agregarMantenimiento(string,string, int, Vehiculo*, Mecanico*, Fecha, float, float, bool, string, string);
        bool agregarMantenimiento(string, string, int, string, string, Fecha, float, float, bool, string, string);
            //Agregar Elementos Secundarios
        void agregarTareaMantenimientoPreventivo(MantenimientoPreventivo*,string);
        bool agregarTareaMantenimientoPreventivo(int,string);            

        //Eliminadores:
        bool eliminarUsuario(string);   
        bool eliminarVehiculo(string);
        bool eliminarMantenimineto(int);

        //Buscadores
        Usuario* buscarUsuario(string);
        Vehiculo* buscarVehiculo(string);
        Mantenimiento* buscarMantenimiento(int);
        
        //Editores
        void editarUsuario(Usuario*, string, string, int);
        void editarVehiculo(Vehiculo*, string, string, int, float, bool);
        void editarMantenimiento(Mantenimiento*, string, string, int, float, bool, Fecha, Mecanico*);
        

        //Mostradores
        void mostrarUsuarios() const;
        void mostrarVehiculos() const;

        //Getter's
            //Obtener el Número de los Registros
        int getNumeroVehiculos();
        int getNumeroMantenimientos();
        int getNumeroUsuarios();
            //Getter's de los Apuntadores
        vector<Usuario*> getUsuariosEnteros();

        //Métodos Útiles Varios
        bool iniciarSesion(string,string);
        vector<Mantenimiento*> adjuntarMantenimientosPorFecha(Fecha,Fecha);
        void ordenarMantenimientosPorFecha();
        void cargarRegistros();

};

//Constructor
GIVAM::GIVAM(){}
//Destructor.
//Libera de la memoria todos los objetos creados
GIVAM::~GIVAM(){
    for(auto usuario: usuarios){delete usuario;}
    for(auto vehiculo : vehiculos){delete vehiculo;}
    for(auto mantenimiento: historialMantenimiento){delete mantenimiento;}
}

//Agregadores:
/*
Los Agregadores en GIVAM siguen la metodología Factory
Esto es que existen funciones que solo con su paso de parámetros crean objetos diferentes según los parámetros que se le pasen
Esto agiliza mucho el mantenimiento del código y el agregar nuevos tipos de usuarios, Vehículos y Mantenimientos
*/
    //Agregar Elementos Principales:
    bool GIVAM::agregarUsuario(string tipo, string nombreUsuario, string contrasenaEncriptada, string nombre, int edad){
        contrasenaEncriptada = GestorSeguridad::generarHash(contrasenaEncriptada);
        if(buscarUsuario(nombreUsuario))
            return false;
        else if(tipo == "Administrador")
                usuarios.push_back(new Administrador(nombreUsuario, contrasenaEncriptada, nombre, edad));
        else if(tipo == "Mecanico")
                usuarios.push_back(new Mecanico(nombreUsuario, contrasenaEncriptada, nombre, edad));
        guardarUsuarios();
        return true;
}

bool GIVAM::agregarMantenimiento(string tipoMantenimiento, string descripcion, int id, Vehiculo* vehiculo, Mecanico* responsable, Fecha fechaRealizacion, float costo, float especificoFloat, bool especificoBool, string especificoString1, string especificoString2){
    if(buscarMantenimiento(id))
        return false;
    else if(tipoMantenimiento == "Mantenimiento Preventivo")
        historialMantenimiento.push_back(new MantenimientoPreventivo(id, vehiculo, responsable, fechaRealizacion, descripcion, costo, especificoFloat, especificoBool));
    else if(tipoMantenimiento == "Mantenimiento Correctivo")
        historialMantenimiento.push_back(new MantenimientoCorrectivo(id, vehiculo, responsable, fechaRealizacion, descripcion, costo, especificoString1, especificoString2, especificoBool));
    
    vehiculo->agregarMantenimiento(historialMantenimiento.back());
    ordenarMantenimientosPorFecha();
    guardarHistorial();
    guardarVehiculos();
    return true;
}

bool GIVAM::agregarVehiculo(string tipoVehiculo, string placas, string marca, string modelo, int anio, float kilometraje, Fecha ultimoMantenimiento, int especificoInt, string especificoString, bool especificoBool){
    if(buscarVehiculo(placas))
        return false;
    else if(tipoVehiculo == "Carro")
        vehiculos.push_back(new Carro(placas, marca, modelo, anio, kilometraje,ultimoMantenimiento,especificoInt, especificoBool));
    else if(tipoVehiculo == "Camioneta")
        vehiculos.push_back(new Camioneta(placas, marca, modelo, anio, kilometraje, ultimoMantenimiento, especificoString, especificoBool));
    else if(tipoVehiculo == "Moto")
        vehiculos.push_back(new Moto(placas, marca, modelo, anio, kilometraje, ultimoMantenimiento, especificoString));
    
    guardarVehiculos();
    return true;
}

void GIVAM::agregarTareaMantenimientoPreventivo(MantenimientoPreventivo* mantenimiento, string tarea){
    mantenimiento->agregarTarea(tarea);
    cout<<"Tarea Agregada";
    guardarHistorial();
    cout<<"Tarea Guardada";
}

bool GIVAM::agregarTareaMantenimientoPreventivo(int id, string tarea){
    MantenimientoPreventivo* mantenimientoPreventivo = dynamic_cast<MantenimientoPreventivo*>(buscarMantenimiento(id));
    if(mantenimientoPreventivo){
        mantenimientoPreventivo->agregarTarea(tarea);
        guardarHistorial();   
        return true;     
    }
    //O el Mantenimiento no Existe o no es Preventivo.
    return false;
}

//Eliminadores:
bool GIVAM::eliminarUsuario(const string nombreDeUsuario){
    for(auto iterador = usuarios.begin(); iterador != usuarios.end(); iterador++){
        if((*iterador)->getNombreUsuario() == nombreDeUsuario){
            if((*iterador)->getTipoUsuario() == "Mecanico")
                limpiarMantenimientosDeMecanico(dynamic_cast<Mecanico*>(*iterador)); //Si es Mecánico, se eliminan todos los mantenimiengos que haya hecho
            delete (*iterador);
            usuarios.erase(iterador);
            guardarUsuarios();
            return true;
        }
    }
    return false;
}

bool GIVAM::eliminarVehiculo(const string placas){
    for(auto iterador = vehiculos.begin(); iterador != vehiculos.end(); iterador++){
        if((*iterador)->getPlacas() == placas){
            //Eliminar Sus Mantenimientos:
            if((*iterador)->getHistorial().size() != 0)
                for(auto mantenimiento : (*iterador)->getHistorial())
                    eliminarMantenimineto(mantenimiento->getId());

            //Eliminar Objeto de Apuntado
            delete (*iterador);
            vehiculos.erase(iterador); //Liberar Apuntador
            guardarVehiculos(); 
            return true;
        }
    }
    return false;
}

bool GIVAM::eliminarMantenimineto(const int id){
    for(auto iterador = historialMantenimiento.begin();  iterador != historialMantenimiento.end(); iterador++){
        if((*iterador)->getId() == id){
            (*iterador)->getVehiculo()->eliminarMantenimiento(id);           
            historialMantenimiento.erase(iterador);
            guardarHistorial();
            return true;
        }
    }
    return false;
}

//Buscadores
Usuario* GIVAM::buscarUsuario(const string nombreDeUsuario){
    for(Usuario* usuario : usuarios)
        if(usuario->getNombreUsuario() == nombreDeUsuario)
            return usuario;
    return nullptr;
}

Vehiculo* GIVAM::buscarVehiculo(const string placas){
    for(Vehiculo* vehiculo : vehiculos)
        if(vehiculo->getPlacas() == placas)
            return vehiculo;
    return nullptr;
}

Mantenimiento* GIVAM::buscarMantenimiento(int id){
    for(Mantenimiento* mantenimiento : historialMantenimiento)
        if(mantenimiento->getId() == id)
            return mantenimiento;
    return nullptr;
}

//Editores
void GIVAM::editarUsuario(Usuario* usuario, string edicion, string especificoString, int especificoInt){
    if(edicion == "Nombre de Usuario")
        usuario->setNombreUsuario(especificoString);
    else if(edicion == "Contrasena")
        usuario->setContrasena(GestorSeguridad::generarHash(especificoString));
    else if(edicion == "Nombre")
        usuario->setNombre(especificoString);
    else if(edicion == "Edad")
        usuario->setEdad(especificoInt);
    guardarUsuarios();
    guardarHistorial();
}

void GIVAM::editarMantenimiento(Mantenimiento* mantenimiento, string editor, string especificoString, int especificoInt, float especificoFloat, bool especificoBool, Fecha especificoFecha, Mecanico* mecanico){
    if(editor == "Id")
        mantenimiento->setId(especificoInt);
    else if(editor == "Responsable")
        mantenimiento->setResponsable(mecanico);
    else if(editor == "Fecha Realizacion"){
        mantenimiento->setFechaRealizacion(especificoFecha);
        ordenarMantenimientosPorFecha();
    }
    else if(editor == "Descripcion")
        mantenimiento->setDescripcion(especificoString);
    else if(editor == "Costo")
        mantenimiento->setCosto(especificoFloat);
    else if(editor == "Kilometraje Objetivo")
        dynamic_cast<MantenimientoPreventivo*>(mantenimiento)->setKilometrajeObjetivo(especificoFloat);
    else if(editor == "Realizado a Tiempo")
        dynamic_cast<MantenimientoPreventivo*>(mantenimiento)->setRealizadoATiempo(especificoBool);
    else if(editor == "Componente Averiado")
        dynamic_cast<MantenimientoCorrectivo*>(mantenimiento)->setComponenteAveriado(especificoString);
    else if(editor == "Causa Falla")
        dynamic_cast<MantenimientoCorrectivo*>(mantenimiento)->setCausaFalla(especificoString);
    else if(editor == "Requirio Reemplazo")
        dynamic_cast<MantenimientoCorrectivo*>(mantenimiento)->setRequirioReemplazo(especificoBool);
    
    guardarHistorial();
    guardarVehiculos();
}

void GIVAM::editarVehiculo(Vehiculo* vehiculo, string edicion, string especificoString1, int especificoInt, float especificoFloat, bool especificoBool){
    if(edicion == "Placas")
        vehiculo->setPlacas(especificoString1);
    else if(edicion == "Marca")
        vehiculo->setMarca(especificoString1);
    else if(edicion == "Modelo")
        vehiculo->setModelo(especificoString1);
    else if(edicion == "Anio")
        vehiculo->setAnio(especificoInt);
    else if(edicion == "Kilometraje")
        vehiculo->setKilometraje(especificoFloat);
    else if(edicion == "Cantidad Puertas")
        dynamic_cast<Carro*>(vehiculo)->setCantidadPuertas(especificoInt);
    else if(edicion == "Es Automatico")
        dynamic_cast<Carro*>(vehiculo)->setEsAtuomatico(especificoBool);
    else if(edicion == "Tipo Moto")
        dynamic_cast<Moto*>(vehiculo)->setTipoMoto(especificoString1);
    else if(edicion == "Tipo Traccion")
        dynamic_cast<Camioneta*>(vehiculo)->setTipoTraccion(especificoString1);
    else if(edicion == "Tiene Caja")
        dynamic_cast<Camioneta*>(vehiculo)->setTieneCaja(especificoBool);

    guardarVehiculos();
    guardarHistorial();
}

//Mostradores
void GIVAM::mostrarUsuarios() const{
    for(Usuario* usuario : usuarios){
        usuario->mostrarInformacion();
        cout<<"------------------------------------------------------------------------------"<<endl;
    }
    cout<<endl;
    cout<<"Total de Usuarios Registrados: "<<usuarios.size()<<endl;
}

void GIVAM::mostrarVehiculos() const{
    for(Vehiculo* vehiculo : vehiculos){
        vehiculo->mostrarInformacion();
        cout<<endl<<".................................."<<endl<<endl;
    }
    cout<<endl<<endl<<"Un total de: "<<vehiculos.size()<<" vehiculos registrados."<<endl;
}

//Getter's
    //Getter's de Números de Mantenimientos

int GIVAM::getNumeroMantenimientos(){return historialMantenimiento.size();}
int GIVAM::getNumeroVehiculos(){return vehiculos.size();}
int GIVAM::getNumeroUsuarios(){return usuarios.size();}
    //Getter's de Apuntadores:
vector<Usuario*> GIVAM::getUsuariosEnteros(){return usuarios;}

//Métodos Útiles Varios
void GIVAM::limpiarMantenimientosDeMecanico(Mecanico* mecanico){
    /*
    Se Itera Aquí sobre una copia dado que entre las funciones que eliminan los Mantenimientos
    Alteran el Vector de historialMantenimiento que es el que trabajamos aquí.
    Si se modifica antes de que este bucle acabe propicia comportamiento impredescible, por lo que esta copia
    solo rescata la información de los punteros relevante.
    */
    vector<Mantenimiento*> copia = historialMantenimiento;
    for(auto mantenimiento : copia){
        cout<<mantenimiento->getResponsable()->getNombreUsuario()<<endl;
        if(mantenimiento->getResponsable()->getNombreUsuario() == mecanico->getNombreUsuario()){
            eliminarMantenimineto(mantenimiento->getId());   
        }
    }
}

vector<Mantenimiento*> GIVAM::adjuntarMantenimientosPorFecha(Fecha fechaMenor, Fecha fechaMayor){
    vector<Mantenimiento*> registro;
    for(auto mantenimiento : historialMantenimiento)
        if(mantenimiento->getFecha() >= fechaMenor && mantenimiento->getFecha() <= fechaMayor)
            registro.push_back(mantenimiento);

    return registro;
}


bool GIVAM::iniciarSesion(const string nombreUsuario, const string contrasena){
    Usuario* registro = buscarUsuario(nombreUsuario);
    if(registro != nullptr && GestorSeguridad::verificarHash(contrasena, registro->getContrasena()))
        return true;
    return false;
}

bool GIVAM::agregarMantenimiento(string tipoMantenimiento, string descripcion, int id, string placasVehiculo, string nombreUsuarioMecanico, Fecha fechaRealizacion, float costo, float especificoFloat, bool especificoBool, string especificoString1, string especificoString2){
    if(buscarMantenimiento(id))
        return false;
    else if(tipoMantenimiento == "Mantenimiento Preventivo")
        historialMantenimiento.push_back(new MantenimientoPreventivo(id, buscarVehiculo(placasVehiculo), dynamic_cast<Mecanico*>(buscarUsuario(nombreUsuarioMecanico)), fechaRealizacion, descripcion, costo, especificoFloat, especificoBool));
    else if(tipoMantenimiento == "Mantenimiento Correctivo")
        historialMantenimiento.push_back(new MantenimientoCorrectivo(id, buscarVehiculo(placasVehiculo), dynamic_cast<Mecanico*>(buscarUsuario(nombreUsuarioMecanico)), fechaRealizacion, descripcion, costo, especificoString1, especificoString2, especificoBool));
    
    buscarVehiculo(placasVehiculo)->agregarMantenimiento(historialMantenimiento.back());
    ordenarMantenimientosPorFecha();
    guardarHistorial();    
    guardarVehiculos();
    return true;
}

void GIVAM::ordenarMantenimientosPorFecha(){
    if(historialMantenimiento.size() == 0)
        return;
    if(historialMantenimiento.size() == 1)
        return;
    
    int n = historialMantenimiento.size();
    for(int i = 0 ; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(historialMantenimiento[j]->getFecha() > historialMantenimiento[j+1]->getFecha()){
                swap(historialMantenimiento[j],historialMantenimiento[j+1]);
            }
        }
    }
    guardarHistorial();
}

class GestorMantenimientoCSV{
    private:
        string nombreArchivo = "Mantenimiento.csv";
    public:
        bool guardar(vector<Mantenimiento*>);
        vector<Mantenimiento*> cargar(GIVAM&);
        bool exportarReporteMantenimiento(vector<Mantenimiento*>, string);
};

bool GestorMantenimientoCSV::guardar(vector<Mantenimiento*> registro){
    ofstream archivo(nombreArchivo);
    if(!archivo.is_open())
        return false;

    archivo<<"TipoMantenimiento,Id,PlacasVehiculo,UsuarioMecanico,DiaRealizacion,MesRealizacion,AnioRealizacion,Descripcion,Costo,Extra1,Extra2,Extra3\n";
    for(auto mantenimiento : registro){
        archivo<<mantenimiento->getTipo()<<",";
        archivo<<mantenimiento->getId()<<",";
        archivo<<mantenimiento->getVehiculo()->getPlacas()<<",";
        archivo<<mantenimiento->getResponsable()->getNombreUsuario()<<",";
        archivo<<mantenimiento->getFecha().getDia()<<",";
        archivo<<mantenimiento->getFecha().getMes()<<",";
        archivo<<mantenimiento->getFecha().getAnio()<<",";
        archivo<<mantenimiento->getDescripcion()<<",";
        archivo<<mantenimiento->getCosto();

        if(mantenimiento->getTipo() == "Mantenimiento Preventivo"){
            MantenimientoPreventivo* mantenimientoPreventivo = dynamic_cast<MantenimientoPreventivo*>(mantenimiento);
            archivo<<",";
            if(mantenimientoPreventivo->getTareas().size() != 0){
                for(auto tarea : mantenimientoPreventivo->getTareas()){
                    archivo<<tarea;
                    if(tarea != mantenimientoPreventivo->getTareas().back())
                        archivo<<"|";
                }
            }
            archivo<<","<<mantenimientoPreventivo->getKilometrajeObjetivo();
            archivo<<","<<mantenimientoPreventivo->getRealizadoATiempo();
        }

        else if(mantenimiento->getTipo() == "Mantenimiento Correctivo"){
            MantenimientoCorrectivo* mantenimientoCorrectivo = dynamic_cast<MantenimientoCorrectivo*>(mantenimiento);
            archivo<<","<<mantenimientoCorrectivo->getComponenteAveriado();
            archivo<<","<<mantenimientoCorrectivo->getCausaFalla();
            archivo<<","<<mantenimientoCorrectivo->getRequirioReemplazo();     
        }
        archivo<<"\n";
    }
    archivo.close();
    return true;
}

vector<Mantenimiento*> GestorMantenimientoCSV::cargar(GIVAM& bd){
    ifstream archivo(nombreArchivo);
    vector<Mantenimiento*> registro;
    if(!archivo.is_open())
        return registro;

    string linea;
    getline(archivo,linea); //Saltarse los encabezados

    while(getline(archivo,linea)){
        stringstream ss(linea);
        string tipoMantenimiento, idStr, placasVehiculo, usuarioMecanico;
        string diaStr, mesStr, anioStr, descripcion, costoStr, extra1,extra2,extra3;
        vector<string> tareasProgramadas;

        getline(ss,tipoMantenimiento,',');
        getline(ss,idStr,',');
        getline(ss,placasVehiculo,',');
        getline(ss,usuarioMecanico,',');
        getline(ss,diaStr,',');
        getline(ss,mesStr,',');
        getline(ss,anioStr,',');
        getline(ss,descripcion,',');
        getline(ss,costoStr,',');
        getline(ss,extra1,',');
        getline(ss,extra2,',');
        getline(ss,extra3,',');

        //Convertirlos a sus respectivos Datos
        int id = stoi(idStr);
        int dia = stoi(diaStr);
        int mes = stoi(mesStr);
        int anio = stoi(anioStr);
        float costo = stof(costoStr);

        if(tipoMantenimiento == "Mantenimiento Preventivo"){
            stringstream ss(extra1);

            while(getline(ss,extra1,'|'))
                tareasProgramadas.push_back(extra1);
        
            float kilometrajeObjetivo = stof(extra2);
            bool realizadoATiempo = (extra3 == "1");
            registro.push_back(new MantenimientoPreventivo(id, bd.buscarVehiculo(placasVehiculo), dynamic_cast<Mecanico*>(bd.buscarUsuario(usuarioMecanico)),Fecha(dia,mes,anio),descripcion,costo,tareasProgramadas,kilometrajeObjetivo,realizadoATiempo));
        }

        else if(tipoMantenimiento == "Mantenimiento Correctivo"){
            bool requirioReemplazo = (extra3 == "1");
            registro.push_back(new MantenimientoCorrectivo(id, dynamic_cast<Vehiculo*>(bd.buscarVehiculo(placasVehiculo)), dynamic_cast<Mecanico*>(bd.buscarUsuario(usuarioMecanico)),Fecha(dia,mes,anio),descripcion,costo,extra1,extra2,requirioReemplazo));
        }

    }
    archivo.close();
    return registro;
}


bool GestorMantenimientoCSV::exportarReporteMantenimiento(vector<Mantenimiento*> registro, string titloArchivo){
    if(registro.size() == 0)
        return false;
    
    ofstream archivo(titloArchivo);
    archivo<<"Reportes de Mantenimiento."<<endl;
    archivo<<"Fecha de Consulta: "<<Fecha().getDia()<<"/"<<Fecha().getMes()<<"/"<<Fecha().getAnio();
    archivo<<" _______________________________________________________________________________\n\n";

    for(auto mantenimiento : registro){
        archivo<<"Reporte de Mantenimiento de Id "<<mantenimiento->getId()<<"  -------------------------------------------\n";
        archivo<<mantenimiento->getVehiculo()->getTipoVehiculo()<<" de placas: "<<mantenimiento->getVehiculo()->getPlacas()<<endl;
        archivo<<"Tipo de Mantenimiento: "<<mantenimiento->getTipo()<<endl;
        archivo<<"Matenimiento Realizado por el Mecanico: "<<mantenimiento->getResponsable()->getNombre()<<endl;
        archivo<<"Fecha de Realizacion: "<<mantenimiento->getFecha().getDia()<<"/"<<mantenimiento->getFecha().getMes()<<"/"<<mantenimiento->getFecha().getAnio()<<endl;
        archivo<<"Descripcion del Mantenimiento: "<<endl<<mantenimiento->getDescripcion()<<endl;
        archivo<<"Costo Total: "<<mantenimiento->getCosto()<<endl;

        if(mantenimiento->getTipo() == "Mantenimiento Preventivo"){
            MantenimientoPreventivo* mantenimientoPreventivo = dynamic_cast<MantenimientoPreventivo*>(mantenimiento);
            archivo<<"Tareas Programadas: "<<endl;
        
            for(size_t tarea = 0; tarea < mantenimientoPreventivo->getTareas().size(); tarea++)
                archivo<<"Tarea "<<tarea+1<<": "<<mantenimientoPreventivo->getTareas()[tarea]<<endl;
            
            archivo<<"kilometraje Objetivo: "<<mantenimientoPreventivo->getKilometrajeObjetivo()<<endl;
            if(mantenimientoPreventivo->getRealizadoATiempo())
                archivo<<"El Mantenimiento Preventivo se Realizo a Tiempo Recomendado"<<endl;
            else
                archivo<<"El mantenimiento Preventivo no se Realizo a Tiempo Recomendado"<<endl;
        }

        else if(mantenimiento->getTipo() == "Mantenimiento Correctivo"){
            MantenimientoCorrectivo* mantenimientoCorrectivo = dynamic_cast<MantenimientoCorrectivo*>(mantenimiento);
            archivo<<"Componente Averiado: "<<mantenimientoCorrectivo->getComponenteAveriado()<<endl;
            archivo<<"Causa Detectada de la Falla: "<<mantenimientoCorrectivo->getCausaFalla()<<endl;
            
            if(mantenimientoCorrectivo->getRequirioReemplazo())
                archivo<<"La pieza requirio de ser cambiada"<<endl;
            else
                archivo<<"La pieza no requirio ser cambiada"<<endl;

        }
        archivo<<"\n\n";
    }
    archivo<<"Total de Reportes: "<<registro.size();
    archivo<<"\n\n";
    return true;
}

void GIVAM::cargarRegistros(){
    GestorUsuariosCSV gestorUsuariosCSV;
    GestorVehiculosCSV gestorVehiculosCSV;
    GestorMantenimientoCSV gestorMantenimientoCSV;

    usuarios = gestorUsuariosCSV.cargar();
    vehiculos = gestorVehiculosCSV.cargar();
    historialMantenimiento = gestorMantenimientoCSV.cargar(*this);

    //Agregar los Apuntadores a los Vehículos
    if(historialMantenimiento.size() != 0)
        for(auto mantenimiento : historialMantenimiento)
            mantenimiento->getVehiculo()->agregarMantenimiento(mantenimiento);

}

void GIVAM::guardarUsuarios(){
    GestorUsuariosCSV gestorUsuariosCSV;
    gestorUsuariosCSV.guardar(usuarios);
}

void GIVAM::guardarVehiculos(){
    GestorVehiculosCSV gestorVehiculosCSV;
    gestorVehiculosCSV.guardar(vehiculos);
}

void GIVAM::guardarHistorial(){
    GestorMantenimientoCSV gestorMantenimiento;
    gestorMantenimiento.guardar(historialMantenimiento);
}



//------------------------------------------Clase Menú ----------------------------------------------------------
/*
Clase que se encarga de adjuntar los Menús y Submenús de las funcionalidades
Depura los Datos que se le pasan a GIVAM para que el comportamiento sea Correcto.abort
*/
class Menu{
    private: 
        GIVAM& sistema;
        Usuario* usuario;

        //Funciones Útiles Varias
            //Mensajería
        void informacionGIVAM();
        void opcionIncorrecta();
        void faltaRegistro(string);
        void accesoDenegado();
        void cantidadFueraDeRango();
        void regresandoMenuAnterior();

            //Pedir Interos y Flotantes dentro de un rango
        int limiteInt(string,int,int);
        float limiteFloat(string,float,float);
            //Pedir un identificador, puede ser uno registrado o no registrado
        Vehiculo* pedirPlacas(string);
        Mecanico* pedirMecanico(string);
        Usuario* pedirUsuario(string);
        Mantenimiento* pedirMantenimiento(string);
            //Inicial Sesión
        void iniciarSesion();

        //Menú Principal
        void menuPrincipal();
        //SubMenús
        void gestionVehiculos();
        void gestionUsuarios();
        void gestionMantenimientos();
        void gestionReportes();

        //Funcionalidades:
            //Registros:
        void registrarNuevoVehiculo();
        void registrarNuevoUsuario();
        void registrarNuevoMantenimiento();
            //Eliminadores:
        void eliminarVehiculo();
        void eliminarMantenimineto();
        void eliminarUsuario();
            //Editores
        void editarUsuario();
        void editarVehiculo();
        void editarMantenimiento();
            //Buscadores:
        void buscarUsuario();
        void buscarVehiculo();
        void buscarMantenimientoPorId();
            //Mostradores:
        void mostrarTodoRegistroVehiculos();
        void mostrarTodoRegistroUsuarios();   
        void consultarHistorialPorVehiculo();     

            //Generadores de Reportes:
        void generarReporteUnico();
        void generarReportesEntreFechas();
        void generarReporteDeVehiculo();

    public:
        Menu(GIVAM&); //Constructor
        Menu(GIVAM&,Usuario*); //Sobreescritura del Constructor, Mucha Utilidad para el Desarrollar y Pruebas del Programa
        void login(); //La única función pública, desde esta se puede acceder a todas las demás
};

//Constructores
Menu::Menu(GIVAM& sistema) : sistema(sistema){
    this->sistema = sistema;
    usuario = nullptr;
}

Menu::Menu(GIVAM& sistema, Usuario* usuario) : sistema(sistema){
    this->sistema = sistema;
    this->usuario = usuario;
}

//Funciones Útiles Varias
    //Mensajería
void Menu::opcionIncorrecta(){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"La opcion que ha ingresado no Corresponde a ninguna de las opciones propuestas."<<endl;
    cout<<"Por favor, vuelva a intentarlo.\n";
    cout<<"-----------------------------------------------------------"<<endl<<endl;
    system("PAUSE");
}

void Menu::cantidadFueraDeRango(){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"La cantidad ingresada esta fuera de rango."<<endl;
    cout<<"Por favor, vuelva a intentarlo.\n";
    cout<<"-----------------------------------------------------------"<<endl<<endl;
    system("PAUSE");    
}

void Menu::accesoDenegado(){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"El tipo de usuario "<<usuario->getTipoUsuario()<<" no tiene privilegios para esta funcion"<<endl;
    cout<<"Por favor, seleccione otra funcionalidad o inicie sesion con otros privilegios.\n";
    cout<<"-----------------------------------------------------------"<<endl<<endl;
    system("PAUSE");
}

void Menu::regresandoMenuAnterior(){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Regresando al Menu Anterior"<<endl;
    cout<<"-----------------------------------------------------------"<<endl<<endl;
    system("PAUSE");    
}

void Menu::faltaRegistro(string registro){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Aun no Hay "<<registro<<" Registrados en GIVAM."<<endl;
    cout<<"Por favor, ingrese "<<registro<<" antes de Acceder a esta Opcion"<<endl;
    cout<<"-----------------------------------------------------------"<<endl<<endl;
    system("PAUSE");  
}

void Menu::informacionGIVAM(){
    system("CLS");
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"GIVAM"<<endl;
    cout<<"Gestor Inteligente de Vehiculos y Administracion de Mantenimiento"<<endl;
    cout<<"GIVAM es un gestor para taller mecanico en el cual puedes llevar el control sobre los vehiculos y los mantenimientos que estos reciben a lo largo del tiempo."<<endl;
    cout<<"GIVAM guarda la informacion de los Usuarios divididos en Administradores y Mecanicos"<<endl<<endl;
    cout<<"Los administradores tienen control sobre la eliminacion de vehiculos y mantenimientos."<<endl;
    cout<<"Los mecanicos tienen controles mas limitados sobre el sistema."<<endl<<endl;
    cout<<"GIVAM guarda diversa informacion en archivos CSV, separados por comas."<<endl;
    cout<<"Para llevar los registros estan: Mantenimientos.csv, Usuarios.csv, Vehiculos.csv"<<endl;
    cout<<"Los Archivos CSV tienen la ventaja de que pueden ser editados con facilidades en programas como Excel, lo que le da un mayor control sobre los datos"<<endl;
    cout<<"Para el registro de los Usuarios, la contrasena se guarda encriptada, por lo que el que tenga acceso a los archivos no podra conocer la contrasena"<<endl;
    cout<<"GIVAM carga y maneja automaticamente estos registros, ademas de poder generar en archivos de texto, reportes de los mantenimientos registrados"<<endl;
    cout<<endl<<"Espero que GIVAM sea de utilidad para su empresa :)"<<endl<<endl;
    cout<<"Producto Integrados de Programacion Orientada a Objetos"<<endl;
    cout<<"Desarrollador: Mariscal Rodriguez Omar Jesus"<<endl;
    cout<<"Version de GIVAM: 1.0"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    system("PAUSE");

}

//Pedir Enteros y Flotantes dentro de un límite
int Menu::limiteInt(string consulta,int limiteInferior, int limiteSuperior){
    int cantidad;
    do{
        cout<<consulta;
        cin>>cantidad;
        if(cantidad > limiteSuperior || cantidad < limiteInferior){
            cantidadFueraDeRango();
            system("CLS");

        }   
    }while(cantidad < limiteInferior || cantidad > limiteSuperior);
    
    return cantidad; 
}


float Menu::limiteFloat(string consulta, float limiteInferior, float limiteSuperior){
    float cantidad;
    do{
        cout<<consulta;
        cin>>cantidad;
        if(cantidad > limiteSuperior || cantidad < limiteInferior){
            cantidadFueraDeRango();
            system("CLS");
        }
    }while(cantidad < limiteInferior || cantidad > limiteSuperior);
    
    return cantidad; 
}
//Iniciar Sesión
void Menu::iniciarSesion(){
    string nombreUsuario,contrasena;

    if(sistema.getNumeroUsuarios() == 0){
        system("CLS");
        cout<<"No hay Usuarios, Registrados."<<endl;
        cout<<"Accediendo al Registro..."<<endl;
        system("PAUSE");
        registrarNuevoUsuario();
    }
    do{
        system("CLS");
        cout<<"Para Regresar al Menu Anterior Ingrese -1"<<endl;    
        cout<<"Ingrese su nombre de Usuario: ";
        getline(cin>>ws,nombreUsuario);

        if(nombreUsuario == "-1"){
            regresandoMenuAnterior();
            return;
        }

        cout<<"Ingrese su contrasena: ";
        getline(cin>>ws,contrasena);
        cout<<endl;

        

        if(sistema.iniciarSesion(nombreUsuario, contrasena)){
            usuario = sistema.buscarUsuario(nombreUsuario);
            cout<<"Sesion Iniciada Correctamente!"<<endl;
            cout<<"Bienvenido "<<usuario->getTipoUsuario()<<" "<<usuario->getNombre()<<endl;
            cout<<"Ingresando al Sistema"<<endl;
            system("PAUSE");
        }
        else{
            system("CLS");
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"Usuario y/o contrasena incorrecta."<<endl;
            cout<<"Por favor, intente nuevamente"<<endl;
            cout<<"-----------------------------------------------------------"<<endl;
            system("PAUSE");
        }
    }while(usuario == nullptr);
}

//Pedir Identificadores

Vehiculo* Menu::pedirPlacas(string tipo){
    Vehiculo* respuesta;
    string placas;
    if(tipo == "No Registrado"){
        do{
            cout<<"Ingrese Placas No Registradas en el Sistema: ";
            getline(cin >> ws, placas);

            respuesta = sistema.buscarVehiculo(placas);

            if(respuesta){
                cout<<"\nEstas Placas ya estan registradas en el sistema"<<endl;
                cout<<"Las posee el siguiente registro: "<<endl;
                respuesta->mostrarInformacion();
                cout<<"\n\nPor favor, ingrese unas placas distintas."<<endl;
            }
        }while(respuesta); 
    }

    if(tipo == "Registrado"){
        do{
            cout<<"Ingrese las Placas del Vehiculo: ";
            getline(cin >> ws, placas);

            respuesta = sistema.buscarVehiculo(placas);

            if(!respuesta){
                cout<<"\nNo existe un Vehiculo en el Sistema con las placas "<<placas<<endl;
                cout<<"Por favor, vuelva a intentarlo\n"<<endl;
            }
        }while(!respuesta);
    }
    return respuesta;
}

Mecanico* Menu::pedirMecanico(string tipo){
    Mecanico* respuesta;
    string nombreUsuario;
    if(tipo == "No Registrado"){
        do{
            cout<<"Ingrese el Nombre del Mecanico No Registrado: ";
            getline(cin >> ws, nombreUsuario);

            respuesta = dynamic_cast<Mecanico*>(sistema.buscarUsuario(nombreUsuario));

            if(respuesta){
                cout<<"\n Este Mecanico ya esta Registrado en el Sistema"<<endl;
                cout<<"Posee el Siguiente Registro: "<<endl;
                respuesta->mostrarInformacion();
                cout<<"\n\nPor favor, ingrese un Nombre de Usuario distintas."<<endl;
            }
        }while(respuesta); 
    }

    if(tipo == "Registrado"){
        do{
            cout<<"Ingrese el Nombre de Usuario del Mecanico: ";
            getline(cin >> ws, nombreUsuario);

            respuesta = dynamic_cast<Mecanico*>(sistema.buscarUsuario(nombreUsuario));

            if(!respuesta){
                cout<<"\nNo existe un Mecanico en el Sistema con el Nombre de Usuario "<<nombreUsuario<<endl;
                cout<<"Por favor, vuelva a intentarlo\n"<<endl;
            }
        }while(!respuesta);
    }
    return respuesta;
}

Usuario* Menu::pedirUsuario(string tipo){
    Usuario* respuesta;
    string nombreUsuario;
    if(tipo == "No Registrado"){
        do{
            cout<<"Ingrese un Nombre de Usuario No Registrado: ";
            getline(cin >> ws, nombreUsuario);

            respuesta = sistema.buscarUsuario(nombreUsuario);

            if(respuesta){
                cout<<"\n Este Usuario ya esta Registrado en el Sistema"<<endl;
                cout<<"Posee el Siguiente Registro: "<<endl;
                respuesta->mostrarInformacion();
                cout<<"\n\nPor favor, ingrese un Nombre de Usuario distinto."<<endl;
            }
        }while(respuesta); 
    }

    if(tipo == "Registrado"){
        do{
            cout<<"Ingrese el Nombre del Usuario: ";
            getline(cin >> ws, nombreUsuario);

            respuesta = sistema.buscarUsuario(nombreUsuario);

            if(!respuesta){
                cout<<"\nNo existe un Usuario en el Sistema con el Nombre de Usuario "<<nombreUsuario<<endl;
                cout<<"Por favor, vuelva a intentarlo\n"<<endl;
            }
        }while(!respuesta);
    }
    return respuesta;
}

Mantenimiento* Menu::pedirMantenimiento(string tipo){
    Mantenimiento* respuesta;
    int id;
    if(tipo == "No Registrado"){
        do{
            cout<<"Ingrese el ID del Mantenimiento No Registrado: ";
            cin>>id;

            respuesta = dynamic_cast<Mantenimiento*>(sistema.buscarMantenimiento(id));


            if(respuesta){
                cout<<"\n El Mantenimiento de ID "<<id<<" ya esta Registrado en el Sistema"<<endl;
                cout<<"Posee el Siguiente Registro: "<<endl;
                respuesta->mostrarInformacion();
                cout<<"\n\nPor favor, ingrese un ID distintio."<<endl;
            }
        }while(respuesta); 
    }

    if(tipo == "Registrado"){
        do{
            cout<<"Ingrese el ID del Mantenimiento Registrado: ";
            cin>>id;

            respuesta = dynamic_cast<Mantenimiento*>(sistema.buscarMantenimiento(id));

            if(!respuesta){
                cout<<"\nNo existe un Mantenimiento en el Sistema con el ID "<<id<<endl;
                cout<<"Por favor, vuelva a intentarlo\n"<<endl;
            }
        }while(!respuesta);
    }
    return respuesta;
}

//Menú Principal
void Menu::menuPrincipal(){
    
    int selector;
    string opciones;
    do{
        system("CLS");
        cout<<"GIVAM"<<endl;
        cout<<"Gestor Inteligente de Vehiculos y Administracion de Mantenimiento."<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"Menu Principal"<<endl;
        cout<<"Seleccione una de las Siguientes Opciones: "<<endl;
        opciones = "1. Gestion de Vehiculos\n2. Gestion de Usuarios\n3. Gestion de Mantenimientos.\n4. Reportes.\n5. Configuracion de su Cuenta.\n6. Informacion de GIVAM.\n7. Cerrar Sesion\n";

        selector = limiteInt(opciones,1,7);

        switch(selector){
            case 1:
                gestionVehiculos();
                break;
            case 2:
                gestionUsuarios();
                break;
            case 3:
                gestionMantenimientos();
                break;
            case 4:
                gestionReportes();
                break;
            case 5:
                editarUsuario();
                break;
            case 6:
                informacionGIVAM();
                break;
            case 7:
                usuario = nullptr;
                regresandoMenuAnterior();
                login();
                break;
        }

    }while(selector != 7);
}

//Submenús

void Menu::gestionVehiculos(){
    int opcion;
    string opciones;
    do{
        system("CLS");
        cout<<"GIVAM: Gestion de Vehiculo\n";
        cout<<"------------------------------------------------------------"<<endl;
        opciones = "1. Registrar un Nuevo Vehiculo.\n2. Editar un Vehiculo Existente.\n";
        opciones = opciones + "3. Buscar un Vehiculo.\n4. Eliminar un Vehiculo.\n5. Mostrar todo el Registro de Vehiculos.\n";
        opciones = opciones + "6. Salir al Menu Principal.\n";
       
        opcion = limiteInt(opciones,1,6);

        switch (opcion){
            case 1:
                registrarNuevoVehiculo();                
                break;
            case 2:
                editarVehiculo();
                break;
            case 3:
                buscarVehiculo();
                break;
            case 4:
                eliminarVehiculo();
                break;
            case 5:
                mostrarTodoRegistroVehiculos();
                break;
            case 6:
                regresandoMenuAnterior();
                break;
        }
    }while(opcion != 6);
}

void Menu::gestionUsuarios(){
    int opcion;
    string opciones;
    do{
        system("CLS");
        cout<<"GIVAM: Gestion de Usuarios\n";
        cout<<"------------------------------------------------------------"<<endl;
        opciones = "1. Buscar un Usuario Registrado.\n2. Mostrar Todos los Usuarios Registrados.\n";
        opciones = opciones + "3. Salir al Menu Principal.\n";
       
        opcion = limiteInt(opciones,1,3);

        switch (opcion){
            case 1:
                buscarUsuario();                
                break;
            case 2:
                mostrarTodoRegistroUsuarios();
                break;
            case 3:
                regresandoMenuAnterior();
                break;
        }
    }while(opcion != 3);
}

void Menu::gestionMantenimientos(){
    int opcion;
    string opciones;
    do{
        system("CLS");
        cout<<"GIVAM: Gestion de Mantenimientos\n";
        cout<<"------------------------------------------------------------"<<endl;
        opciones = "1. Registrar un Nuevo Mantenimiento.\n2. Buscar Mantenimiento por ID.\n";
        opciones = opciones + "3. Consultar Historial por Vehiculo.\n4. Editar Mantenimiento\n";
        opciones = opciones + "5. Salir al Menu Principal.\n";
       
        opcion = limiteInt(opciones,1,5);

        switch (opcion){
            case 1:
                registrarNuevoMantenimiento();                
                break;
            case 2:
                buscarMantenimientoPorId();
                break;
            case 3:
                consultarHistorialPorVehiculo();
                break;
            case 4:
                editarMantenimiento();
                break;
            case 5:
                regresandoMenuAnterior();
                break;
        }
    }while(opcion != 5);
}

void Menu::gestionReportes(){
    int opcion;
    string opciones;
    do{
        system("CLS");
        cout<<"GIVAM: Gestion de Reportes\n";
        cout<<"------------------------------------------------------------"<<endl;
        opciones = "1. Exportar un Reporte de un Mantenimiento Determinado.\n2. Exportar el Historial de Mantenimiento de un Vehiculo. .\n3. Exportar el Reporte de Todos los Mantenimientos Entre Dos Fechas\n";
        opciones = opciones + "4. Salir al Menu Principal.\n";
       
        opcion = limiteInt(opciones,1,4);
        
        switch (opcion){
            case 1:
                generarReporteUnico();                
                break;
            case 2:
                generarReporteDeVehiculo();
                break;
            case 3:
                generarReportesEntreFechas();
                break;
            case 4:
                regresandoMenuAnterior();
                break;
        }
    }while(opcion != 4);
}

//Funcionalidades:
    //Registros:
void Menu::registrarNuevoVehiculo(){
    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    int tipoVehiculo, repetidor; 
    string placas, marca, modelo, especificoString, tipoVehiculoString;
    int anio, especificoInt;
    float kilometraje;
    bool especificoBool;

    Vehiculo* verificador;

    do{
        system("CLS");
            string encabezado = "GIVAM: Registrar un Nuevo Vehiculo: ..............................................................................\n";
            tipoVehiculo = limiteInt(encabezado+"Indique que tipo de Vehiculo desea registrar.\n 1. Carro.\n 2. Camioneta\n 3. Moto\n 4. Regresar\n",1,4);

        if(tipoVehiculo == 4)
            break;
        
        //Verificar que las placas no estan 
        do{
            cout<<"Registrando un Vehiculo"<<endl;
            cout<<"Ingrese las placas del Nuevo Vehiculo: ";
            getline(cin>>ws,placas);

            verificador = sistema.buscarVehiculo(placas);
            if(verificador){
                system("CLS");
                cout<<"El Vehiculo ya esta registrado."<<endl;
                cout<<"Se ve de la siguiente manera: "<<endl;
                verificador->mostrarInformacion();
                cout<<"\n\n";
                cout<<"Por favor, ingrese placas distintas: "<<endl<<endl;
                system("PAUSE");
                system("CLS");
            }
        }while(verificador || placas == "");

        cout<<"Ingrese la Marca del Vehiculo: ";
        getline(cin>>ws,marca);

        cout<<"Ingrese el modelo el Vehiculo: ";
        getline(cin>>ws,modelo);

        anio = limiteInt("Ingrese el Anio del Vehiculo: ",0,Fecha().getAnio());
        kilometraje = limiteFloat("Ingrese el Kilomtraje del Vehiculo: ",0,999999999);

        switch(tipoVehiculo){
            case 1:
                tipoVehiculoString = "Carro";
                especificoInt = limiteInt("Ingrese la Cantidad de Puertas del Carro: ",1,10);
                especificoBool = (limiteInt("La Traccion es Automatica (1.Si/2.No): ",1,2) == 1);
                break;
            case 2:
                tipoVehiculoString = "Camioneta";
                cout<<"Ingrese el Tipo de Traccion de la Camioneta: ";
                cin.ignore();
                getline(cin>>ws,especificoString);
                especificoBool = (limiteFloat("Ingrese si la Camioneta tiene Caja (1.Si/2.No): ",1,2) == 1);
                break;
            case 3:
                tipoVehiculoString = "Moto";
                cout<<"Ingrese el Tipo de Moto: ";
                getline(cin>>ws,especificoString);
                break;

        }
    
        if(sistema.agregarVehiculo(tipoVehiculoString, placas, marca, modelo, anio, kilometraje, Fecha(0,0,0), especificoInt, especificoString, especificoBool))
            cout<<"\nVehiculo Agregado Correctamente.\n";
        else
            cout<<"\nHa Habido un Error en el Sistema.\n";
    
    system("PAUSE");
    system("CLS");
    repetidor = limiteInt("Desea Agregar un Nuevo Vehiculo?\n1. Si\n2. No\n",1,2);

    }while(repetidor != 2);
    regresandoMenuAnterior();
}

void Menu::registrarNuevoUsuario(){
    string nombreUsuario,contrasena,tipoUsuarioStr, nombre;
    int tipoUsuario, edad;
    Usuario* verificador;

    system("CLS");
    cout<<"GIVAM: Registro de Nuevo Usuario------------------------------------------------------------"<<endl;
    
    tipoUsuario = limiteInt("Ingrese el tipo de Usuario que Desea Registrar\nTenga en Cuenta que Cuentan con Distintos Privilegios: \n1. Administrador.\n2. Mecanico.\n3. Salir.\n",1,3);
    
    if(tipoUsuario == 3){
        regresandoMenuAnterior();
        return;
    }

    do{
        cout<<"\nIngrese su Nombre de Usuario: ";
        getline(cin>>ws,nombreUsuario);

        verificador = sistema.buscarUsuario(nombreUsuario);
        if(verificador){
            system("CLS");
            cout<<"El usuario ya esta registrado."<<endl;
            cout<<"Tiene el siguiente registro: "<<endl;
            verificador->mostrarInformacion();
            cout<<"\n\nPor favor, intente con otro Nombre de Usuario"<<endl;
        }

    }while(verificador || nombreUsuario == "");
    
    cout<<"Ingrese su contrasena: ";
    getline(cin>>ws,contrasena);

    cout<<"Ingrese su Nombre: ";
    getline(cin>>ws,nombre);

    edad = limiteInt("Ingrese su edad: ",10,999);

    switch(tipoUsuario){
        case 1:
            tipoUsuarioStr = "Administrador";
            break;
        case 2:
            tipoUsuarioStr = "Mecanico";
            break;
    }

    if(sistema.agregarUsuario(tipoUsuarioStr, nombreUsuario, contrasena, nombre, edad))
        cout<<"\nUsuario Agregado con Exito.\n";
    else
        cout<<"Ha Habio un Problema al Intentar Agregar a un Nuevo Usuario\n";
    
    system("PAUSE");
    regresandoMenuAnterior();
}

void Menu::registrarNuevoMantenimiento(){
    if(sistema.getNumeroVehiculos() == 0){
        faltaRegistro("Vehiculos");
        regresandoMenuAnterior();
        return;
    }
    int mecanicos=0;
    //Verificar que haya Mecanicos 
    for(auto usuario : sistema.getUsuariosEnteros()){
        if(usuario->getTipoUsuario() == "Mecanico")
            mecanicos++;
    }
    
    if(mecanicos == 0){
        faltaRegistro("Mecanicos");
        regresandoMenuAnterior();
        return;
    }

    string tipoMantenimientoStr, placasVehiculo, UsuarioMecanico, descripcion, especificoString1, especificoString2;
    vector<string> tareasProgramadas;

    Fecha fecha;
    int id, tipoMantenimiento, numeroTareas;
    float costo, especificoFloat;
    bool especificoBool;
    Mantenimiento* verificadorMantenimiento;
    Vehiculo* vehiculo;
    Mecanico* mecanico;

    cout<<"GIVAM: Registrar Mantenimiento-----------------------------------------------------------------------------------------"<<endl;
    tipoMantenimiento = limiteInt("Ingrese el tipo de mantenimiento que desea registrar: \n1. Mantenimiento Preventivo.\n2. Mantenimiento Correctivo.\n3. Salir\n",1,3);

    if(tipoMantenimiento == 3){
        regresandoMenuAnterior();
        return;
    }

    do{
        cout<<"Ingrese el ID del Nuevo Mantenimiento: ";
        cin>>id;

        verificadorMantenimiento = sistema.buscarMantenimiento(id);
        if(verificadorMantenimiento){
            cout<<"\nEl ID "<<id<<" ya esta registrado con un mantenimiento."<<endl;
            cout<<"Dicho mantenimiento es el siguiente: "<<endl;
            verificadorMantenimiento->mostrarInformacion();
            cout<<"\n\nPor favor, seleccione otro ID para su Nuevo Mantenimiento."<<endl;
            system("PAUSE");
            system("CLS");
        }

    }while(verificadorMantenimiento);

    vehiculo = pedirPlacas("Registrado");

    //Linea Para asignar automaticamente el mecánico si es este quién está registrando el Mantenmiento
    if(usuario->getTipoUsuario() == "Mecanico"){
        mecanico = dynamic_cast<Mecanico*>(usuario);
    }
    else{
        mecanico = pedirMecanico("Registrado");

    }

    int dinamicaFecha = limiteInt("\nPara Ingresar la Fecha: \n1. Ingresar la Fecha de Hoy.\n2. Ingresar una Fecha Diferente\n",1,2);

    if(dinamicaFecha == 1)
        fecha = Fecha();
    else if(dinamicaFecha == 2){
        int dia = limiteInt("Ingrese el dia de realizacion del mantenimiento: ",1,31);
        int mes = limiteInt("Ingrese el mes de realizacion del mantenimiento: ",1,12);
        int anio = limiteInt("Ingrese el anio de realizacion del mantenimiento: ",1800, Fecha().getAnio());
        fecha = Fecha(dia,mes,anio);
    }

    cout<<"Ingrese la descripcion del Mantenimiento: ";
    getline(cin>>ws, descripcion);

    costo = limiteFloat("Ingrese el costo total del Mantenimiento: ",0,999999999);

    switch(tipoMantenimiento){
        case 1:
            tipoMantenimientoStr = "Mantenimiento Preventivo";
            especificoFloat = limiteFloat("Ingrese el Kilometraje Recomendado para el Siguiente Mantenimiento: ",vehiculo->getKilometraje(),9999999999);
            especificoBool = (limiteFloat("Ingrese si el Mantenimiento se Realizo en el Tiempo Recomendado (1.Si/2.No): ",1,2) == 1);
                        
            if(limiteInt("Desea Ingresar Tareas Programadas para Este Mantenimiento (1.Si/2.No): ",1,2) == 1){
                numeroTareas = limiteInt("Ingrese el numero de tareas programadas a agregar al Mantenimiento Preventivo: ",0,99);
                for(int i = 0; i < numeroTareas; i++){
                    cout<<"Tarea "<<i+1<<": ";
                    getline(cin>>ws, especificoString1);
                    tareasProgramadas.push_back(especificoString1);
                }
            }
            else
                cout<<"Sin Tareas Programadas para el Mantenimiento Preventivo."<<endl;
            break;
        case 2:
            tipoMantenimientoStr = "Mantenimiento Correctivo";
            cout<<"Ingrese el Componente Averiado que se trato en el Mantenimiento Correctivo: ";
            getline(cin>>ws, especificoString1);
            cout<<"Ingrese la Causa Detectada de la Falla: ";
            getline(cin>>ws, especificoString2);
            especificoBool = (limiteInt("Ingrese si se Requirio Reemplazo de la Pieza Afectada (1.Si/2.No): ",1,2) == 1);
            break;
    }

    sistema.agregarMantenimiento(tipoMantenimientoStr, descripcion, id, vehiculo->getPlacas(), mecanico->getNombreUsuario(), fecha, costo, especificoFloat, especificoBool, especificoString1, especificoString2);
    
    if(tipoMantenimientoStr == "Mantenimiento Preventivo")
        for(auto tarea : tareasProgramadas)
            sistema.agregarTareaMantenimientoPreventivo(id, tarea);
        
    cout<<"Se ha registrado correctamente el nuevo Mantenimiento"<<endl;
    system("PAUSE");
    regresandoMenuAnterior();
    return;
}
//Eliminadores
void Menu::eliminarVehiculo(){
    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    if(sistema.getNumeroVehiculos() == 0){
        faltaRegistro("Vehiculos");
        regresandoMenuAnterior();
        return;
    }


    Vehiculo* vehiculo = nullptr;
    int repetidor;
    string placas;

    do{
        do{
            system("CLS");
            cout<<"GIVAM: Eliminar Vehiculos del Registro-----------------------------------------------------------------------endl"<<endl;
            cout<<"Ingrese las placas del Vehiculo que Desee Eliminar: "<<endl;
            cout<<"Si Desea Regresar, Ingrese -1"<<endl;

            getline(cin>>ws,placas);
            
            if(placas == "-1")
                break;
            else{
                vehiculo = sistema.buscarVehiculo(placas);
                if(!vehiculo){
                    cout<<"Vehiculo no Encontrado"<<endl;
                    cout<<"Por favor, intentelo nuevamente."<<endl;
                    system("PAUSE");

                }
            }

        }while(placas != "-1" && vehiculo == nullptr);

        if(vehiculo){
            cout<<"A continuacion, se muestra la informacion del Vehiculo seleccionado: "<<endl;
            vehiculo->mostrarInformacion();
            int confirmacion = limiteInt("\nEsta Seguro/a que Desea Eliminar Este Vehiculo? (1.Si/2.No)\nNota: Tambien seran eliminados los mantenimientos Registrados a este Vehiculo\n",1,2);
        
            if(confirmacion == 1){
                sistema.eliminarVehiculo(placas);
                cout<<"Eliminacion Exitosa."<<endl;
            }
        }
        
        vehiculo = nullptr;

        if(sistema.getNumeroVehiculos() == 0){
            cout<<"\nSe han eliminado todos los vehiculos del registro."<<endl;
            cout<<"Se regresara al menu anterior."<<endl;
            system("PAUSE");
            regresandoMenuAnterior();
            return;
        }

        repetidor= limiteInt("Desea Eliminar otro Vehiculo del Registro? (1.Si/2.No): ",1,2);
        
    }while(repetidor != 2);

    regresandoMenuAnterior();
}

void Menu::eliminarMantenimineto(){
    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("Mantenimientos");
        regresandoMenuAnterior();
        return;
    }


    Mantenimiento* mantenimiento = nullptr;
    int repetidor, id;

    do{
        do{
            system("CLS");
            cout<<"GIVAM: Eliminar Mantenimientos del Registro-----------------------------------------------------------------------endl"<<endl;
            cout<<"Ingrese el ID del Mantenimiento que Desee Eliminar: "<<endl;
            cout<<"Si Desea Regresar, Ingrese -1"<<endl;
            cin>>id;

            if(id == -1)
                break;
            else{
                mantenimiento = sistema.buscarMantenimiento(id);
                if(mantenimiento == nullptr){
                    cout<<"Mantenimiento no Encontrado."<<endl;
                    cout<<"Por favor, intetelo nuevamente."<<endl;
                    system("PAUSE");
                }

            }

        }while(id != -1 && mantenimiento == nullptr);

        if(mantenimiento){
            cout<<"A continuacion, se muestra la informacion del Mantenimiento seleccionado: "<<endl;
            mantenimiento->mostrarInformacion();
            int confirmacion = limiteInt("\nEsta Seguro/a que Desea Eliminar Este Mantenimiento? (1.Si/2.No): ",1,2);
        
            if(confirmacion == 1){
                sistema.eliminarMantenimineto(id);
                cout<<"Eliminacion Exitosa."<<endl;
            }
        }
        
        mantenimiento = nullptr;

        if(sistema.getNumeroMantenimientos() == 0){
            cout<<"\nSe han Eliminado todos los Mantenimientos del Registro."<<endl;
            cout<<"Se Regresara al Menu Anterior."<<endl;
            system("PAUSE");
            regresandoMenuAnterior();
            return;
        }

        repetidor= limiteInt("Desea Eliminar otro Mantenimiento del Registro? (1.Si/2.No): ",1,2);
        
    }while(repetidor != 2);

    regresandoMenuAnterior();   
}

void Menu::eliminarUsuario(){
    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    Usuario* usuarioAEliminar = nullptr;
    int repetidor;
    string nombreDeUsuario;

    do{
        do{
            system("CLS");
            cout<<"GIVAM: Eliminar Usuarios del Registro-----------------------------------------------------------------------endl"<<endl;
            cout<<"Ingrese el Nombre de Usuario del Registro que Desee Eliminar: "<<endl;
            cout<<"Si Desea Regresar, Ingrese -1"<<endl;

            getline(cin>>ws,nombreDeUsuario);
            
            if(nombreDeUsuario == "-1")
                break;
            else{
                usuarioAEliminar = sistema.buscarUsuario(nombreDeUsuario);
                if(usuarioAEliminar == nullptr){
                    cout<<"Usuario no Encontrado"<<endl;
                    cout<<"Por favor, intetelo Nuevamente"<<endl;
                    system("PAUSE"); 
                }
            }

        }while(nombreDeUsuario != "-1" && usuarioAEliminar == nullptr);

        if(usuarioAEliminar != nullptr && usuarioAEliminar != usuario){
            cout<<"A continuacion, se muestra la informacion del Usuario seleccionado: "<<endl;
            usuarioAEliminar->mostrarInformacion();
            int confirmacion = limiteInt("\nEsta Seguro/a que Desea Eliminar Este Usuario? (1.Si/2.No)\nNota: Al Eliminar un Mecanico, Tambien Se Eliminaran Sus Mantenimientos Realizados\n",1,2);
        
            if(confirmacion == 1){
                sistema.eliminarUsuario(nombreDeUsuario);
                cout<<"Eliminacion Exitosa."<<endl;
            }
        }

        else if(usuarioAEliminar != nullptr && usuarioAEliminar == usuario){
            cout<<"El Usuario Seleccionado es el Suyo: "<<endl;
            usuarioAEliminar->mostrarInformacion();
            int confirmacion = limiteInt("\nEsta Seguro/a que Desea Eliminar Su Perfil? (1.Si/2.No): \nNota: Al Eliminar un Mecanico, Tambien se Eliminaran Sus Matenimientos Realizados\n",1,2);
            if(confirmacion == 1){
                sistema.eliminarUsuario(nombreDeUsuario);
                usuario = nullptr;
                cout<<"Elinacion Exitosa."<<endl;
                cout<<"Su Sesion Ha Sido Eliminada."<<endl;
                cout<<"Regresando al Login..."<<endl;
                system("PAUSE");
                login();
            }
        }
        usuarioAEliminar = nullptr;

        repetidor= limiteInt("Desea Eliminar otro Usuario del Registro? (1.Si/2.No): ",1,2);
        
    }while(repetidor != 2);

    regresandoMenuAnterior();
}
//Editores
void Menu::editarUsuario(){
    string especificoString = "", edicion = "", evaluarContrasena;
    int especificoInt = 0, repetidor, seleccion;
    Usuario* verificador;

    do{
        system("CLS");
        cout<<"GIVAM: Editor de Perfil----------------------------------------------------------------------"<<endl;
        cout<<"Actualmente, su perfil de "<<usuario->getTipoUsuario()<<" tiene la siguiente forma: "<<endl;
        cout<<"Eliga el Numero de la opcion que desee modificar: "<<endl;
        seleccion = limiteInt("1. Nombre de Usuario: "+usuario->getNombreUsuario() + "\n2. Nombre: " + usuario->getNombre() + "\n3. Edad: " + to_string(usuario->getEdad()) + "\n4. Cambiar Contrasena.\n5. Eliminar Perfil\n6. Regresar.\n",1,6);
        switch(seleccion){
            case 1:
                do{
                    cout<<"Ingrese el Nombre de Usuario Nuevo que Desee Tener: ";
                    getline(cin>>ws, especificoString);

                    verificador = sistema.buscarUsuario(especificoString);
                    if(verificador){
                        cout<<"El Nombre de Usuario "<<especificoString<<" ya esta registrado en el sistema."<<endl;
                        cout<<"Tiene la siguiente forma: "<<endl;
                        verificador->mostrarInformacion();
                        cout<<"Por favor, ingrese un Nombre de Usuario Diferente"<<endl;

                    }
                }while(verificador);
                edicion = "Nombre de Usuario";
                break;
            case 2:
                cout<<"Ingrese el Nuevo Nombre para el Registro: ";
                getline(cin>>ws,especificoString);
                edicion = "Nombre";
                break;
            case 3:
                especificoInt = limiteInt("Ingrese la Nueva Edad para el Registro: ",15,999);
                edicion = "Edad";
                break;
            case 4:
                do{
                    cout<<"Ingrese su Contrasena Actual: \n";
                    cout<<"Nota: Si desea Regresar ingrese: -1\n";
                    getline(cin>>ws, evaluarContrasena);
                    if(evaluarContrasena == "-1"){
                        edicion = "None";
                        break;
                    }
                    
                    if(sistema.iniciarSesion(usuario->getNombreUsuario(), evaluarContrasena)){
                        cout<<"Ingrese su Nueva Contrasena: ";
                        getline(cin>>ws, especificoString);
                        edicion = "Contrasena";
                    }
                    else{
                        cout<<"Contrasena Incorrecta"<<endl;
                        cout<<"Por favor, intentelo Nuevamente.\n"<<endl;
                    }
                }while(!sistema.iniciarSesion(usuario->getNombreUsuario(), evaluarContrasena));
                break;
            case 5:{
                int confirmarEliminacion = limiteInt("Esta Seguro/a que desea Elimiar Este Perfil? (1.Si/2.No): \nNota: Para los Mecanicos, tambien seran eliminados los mantenimientos que ha realizado\n",1,2);
                if(confirmarEliminacion == 1){
                    sistema.eliminarUsuario(usuario->getNombreUsuario());
                    usuario = nullptr;
                    cout<<"Perfil Eliminado Con Exito."<<endl;
                    cout<<"Volviendo a la Pantalla de inicio"<<endl;
                    system("PAUSE");
                    login();
                }
                break;                
            }
            case 6:
                regresandoMenuAnterior();
                return;
                break;

                
        }
        if(seleccion != 5){
            sistema.editarUsuario(usuario, edicion, especificoString, especificoInt);
            cout<<"Edicion Realizada con Exito."<<endl;
            repetidor = limiteInt("Desea Editar Otro Apartado de su Perfil? (1.Si/2.No): ",1,2); 
        }
    }while(repetidor != 2); 
}

void Menu::editarVehiculo(){
    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    if(sistema.getNumeroVehiculos() == 0){
        faltaRegistro("Vehiculos");
        regresandoMenuAnterior();
        return;
    }

    Vehiculo* vehiculo;
    int seleccion, repetidor;
    string consulta;

    string especificoString, edicion;
    int especificoInt;
    bool especificoBool;
    float especificoFloat;
    Vehiculo* verificador;

    do{
        system("CLS");
        cout<<"GIVAM: Editar Informacion de Vehiculos------------------------------------------------------\n";
        vehiculo = pedirPlacas("Registrado");
        consulta = "A continuacion se muestra la informacion del Vehiculo Seleccionado\nIngrese el numero de lo que desea modificar.\n";
        consulta = consulta + "1. Placas: " + vehiculo->getPlacas() + "\n2. Marca: " + vehiculo->getMarca() + "\n3. Modelo: " + vehiculo->getModelo() + "\n4. Anio: " + to_string(vehiculo->getAnio()) + "\n5. Kilometraje: " + to_string(vehiculo->getKilometraje());

        if(vehiculo->getTipoVehiculo() == "Carro"){
            Carro* carro = dynamic_cast<Carro*>(vehiculo);
            consulta = consulta + "\n6. Cantidad de Puertas: " + to_string(carro->getCantidadPuertas()) + "\n7. Manejo: ";
            if(carro->getEsAutomatico())
                consulta = consulta + "Automatico\n";
            else
                consulta = consulta + "Estandar\n";
            seleccion = limiteInt(consulta, 1, 7);

        }
        
        else if(vehiculo->getTipoVehiculo() == "Camioneta"){
            Camioneta* camioneta = dynamic_cast<Camioneta*>(vehiculo);
            consulta = consulta + "\n6. Tipo de Traccion: " + camioneta->getTipoTraccion();
            if(camioneta->getTieneCaja())
                consulta = consulta + "\n7. Tiene Caja\n";
            else
                consulta = consulta + "\n7. Sin Caja\n";
            seleccion = limiteInt(consulta, 1,7);
        }
        
        else if(vehiculo->getTipoVehiculo() == "Moto"){
            Moto* moto = dynamic_cast<Moto*>(vehiculo);
            consulta = consulta + "\n6. Tipo de Moto: " + moto->getTipoMoto() + "\n";
            seleccion = limiteInt(consulta,1,6);
            seleccion = limiteInt(consulta, 1,6);
        }
        
        //Si se selecciona algo en comun
        switch (seleccion){
            case 1:
                do{
                    cout<<"Ingrese las Placas Corregidas del Vehiculo: ";
                    getline(cin>>ws, especificoString);
                    verificador = sistema.buscarVehiculo(especificoString);
                    if(verificador){
                        cout<<"Las placas ya le pertenecen al siguiente registro: ";
                        verificador->mostrarInformacion();
                        cout<<"\nPor favor, ingrese unas placas distintas.";
                    }
                }while(verificador);
                edicion = "Placas";
                break;
            case 2:
                cout<<"Ingrese la Nueva Marca del Vehiculo: ";
                getline(cin>>ws,especificoString);
                edicion = "Marca";
                break;
            case 3:
                cout<<"Ingrese el Nuevo Modelo del Vehiculo: ";
                getline(cin>>ws,especificoString);
                edicion = "Modelo";
                break;
            case 4:
                especificoInt = limiteInt("Ingrese el Anio del Vehiculo: ",1600,99999);
                edicion = "Anio";
                break;
            case 5:
                especificoFloat = limiteFloat("Ingrese el Kilometraje Actualizado del Vehiculo\nNota: Solo se permite un Kilometraje Superior\n",vehiculo->getKilometraje(),9999999);
                edicion = "Kilometraje";
                break;
            }

            if(vehiculo->getTipoVehiculo() == "Carro"){
                if(seleccion == 6){
                    especificoInt = limiteInt("Ingrese la Cantidad de Puertas del Vehiculo: ",1,10);
                    edicion = "Cantidad Puertas";
                }
                else if(seleccion == 7){
                    especificoBool = (limiteInt("Ingrese si el Carro tiene un Manejo Automatico (1.Si/2.No): ",1,2) == 1);                
                    edicion = "Es Automatico";
                }
            }

            if(vehiculo->getTipoVehiculo() == "Camioneta"){
                if(seleccion == 6){
                    cout<<"Ingrese el Tipo de Traccion de la Camioneta: ";
                    getline(cin>>ws,especificoString);
                    edicion = "Tipo Traccion";
                }
                else if(seleccion == 7){
                    especificoBool = (limiteInt("Especifique si la Camioneta Tiene Caja (1.Si/2.No): ",1,2) == 1);
                    edicion = "Tiene Caja";
                }
            }

            if(vehiculo->getTipoVehiculo() == "Moto"){
                if(seleccion == 6){
                    cout<<"Ingrese el Tipo de Moto: ";
                    getline(cin>>ws, especificoString);
                    edicion = "Tipo Moto";
                }
            }
            sistema.editarVehiculo(vehiculo, edicion, especificoString, especificoInt, especificoFloat, especificoBool);
            cout<<"Cambio Realizado con Exito.";
            system("PAUSE");
            repetidor = limiteInt("Desea Realizar Otra Edicion? (1.Si/2.No): ",1,2);
    }while(repetidor != 2);
}


void Menu::editarMantenimiento(){
    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("Mantenimientos");
        regresandoMenuAnterior();
        return;
    }

    if(usuario->getTipoUsuario() != "Administrador"){
        accesoDenegado();
        regresandoMenuAnterior();
        return;
    }

    Mantenimiento* mantenimiento;
    Mantenimiento* verificador;
    int seleccion, repetidor;
    string consulta;
    string especificoString, edicion;
    int especificoInt, especificoInt2, especificoInt3;
    float especificoFloat;
    Mecanico* mecanico;
    Fecha especificoFecha;
    bool especificoBool;

    do{
        system("CLS");
        cout<<"GIVAM: Editar Informacion de un Mantenimiento------------------------------------------------"<<endl;
        mantenimiento = pedirMantenimiento("Registrado");
        consulta = "A continuacion, se muestra la informacion del mantenimiento Seleccionado\nIngrese el Numero de lo que Desee modificar.\n";
        consulta = consulta + "1. ID: " + to_string(mantenimiento->getId()) + "\n2. Responsable: " + mantenimiento->getResponsable()->getNombre() + "\n3. Fecha de Realizacion: " + to_string(mantenimiento->getFecha().getDia()) + "/" + to_string(mantenimiento->getFecha().getMes()) + "/" + to_string(mantenimiento->getFecha().getAnio());
        consulta = consulta + "\n4. Descripcion: " + mantenimiento->getDescripcion() + "\n5. Costo: " + to_string(mantenimiento->getCosto());

        if(mantenimiento->getTipo() == "Mantenimiento Preventivo"){
            MantenimientoPreventivo* mantenimientoPreventivo = dynamic_cast<MantenimientoPreventivo*>(mantenimiento);
            consulta = consulta + "\n6. Agregar una Tarea Programada\n7. Kilometraje Objetivo: " + to_string(mantenimientoPreventivo->getKilometrajeObjetivo()) + "\n8. Mantenimiento Realizado a Tiempo: ";
            if(mantenimientoPreventivo->getRealizadoATiempo())
                consulta = consulta + "Si\n";
            else
                consulta = consulta + "No\n";
            seleccion = limiteInt(consulta,1,8);
        }

        else if(mantenimiento->getTipo() == "Mantenimiento Correctivo"){
            MantenimientoCorrectivo* mantenimientoCorrectivo = dynamic_cast<MantenimientoCorrectivo*>(mantenimiento);
            consulta = consulta + "\n6. Componente Averiado: " + mantenimientoCorrectivo->getComponenteAveriado() + "\n7. Causa Falla: " + mantenimientoCorrectivo->getCausaFalla() + "\n8. La Pieza Requirio Reemplazo: ";
            if(mantenimientoCorrectivo->getRequirioReemplazo())
                consulta = consulta + "Si\n";
            else
                consulta = consulta + "No\n";
            seleccion = limiteInt(consulta,1,8);
        }
        
        //Si se selecciona algo en común
        switch(seleccion){
            case 1:
                do{
                    cout<<"Ingrese el Nuevo ID para el Mantenimiento: ";
                    cin>>especificoInt;
                    verificador = sistema.buscarMantenimiento(especificoInt);
                    if(verificador){
                        cout<<"El ID ya le pertenece al siguiente registro: ";
                        verificador->mostrarInformacion();
                        cout<<"\nPor favor, ingrese un ID diferente.";
                    }
                }while(verificador);
                edicion = "Id";
                break;
            case 2:
                mecanico = pedirMecanico("Registrado");
                edicion = "Responsable";
                break;
            case 3:
                especificoInt = limiteInt("Ingrese el Nuevo Dia de Realizacion: ",1,31);
                especificoInt2 = limiteInt("Ingrese el Nuevo Mes de Realizacion: ",1,12);
                especificoInt3 = limiteInt("Ingrese el Anio de Realizacion: ",1500, Fecha().getAnio());
                especificoFecha = Fecha(especificoInt, especificoInt2, especificoInt3);
                edicion = "Fecha Realizacion";
                break;
            case 4:
                cout<<"Ingrese la Nueva Descripcion del Mantenimiento: ";
                getline(cin>>ws, especificoString);
                edicion = "Descripcion";
                break;
            case 5:
                especificoFloat = limiteFloat("Ingrese el Nuevo Costo del Mantenimiento: ",0,999999999);
                edicion = "Costo";
                break;
        }
        
        if(mantenimiento->getTipo() == "Mantenimiento Preventivo"){
            if(seleccion == 6){
                int numeroTareas = limiteInt("Ingrese la cantidad de Tareas nuevas que Desea Registrar: ",0,99);
                string tarea; 
                for(int i = 0; i<numeroTareas; i++){
                    cout<<"Tarea Nueva "<<i+1<<": ";
                    getline(cin>>ws,tarea);
                    sistema.agregarTareaMantenimientoPreventivo(mantenimiento->getId(),tarea);
                }
            }
            else if(seleccion == 7){
                especificoFloat = limiteFloat("Ingrese el Nuevo Kilometraje Objetivo\nNota: Tiene que se mayor al Kilometraje Actual del Vehiculo: ",mantenimiento->getVehiculo()->getKilometraje(),999999999);
                edicion = "Kilometraje Objetivo";
            }
            else if(seleccion == 8){
                especificoBool = (limiteInt("Ingrese Si el Mantenimiento Fue Realizado a Tiempo (1.Si/2.No): ",1,2) == 1);
                edicion = "Realizado a Tiempo";
            }
        }

        if(mantenimiento->getTipo() == "Mantenimiento Correctivo"){
            if(seleccion == 6){
                cout<<"Ingrese el Componente Averiado: ";
                getline(cin>>ws, especificoString);
                edicion = "Componente Averiado";
            }
            else if(seleccion == 7){
                cout<<"Ingrese la Nueva Causa de la Falla: ";
                getline(cin>>ws, especificoString);
                edicion = "Causa Falla";
            }
            else if(seleccion == 8){
                especificoBool = (limiteInt("Ingrese si la Pieza Requirio de un Reemplazo (1.Si/2.No): ",1,2) == 1);
                edicion = "Requirio Reemplazo";
            }
        }
        
        sistema.editarMantenimiento(mantenimiento, edicion, especificoString, especificoInt, especificoFloat, especificoBool, especificoFecha, mecanico);
        cout<<"Cambio realizado con Exito"<<endl;
        system("PAUSE");
        repetidor = limiteInt("Desea Realizar Otra Edicion? (1.Si/2.No): ",1,2);
    }while(repetidor != 2);


}

//Buscadores
void Menu::buscarUsuario(){
    if(sistema.getNumeroUsuarios() == 0){
        faltaRegistro("Usuarios");
        regresandoMenuAnterior();
        return;
    }
    int repetidor;
    string nombreUsuario;
    Usuario* usuario;
    do{
        system("CLS");
        cout<<"GIVAM: Buscar Usuario Registrados por Nombre de Usuario--------------------------------------------------------------------------------------------"<<endl;
        cout<<"Ingrese el Nombre de Usuario del Mecanico que quiera buscar: ";
        getline(cin>>ws, nombreUsuario);
        usuario = sistema.buscarUsuario(nombreUsuario);

        if(usuario)
            usuario->mostrarInformacion();
        else
            cout<<"El Nombre de Usuario "<<nombreUsuario<<" no se encuentra registrado en el sistema.";
        
        cout<<endl;
        repetidor = limiteInt("Desea Realizar Una Nueva Busqueda? (1.Si/2.No): ",1,2);
    }while(repetidor != 2);
}



void Menu::buscarVehiculo(){
    if(sistema.getNumeroVehiculos() == 0){
        system("CLS");
        cout<<"No hay Vehiculos registrados."<<endl;
        cout<<"Por favor, registre vehiculos antes de Seleccionar esta opcion"<<endl;
        system("PAUSE");
        regresandoMenuAnterior();
        return;
    }


    int repetidor;
    Vehiculo* vehiculo;
    do{
        system("CLS");
        cout<<"GIVAM: Busqueda de Vehiculo"<<endl;
        vehiculo = pedirPlacas("Registrado");
        vehiculo->mostrarInformacion();
        cout<<endl;
        system("PAUSE");
        repetidor = limiteInt("Desea Realizar una Nueva Busqueda?\n1. Si\n2. No\n",1,2);
    }while(repetidor != 2);
    regresandoMenuAnterior();
}

void Menu::buscarMantenimientoPorId(){
    if(sistema.getNumeroVehiculos() == 0){
        faltaRegistro("Mantenimientos");
        regresandoMenuAnterior();
        return;
    }

    int repetidor;
    Mantenimiento* mantenimiento;
    do{
        system("CLS");
        cout<<"GIVAM: Consulta de Mantenimiento."<<endl;
        mantenimiento = pedirMantenimiento("Registrado");
        mantenimiento->mostrarInformacion();
        cout<<endl;
        system("PAUSE");
        repetidor = limiteInt("Desea Realizar una Nueva Busqueda?\n1. Si.\n2. No.\n",1,2);
    }while(repetidor != 2);
}

//Mostradores
void Menu::mostrarTodoRegistroVehiculos(){
    system("CLS");
    
    if(sistema.getNumeroVehiculos() == 0){
        cout<<"Aun no hay Vehiculos Registrados"<<endl;
        cout<<"Por favor, registre Vehiculos Antes de Seleccionar esta Opcion."<<endl;
        system("PAUSE");
        regresandoMenuAnterior();
        return;
    }
    
    cout<<"GIVAM: Registro Completo de Vehiculos.------------------------------------------------------------------------"<<endl;
    cout<<"A continuacion, se muestra el total de Vehiculos registrados en GIVAM"<<endl;

    sistema.mostrarVehiculos();
    system("PAUSE");
    regresandoMenuAnterior();
}

void Menu::mostrarTodoRegistroUsuarios(){
    system("CLS");
    
    cout<<"GIVAM: Registro Completo de Usuarios.------------------------------------------------------------------------"<<endl;
    cout<<"A continuacion, se muestra el total de Usuarios registrados en GIVAM"<<endl;

    sistema.mostrarUsuarios();
    system("PAUSE");
    regresandoMenuAnterior();
}

void Menu::consultarHistorialPorVehiculo(){
    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("Mantenimientos");
        regresandoMenuAnterior();
        return;
    }
    int repetidor;
    Vehiculo* vehiculo;
    do{
        cout<<"GIVAM: Consulta del Historial del Mantenimiento de un Vehiculo-------------------------------------------------------"<<endl;
        vehiculo = pedirPlacas("Registrado");
        if(vehiculo)
            vehiculo->mostrarHistorial();
        cout<<endl;
        repetidor = limiteInt("Desea realizar una nueva busqueda? (1.Si/2.No): ",1,2);

    }while(repetidor != 2);
}   

//Generación de Reportes

void Menu::generarReporteUnico(){
    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("Mantenimientos");
        regresandoMenuAnterior();
        return;
    }

    Mantenimiento* mantenimiento;
    GestorMantenimientoCSV gestorCSV;
    vector<Mantenimiento*> registro;
    int repetidor;
    string nombreArchivo;
    do{
        cout<<"GIVAM: Exportar Reporte de Mantenimiento---------------------------------------------------------------"<<endl;
        mantenimiento = pedirMantenimiento("Registrado");
        registro.push_back(mantenimiento);
        nombreArchivo = mantenimiento->getVehiculo()->getPlacas() + "-" + mantenimiento->getVehiculo()->getTipoVehiculo() +"-ID" + to_string(mantenimiento->getId())+ "-" + mantenimiento->getTipo() + "-" + to_string(mantenimiento->getFecha().getDia()) + "_" + to_string(mantenimiento->getFecha().getMes()) + "_" + to_string(mantenimiento->getFecha().getAnio()) + ".txt";
        gestorCSV.exportarReporteMantenimiento(registro, nombreArchivo);
        cout<<"Reporte Generado con Exito"<<endl;
    
        repetidor = limiteInt("Desea Exportar otro Mantenimiento Registrado? (1.Si/2.No): ",1,2);
        }while(repetidor != 2);    
        system("PAUSE");
        regresandoMenuAnterior();
    return;
}

void Menu::generarReportesEntreFechas(){
    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("mantenimientos");
        regresandoMenuAnterior();
        return;
    }
    int repetidor;
    int dia, mes, anio;
    Fecha fechaMenor, fechaMayor;
    vector<Mantenimiento*> registro;
    string nombreArchivo;
    GestorMantenimientoCSV gestorCSV;

    do{
        system("CLS");
        cout<<"GIVAM: Exportar Mantenimientos Entre Fechas: --------------------------------------------------"<<endl;
        cout<<"Ingrese la Primera Fecha de la Cual Quiera Exportar los Mantenimientos: "<<endl;
        dia = limiteInt("Dia: ",1,31);
        mes = limiteInt("Mes: ",1,12);
        anio = limiteInt("Anio: ",1500, Fecha().getAnio());

        fechaMenor = Fecha(dia,mes,anio);

        cout<<"\nIngrese la Segunda Fecha de la Cual Quiera Exportar los Manteniniemtos: "<<endl;
        dia = limiteInt("Dia: ",1,31);
        mes = limiteInt("Mes: ",1,12);
        anio = limiteInt("Anio: ",1500,Fecha().getAnio());

        fechaMayor = Fecha(dia,mes,anio);

        registro = sistema.adjuntarMantenimientosPorFecha(fechaMenor, fechaMayor);

        if(registro.size() == 0){
            cout<<"No existen mantenimientos entre las fechas dadas"<<endl;
        }

        else{
            nombreArchivo = "ReporteEntreFechas_" + to_string(fechaMenor.getDia()) + "-" + to_string(fechaMenor.getMes()) + "-" + to_string(fechaMenor.getAnio()) + "_";
            nombreArchivo = nombreArchivo + to_string(fechaMayor.getDia()) + "-" + to_string(fechaMayor.getMes()) + "-" + to_string(fechaMayor.getAnio());
            nombreArchivo = nombreArchivo + ".txt";
            gestorCSV.exportarReporteMantenimiento(registro,nombreArchivo);
            cout<<"Reporte Exportado con Exito!"<<endl;
        }

        repetidor = limiteInt("Desea Exportar Mas Reportes Entre Fechas Dadas? (1.Si/2.No): ",1,2);
    }while(repetidor != 2);

    regresandoMenuAnterior();
}

void Menu::generarReporteDeVehiculo(){
    if(sistema.getNumeroMantenimientos() == 0){
        faltaRegistro("mantenimientos");
        regresandoMenuAnterior();
        return;
    }

    if(sistema.getNumeroVehiculos() == 0){
        faltaRegistro("Vehiculos");
        regresandoMenuAnterior();
        return;
    }

    int repetidor;
    Vehiculo* vehiculo;
    string nombreArchivo;
    GestorMantenimientoCSV gestorCSV;

    do{
        system("CLS");
        cout<<"GIVAM: Exportar Reportes de los Mantenimientos de un Vehiculo: --------------------------------------------------"<<endl;
        
        vehiculo = pedirPlacas("Registrado");

        if(vehiculo->getHistorial().size() == 0){
            cout<<"El vehiculo aun no tiene Mantenimientos Registrados."<<endl;
            cout<<"Por favor, intetelo con otro Vehiculo"<<endl;
        }

        else{
            nombreArchivo = vehiculo->getPlacas() + "-" + vehiculo->getTipoVehiculo() + "-ReportesMantenimiento.txt";
            gestorCSV.exportarReporteMantenimiento(vehiculo->getHistorial(),nombreArchivo);
            cout<<"Reporte Exportado con Exito!"<<endl;
        }

        repetidor = limiteInt("Desea Exportar el Registro de Otro Vehiculo? (1.Si/2.No): ",1,2);
    }while(repetidor != 2);

    regresandoMenuAnterior();
}

//Login. Primera Pantalla
void Menu::login(){
    int opcion;
    do{
        system("CLS");
        cout<<"Bienvenido/a al GIVAM"<<endl;
        cout<<"Gestor Inteligente de Vehiculos y Administracion de Mantenimiento"<<endl;

        opcion = limiteInt("Desea Iniciar Sesion o Registrarse en GIVAM?\n1. Iniciar Sesion.\n2. Registrarse\n3. Cerrar GIVAM\n",1,3);
    
        if(opcion == 1){
        iniciarSesion();
    }

    else if(opcion == 2){
            registrarNuevoUsuario();
        }
    else if(opcion == 3){
        cout<<"\nSaliendo de GIVAM..."<<endl;
        cout<<"Tenga un Lindo Dia :)"<<endl;
        cout<<"-----------------------------------------------------------------------------"<<endl;
        exit(-1);
    }

    }while(usuario == nullptr);
    
    menuPrincipal();

}

int main(){
    //Crear el Objeto GIVAM que sirve como el cerebro y base de datos central
    GIVAM bd;
    //En caso de que GIVAM haya sido ejecutado con anterioridad, carga los registros de la información guardada para que no se resetee cada vez que se cierra
    bd.cargarRegistros();
    //Creamos el objeto Menu que maneja el Menu Principal y Secundarios ademas de la depuracion de datos para las funciones de GIVAM
    Menu menu(bd);
    //ejecutamos el Login, la pantalla inicial donde se inicia sesión o se registran nuevos perfiles.
    menu.login();
    return 0;
}