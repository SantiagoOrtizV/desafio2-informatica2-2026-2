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



unsigned int UdeaBook::buscarUsuario(const string usuario){
    unsigned int cont = 0;
    while((cont<cantidadUsuarios)&&(usuario!=(usuarios[cont].getNombre()))){
        cont++;
    }
    cont++;
    if(cont>cantidadUsuarios){
        cont = 0;
    }
    return cont;
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
    bool albumesGuardados = guardarAlbumes();
    bool fotosGuardadas = guardarFotos();

    return albumesGuardados && fotosGuardadas;
}

bool UdeaBook::enviarMensaje(unsigned int indiceReceptor,
                             const string& texto,
                             const Fecha& fechaEnvio) {
    // Verificar que haya un usuario emisor con sesion iniciada
    if (usuarioActual == nullptr) {
        return false;
    }

    // Verificar que el indice del receptor sea valido
    if (indiceReceptor == 0 ||
        indiceReceptor > cantidadUsuarios) {
        return false;
    }

    // Obtener el receptor: los indices de usuario empiezan en 1
    Usuario* receptor = &usuarios[indiceReceptor - 1];

    // Un usuario no puede enviarse mensajes a si mismo
    if (receptor == usuarioActual) {
        return false;
    }

    // Validar el texto y la fecha antes de crear el mensaje
    if (texto.empty() || !fechaEnvio.esValida()) {
        return false;
    }

    // Crear un unico mensaje
    Mensaje* mensaje = new Mensaje(
        usuarioActual->getIndice(),
        receptor->getIndice(),
        texto,
        fechaEnvio
        );

    // El receptor sera el propietario del mensaje
    if (!receptor->registrarRecibido(mensaje)) {
        delete mensaje;
        return false;
    }

    // El emisor guarda un puntero no propietario
    if (!usuarioActual->registrarEnviado(mensaje)) {
        receptor->retirarUltimoRecibido(mensaje);
        delete mensaje;
        return false;
    }

    return true;
}
