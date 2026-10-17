#include "funciones.h"
#include "udeabook.h"
#include "usuario.h"
#include "album.h"
#include "foto.h"
#include <iostream>
using namespace std;

bool inicio(){
    unsigned short int opcInicio;
    cout << "                                                           " << endl;
    cout << "                          UdeaBook                         " << endl;
    cout << "                                                           " << endl;
    cout << "          1) Iniciar sesion                                " << endl;
    cout << "          0) Salir                                         " << endl;
    cout << "                                                           " << endl;
    cout << "          >> ";
    cin >> opcInicio;
    while(opcInicio>1){
        cout << "                                                           " << endl;
        cout << "          Ingrese una opcion valida >> ";
        cin >> opcInicio;
    }
    if(opcInicio==0){
        return true;
    }
    return false;
}


bool inicio_sesion(UdeaBook &sistema){
    sistema.cargaUsuarios();
    bool salir = false;

    while(!salir){
        cout << "                      Inicio de sesion                     " << endl;
        cout << "                                                           " << endl;
        cout << "          Usuario >> ";

        string usuario;
        cin.ignore();
        getline(cin, usuario);

        cout << "                                                           " << endl;
        cout << "          Contrasenia >> ";

        string contrasenia;
        getline(cin, contrasenia);

        bool inicioCorrecto = sistema.iniciarSesion(usuario, contrasenia);

        if(inicioCorrecto){

            return true;
        } else{
            unsigned short int opcIncorrecto;
            cout << "                                                           " << endl;
            cout << "          el usuario o la clave son incorrectos            " << endl;
            cout << "                                                           " << endl;
            cout << "               (0)Salir (1)Volver a intentar               " << endl;
            cout << "                                                           " << endl;
            cout << "          >> ";
            cin >> opcIncorrecto;

            while(opcIncorrecto>1){
                cout << "                                                           " << endl;
                cout << "          Ingrese una opcion valida >> ";
                cin >> opcIncorrecto;
            }
            if(opcIncorrecto==0){
                salir = true;
            }
        }
    }
    return false;
}

//version temporal de menu para probar


