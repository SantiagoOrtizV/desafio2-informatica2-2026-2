#include "udeabook.h"
#include "album.h"
#include "foto.h"
#include "fecha.h"
#include "usuario.h"
#include "mensaje.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <ctime>

using namespace std;

UdeaBook::UdeaBook(){
    usuarios = nullptr;
    cantidadUsuarios = 0;
    usuarioActual = nullptr;
}

UdeaBook::~UdeaBook() { //libera toda la memoria usada para cargar los usuarios
    delete[] usuarios;
}


unsigned int contarUsuarios(const string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Buscando archivos en: " << filesystem::current_path() << endl;
        return 0;
    }
    unsigned int cantidad = 0;
    string linea;

    while (getline(archivo, linea)) {
        cantidad++;
    }
    archivo.close();
    return cantidad;
}

void separarCampos(const string& linea, string campos[5]) {
    unsigned int campo = 0;

    for (unsigned int i = 0;
         i < linea.length() && campo < 5;
         i++) {

        if (linea[i] == ';') {
            campo++;
        } else {
            campos[campo] += linea[i];
        }
    }
}

void UdeaBook::cargaUsuarios(){
    const string ruta = "usuarios.txt";

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << ruta << endl;
        return;
    }
    cout << "Archivo leido exitosamente!"<<endl;

    unsigned int nuevaCantidad = contarUsuarios(ruta); //contamos usuarios antes de reemplazar la carga anterior
    //cout << "nueva cantidad usuarios: "<<nuevaCantidad<<endl;

    delete[] usuarios;
    usuarios = nullptr;
    usuarioActual = nullptr;
    cantidadUsuarios = nuevaCantidad;

    usuarios = new Usuario[cantidadUsuarios];

    unsigned int cont = 1;
    string linea;

    while (getline(archivo, linea)) {
        string campos[5];
        if (linea.length() > 0) {
            separarCampos(linea, campos);
        }
        unsigned char valorChar = static_cast<unsigned char>(stoi(campos[3]));
        *(usuarios+cont-1) = Usuario(campos[1], campos[2], campos[4], valorChar, Fecha(campos[0]),cont);
        cont++;
    }
    archivo.close();
}


void UdeaBook::cargaAlbumes() {
    ifstream archivo("albumes.txt");

    if (!archivo.is_open()) {
        cout << "No se encontro albumes.txt. Se iniciara sin albumes."
             << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        string campos[5];
        separarCampos(linea, campos);

        try {
            unsigned int indiceUsuario =
                static_cast<unsigned int>(stoi(campos[0]));

            string nombreAlbum = campos[1];

            unsigned int privacidad =
                static_cast<unsigned int>(stoi(campos[2]));

            // Verificar que el propietario exista.
            if (indiceUsuario == 0 ||
                indiceUsuario > cantidadUsuarios) {
                continue;
            }

            // Verificar que la privacidad sea valida.
            if (privacidad > Album::AMIGOS) {
                continue;
            }

            Album* nuevoAlbum = new Album(
                nombreAlbum,
                indiceUsuario,
                static_cast<unsigned char>(privacidad)
                );

            usuarios[indiceUsuario - 1].agregarAlbum(nuevoAlbum);

        } catch (...) {
            // Ignorar registros con datos numericos invalidos.
            continue;
        }
    }

    archivo.close();
    cout << "Albumes cargados exitosamente." << endl;
}



unsigned int UdeaBook::buscarUsuario(const string usuario){ //búsqueda lineal por nombre
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i].getNombre() == usuario) {
            return i + 1;
        }
    }
    return 0;
}


bool UdeaBook::iniciarSesion(const string& nombre, const string&claveInput){
    unsigned int indiceAux = buscarUsuario(nombre);
    if(indiceAux == 0){
        return false;
    }
    string clave = usuarios[indiceAux-1].getClave();
    if(clave != claveInput){
        return false;
    }
    usuarioActual = usuarios+indiceAux-1;
    return true;
}

Usuario* UdeaBook::getUsuarioActual() {
    return usuarioActual;
}

const Usuario* UdeaBook::getUsuarioActual() const {
    return usuarioActual;
}


/*
bool UdeaBook::guardarAlbumes() const {
    ofstream archivo("albumes.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir albumes.txt para guardar.\n";
        return false;
    }

    for (unsigned int i = 0; i < cantidadUsuarios; i++) { //recorremos todos los usuarios
        const Usuario& usuario = usuarios[i];

        for (unsigned int j = 0;
             j < usuario.cantidadAlbumes(); j++) { //recorremos todos los albumes de todos los usuarios, no solo el que inicio sesion

            const Album* album = usuario.obtenerAlbum(j);

            if (album == nullptr) {
                continue;
            }

            archivo << album->getIndicePropietario() << ';'
                    << album->getNombre() << ';'
                    << static_cast<unsigned int>(
                           album->getPrivacidad())
                    << '\n';
        }
    }

    archivo.close();

    if (!archivo) {
        cout << "Error al guardar los albumes.\n";
        return false;
    }

    return true;
}
*/