void menu(UdeaBook& sistema) {
    bool cerrarSesion = false;

    while (!cerrarSesion) {
        cout << "\n";
        cout << "          Bienvenido a UdeaBook\n";
        cout << "          1) Administrar albumes\n";
        cout << "          0) Cerrar sesion\n";
        cout << "          >> ";

        unsigned short int opcion;
        cin >> opcion;

        switch (opcion) {
        case 0:
            cerrarSesion = true;
            break;

        case 1: {
            Usuario* usuario = sistema.getUsuarioActual();

            if (usuario == nullptr) {
                cout << "No hay un usuario con sesion activa.\n";
                break;
            }

            bool volver = false;

            while (!volver) {
                cout << "\n";
                cout << "          Administracion de albumes\n";
                cout << "          1) Crear album\n";
                cout << "          2) Ver mis albumes\n";
                cout << "          3) Agregar foto a un album\n";
                cout << "          4) Ver fotos de un album\n";
                cout << "          0) Volver\n";
                cout << "          >> ";

                unsigned short int opcionAlbumes;
                cin >> opcionAlbumes;

                switch (opcionAlbumes) {
                case 0:
                    volver = true;
                    break;

                case 1: {
                    string nombre;
                    unsigned int privacidad;

                    cin.ignore(10000, '\n');

                    cout << "Nombre del album >> ";
                    getline(cin, nombre);

                    if (usuario->existeAlbum(nombre)) {
                        cout << "Ya tienes un album con ese nombre.\n";
                        break;
                    }

                    cout << "Privacidad:\n";
                    cout << "0) Publico\n";
                    cout << "1) Privado\n";
                    cout << "2) Solo amigos\n";
                    cout << ">> ";
                    cin >> privacidad;

                    if (privacidad > Album::AMIGOS) {
                        cout << "Privacidad no valida.\n";
                        break;
                    }

                    Album* nuevoAlbum = new Album(
                        nombre,
                        usuario->getIndice(),
                        static_cast<unsigned char>(privacidad)
                        );

                    usuario->agregarAlbum(nuevoAlbum);

                    cout << "Album creado correctamente.\n";
                    break;
                }

                case 2: {
                    unsigned int cantidad =
                        usuario->cantidadAlbumes();

                    if (cantidad == 0) {
                        cout << "Todavia no tienes albumes.\n";
                        break;
                    }

                    cout << "\nTus albumes:\n";

                    for (unsigned int i = 0; i < cantidad; i++) {
                        const Album* album = usuario->obtenerAlbum(i);

                        if (album != nullptr) {
                            cout << i + 1 << ") "
                                 << album->getNombre()
                                 << " | Privacidad: "<<
                                static_cast<unsigned int>(album->getPrivacidad())
                                 << "\n";
                        }
                    }

                    break;
                }


                case 3: {
                    unsigned int cantidad = usuario->cantidadAlbumes();

                    if (cantidad == 0) {
                        cout << "Primero debes crear un album.\n";
                        break;
                    }

                    cout << "\nTus albumes:\n";

                    for (unsigned int i = 0; i < cantidad; i++) {
                        const Album* album = usuario->obtenerAlbum(i);

                        if (album != nullptr) {
                            cout << i + 1 << ") " << album->getNombre() << "\n";
                        }
                    }

                    unsigned int seleccion;
                    cout << "Selecciona el album >> ";
                    cin >> seleccion;

                    if (seleccion == 0 || seleccion > cantidad) {
                        cout << "Numero de album no valido.\n";
                        break;
                    }

                    Album* albumSeleccionado = usuario->obtenerAlbum(seleccion - 1);

                    if (albumSeleccionado == nullptr) {
                        cout << "No se pudo acceder al album.\n";
                        break;
                    }

                    string nombreArchivo;
                    string fechaTexto;
                    unsigned long long tamano;
                    unsigned int likes;

                    cin.ignore(100000, '\n');

                    cout << "Nombre del archivo de la foto >> ";
                    getline(cin, nombreArchivo);

                    cout << "Fecha de captura (DD/MM/AAAA) >> ";
                    getline(cin, fechaTexto);

                    cout << "Tamano en bytes >> ";
                    cin >> tamano;

                    cout << "Cantidad de likes >> ";
                    cin >> likes;

                    Foto* nuevaFoto = new Foto(
                        Fecha(fechaTexto),
                        tamano,
                        nombreArchivo,
                        likes
                        );

                    albumSeleccionado->agregarFoto(nuevaFoto);

                    cout << "Foto agregada correctamente.\n";
                    break;
                }


                case 4: {
                    unsigned int cantidad = usuario->cantidadAlbumes();

                    if (cantidad == 0) {
                        cout << "Primero debes crear un album.\n";
                        break;
                    }

                    cout << "\nTus albumes:\n";

                    for (unsigned int i = 0; i < cantidad; i++) {
                        const Album* album = usuario->obtenerAlbum(i);

                        if (album != nullptr) {
                            cout << i + 1 << ") " << album->getNombre() << "\n";
                        }
                    }

                    unsigned int seleccion;
                    cout << "Selecciona el album >> ";
                    cin >> seleccion;

                    if (seleccion == 0 || seleccion > cantidad) {
                        cout << "Numero de album no valido.\n";
                        break;
                    }

                    const Album* albumSeleccionado =
                        usuario->obtenerAlbum(seleccion - 1);

                    if (albumSeleccionado == nullptr) {
                        cout << "No se pudo acceder al album.\n";
                        break;
                    }

                    unsigned int cantidadFotos = albumSeleccionado->cantidadFotos();

                    if (cantidadFotos == 0) {
                        cout << "Este album todavia no tiene fotos.\n";
                        break;
                    }

                    cout << "\nFotos del album: "
                         << albumSeleccionado->getNombre() << "\n";

                    for (unsigned int i = 0; i < cantidadFotos; i++) {
                        const Foto* foto = albumSeleccionado->obtenerFoto(i);

                        if (foto != nullptr) {
                            cout << "\nFoto " << i + 1 << "\n";
                            cout << "Archivo: " << foto->getNombreArchivo() << "\n";
                            cout << "Fecha de captura: "
                                 << foto->getFechaCap().getDia() << "/"
                                 << foto->getFechaCap().getMes() << "/"
                                 << foto->getFechaCap().getAnio() << "\n";
                            cout << "Tamano: " << foto->getTamano()
                                 << " bytes\n";
                            cout << "Likes: " << foto->getLikes() << "\n";
                        }
                    }

                    break;
                }

                default:
                    cout << "Ingrese una opcion valida.\n";
                    break;
                }
            }

            break;
        }

        default:
            cout << "Ingrese una opcion valida.\n";
            break;
        }
    }
}