string fechaComoTexto(const Fecha& fecha) { //funcion que formatea la fecha para poderla escribir en archivo
    string dia = to_string(fecha.getDia());
    string mes = to_string(fecha.getMes());
    string anio = to_string(fecha.getAnio());

    if (dia.size() < 2) {
        dia = "0" + dia;
    }

    if (mes.size() < 2) {
        mes = "0" + mes;
    }

    while (anio.size() < 4) {
        anio = "0" + anio;
    }

    return dia + "/" + mes + "/" + anio;
}


/*
bool UdeaBook::guardarFotos() const {
    ofstream archivo("fotos.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir fotos.txt para guardar.\n";
        return false;
    }

    for (unsigned int i = 0; i < cantidadUsuarios; i++) { //recorremos los usuarios
        const Usuario& usuario = usuarios[i];

        for (unsigned int j = 0;
             j < usuario.cantidadAlbumes(); j++) { //para cada usuario miramos todos los albumes que tiene

            const Album* album = usuario.obtenerAlbum(j);

            if (album == nullptr) {
                continue;
            }

            for (unsigned int k = 0;
                 k < album->cantidadFotos(); k++) {

                const Foto* foto = album->obtenerFoto(k); //para cada album obtenemos sus fotos

                if (foto == nullptr) {
                    continue;
                }

                archivo << usuario.getIndice() << ';'
                        << j << ';'
                        << foto->getNombreArchivo() << ';'
                        << fechaComoTexto(foto->getFechaCap()) << ';'
                        << foto->getTamano() << ';'
                        << foto->getLikes() << '\n';
            }
        }
    }

    archivo.close();

    if (!archivo) {
        cout << "Error al guardar las fotos.\n";
        return false;
    }

    return true;
}
*/


void UdeaBook::cargaFotos() {
    ifstream archivo("fotos.txt");

    if (!archivo.is_open()) {
        cout << "No se encontro fotos.txt. Se iniciara sin fotos."
             << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        string campos[6];
        unsigned int campo = 0;

        // Separar los seis campos de la linea.
        for (unsigned int i = 0;
             i < linea.length() && campo < 6;
             i++) {
            if (linea[i] == ';') {
                campo++;
            } else {
                campos[campo] += linea[i];
            }
        }

        // Si no hay exactamente seis campos, ignorar la linea.
        if (campo != 5) {
            continue;
        }

        try {
            unsigned int indiceUsuario =
                static_cast<unsigned int>(stoi(campos[0]));

            unsigned int indiceAlbum =
                static_cast<unsigned int>(stoi(campos[1]));

            string nombreArchivo = campos[2];

            Fecha fechaCaptura;
            if (!fechaCaptura.setFecha(campos[3])) {
                continue;
            }

            unsigned long long tamano = stoull(campos[4]);

            unsigned int likes =
                static_cast<unsigned int>(stoul(campos[5]));

            // Comprobar que exista el usuario.
            if (indiceUsuario == 0 ||
                indiceUsuario > cantidadUsuarios) {
                continue;
            }

            Usuario* usuario = &usuarios[indiceUsuario - 1];

            // Comprobar que exista el album.
            if (indiceAlbum >= usuario->cantidadAlbumes()) {
                continue;
            }

            Album* album = usuario->obtenerAlbum(indiceAlbum);

            if (album == nullptr) {
                continue;
            }

            Foto* nuevaFoto = new Foto(
                fechaCaptura,
                tamano,
                nombreArchivo,
                likes
                );

            album->agregarFoto(nuevaFoto);

        } catch (...) {
            // Ignorar registros con datos numericos invalidos.
            continue;
        }
    }

    archivo.close();
    cout << "Fotos cargadas exitosamente." << endl;
}



bool UdeaBook::guardarDatos() const {
    return guardarMensajes();
}


bool UdeaBook::enviarMensaje(const string& nombreReceptor, const string& texto) {
    if (usuarioActual == nullptr) {
        return false;
    }

    if (texto.empty()) {
        return false;
    }

    unsigned int indiceReceptor = buscarUsuario(nombreReceptor);

    if (indiceReceptor == 0) {
        return false;
    }

    Usuario* receptor = &usuarios[indiceReceptor - 1];

    if (receptor == usuarioActual) {
        return false;
    }

    time_t ahora = time(nullptr);
    tm* fechaLocal = localtime(&ahora);

    if (fechaLocal == nullptr) {
        return false;
    }

    Fecha fechaEnvio(
        fechaLocal->tm_mday,
        fechaLocal->tm_mon + 1,
        fechaLocal->tm_year + 1900
        );

    Mensaje* mensaje = new Mensaje(
        usuarioActual->getIndice(),
        receptor->getIndice(),
        texto,
        fechaEnvio
        );

    if (!receptor->registrarRecibido(mensaje)) {
        delete mensaje;
        return false;
    }

    if (!usuarioActual->registrarEnviado(mensaje)) {
        receptor->retirarUltimoRecibido(mensaje);
        delete mensaje;
        return false;
    }

    return true;
}

bool UdeaBook::guardarMensajes() const { //recorremos solo los mensajes recibidos porque cada uno
    //tiene un solo receptor propietario, así evitamos guardar cada msj dos veces
    ofstream archivo("mensajes.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir mensajes.txt para guardar.\n";
        return false;
    }

    // Cada mensaje se guarda una sola vez, desde la lista
    // de recibidos de su propietario.
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        const Usuario& receptor = usuarios[i];

        for (unsigned int j = 0;
             j < receptor.cantidadRecibidos(); j++) {

            const Mensaje* mensaje = receptor.obtenerRecibido(j);

            if (mensaje == nullptr) {
                continue;
            }

            archivo << mensaje->getIndiceEmisor() << ';'
                    << mensaje->getIndiceReceptor() << ';'
                    << fechaComoTexto(mensaje->getFechaEnvio()) << ';'
                    << (mensaje->estaLeido() ? 1 : 0) << ';'
                    << mensaje->getTexto() << '\n';
        }
    }

    archivo.close();

    if (!archivo) {
        cout << "Error al guardar los mensajes.\n";
        return false;
    }

    return true;
}

void UdeaBook::cargaMensajes() { //funcion que lee el archivo de los mensajes y los carga al sistema
    ifstream archivo("mensajes.txt");

    if (!archivo.is_open()) {
        cout << "No se encontro mensajes.txt. "
             << "Se iniciara sin mensajes.\n";
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        // Separar los cuatro primeros campos.
        string campos[4];
        unsigned int campo = 0;
        unsigned int posicion = 0;

        for (; posicion < linea.length() && campo < 4; posicion++) {
            if (linea[posicion] == ';') {
                campo++;
            } else {
                campos[campo] += linea[posicion];
            }
        }

        // Deben existir los cuatro separadores.
        if (campo != 4) {
            continue;
        }

        // Todo lo restante corresponde al texto del mensaje.
        string texto = linea.substr(posicion);

        try {
            unsigned int indiceEmisor =
                static_cast<unsigned int>(stoul(campos[0]));

            unsigned int indiceReceptor =
                static_cast<unsigned int>(stoul(campos[1]));

            Fecha fechaEnvio;

            if (!fechaEnvio.setFecha(campos[2])) {
                continue;
            }

            unsigned int estado =
                static_cast<unsigned int>(stoul(campos[3]));

            if (estado > 1 ||
                indiceEmisor == 0 ||
                indiceEmisor > cantidadUsuarios ||
                indiceReceptor == 0 ||
                indiceReceptor > cantidadUsuarios ||
                indiceEmisor == indiceReceptor ||
                texto.empty()) {
                continue;
            }

            Usuario* emisor = &usuarios[indiceEmisor - 1];
            Usuario* receptor = &usuarios[indiceReceptor - 1];

            Mensaje* mensaje = new Mensaje( //creacion de nuevo objeto mensaje con los datos en el orden del constructor
                indiceEmisor,
                indiceReceptor,
                texto,
                fechaEnvio
                );

            if (estado == 1) {
                mensaje->marcarComoLeido();
            }

            // El receptor pasa a ser propietario del mensaje.
            if (!receptor->registrarRecibido(mensaje)) {
                delete mensaje;
                continue;
            }

            // El emisor conserva solamente una referencia.
            if (!emisor->registrarEnviado(mensaje)) {
                receptor->retirarUltimoRecibido(mensaje);
                delete mensaje;
                continue;
            }

        } catch (...) {
            // Ignorar registros con campos numericos invalidos.
            continue;
        }
    }

    archivo.close();

    cout << "Mensajes cargados exitosamente.\n";
}

unsigned long int UdeaBook::memoriaUsada() const {
    unsigned long int memoria = sizeof(*this);

    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        memoria += usuarios[i].memoriaUsada();
    }

    return memoria;
}