/*

void menu(bool& inicio_exitoso){
    //void visualizacion_superamigos()
    while(inicio_exitoso){
        cout << "                                                           " << endl;
        cout << "                    Bienvenido a UdeaBook                  " << endl;
        cout << "                                                           " << endl;
        cout << "                                                           " << endl;
        cout << "          1) Administrar amistades                         " << endl;
        cout << "          2) Visita perfil amigo                           " << endl;
        cout << "          3) Sugerencias de amistad                        " << endl;
        cout << "          4) Administracion de mensajes                    " << endl;
        cout << "          5) Ver otros SuperAmigos                         " << endl;
        cout << "                                                           " << endl;
        cout << "          0) Cerrar Sesion                                 " << endl;
        cout << "                                                           " << endl;
        cout << "          Su opcion >> ";

        unsigned short int opc_menu;
        cin >> opc_menu;
        while(opc_menu>5){
            cout << "          Ingrese una opcion valida >> ";
            cin >> opc_menu;
        }
        switch(opc_menu){

        case 0: //cierre sesion
            inicio_exitoso = false;
            break;

        case 1: //administrar amistades
            cout << "                                                           " << endl;
            cout << "          1) Enviar solicitud de amistad                   " << endl;
            cout << "          2) Aceptar solicitudes de amistad                " << endl;
            cout << "                                                           " << endl;
            cout << "          0) Salir                                         " << endl;
            cout << "                                                           " << endl;
            cout << "          Su opcion >> ";
            unsigned short int opc_admin;
            cin >> opc_admin;
            while(opc_admin>2){
                cout << "                                                           " << endl;
                cout << "          Ingrese una opcion valida >> ";
                cin >> opc_admin;
            }
            if(opc_admin == 0){
                break;
            }
            switch(opc_admin){
            case 1:
                // enviar solicitud de amistad
                break;
            case 2:
                // aceptar solicitud de amistad
                break;
            }
            break;

        case 2: //visitar el perfil de un amigo
            break;

        case 3: //ver sugerencias de amistad
            break;

        case 4: //administrar mensajes
            cout << "                                                           " << endl;
            cout << "          1) Enviar mensaje                                " << endl;
            cout << "          2) Leer nuevos mensajes                          " << endl;
            cout << "          3) Buscar mensajes por rango de fechas           " << endl;
            cout << "                                                           " << endl;
            cout << "          0) Salir                                         " << endl;
            cout << "                                                           " << endl;
            cout << "          Su opcion >> ";
            unsigned short int opc_mensajes;
            cin >> opc_mensajes;
            while(opc_mensajes>3){
                cout << "                                                           " << endl;
                cout << "          Ingrese una opcion valida >> ";
                cin >> opc_mensajes;
            }
            if(opc_mensajes == 0){
                break;
            }
            switch(opc_mensajes){
            case 1:
                // enviar mensaje
                break;
            case 2:
                // leer nuevos mensajes
                break;
            case 3:
                // buscar mensajes por rango de fecha
                break;
            }
            break;

        case 5: //otros superamigos
            break;
        }
    }
}
*/
