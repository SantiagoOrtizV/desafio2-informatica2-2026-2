#include "funciones.h"
#include "udeabook.h"
#include "usuario.h"
#include "album.h"
#include "foto.h"
#include "mensaje.h"
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
        cout << "          2) Administrar mensajes\n";
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
                cout << "          1) Ver mis albumes\n";
                cout << "          2) Ver fotos de un album\n";
                cout << "          0) Volver\n";
                cout << "          >> ";

                unsigned short int opcionAlbumes;
                cin >> opcionAlbumes;

                switch (opcionAlbumes) {
                case 0:
                    volver = true;
                    break;

                case 1: {
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

                case 2: {
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

                    // Empezamos mostrando la primera foto.
                    unsigned int indiceFoto = 0;
                    unsigned int opcionFoto = 0;

                    while (opcionFoto != 3) {
                        const Foto* foto = albumSeleccionado->obtenerFoto(indiceFoto);

                        if (foto == nullptr) {
                            cout << "No se pudo acceder a la foto.\n";
                            break;
                        }

                        cout << "\n================================\n";
                        cout << "Album: " << albumSeleccionado->getNombre() << "\n";
                        cout << "Foto " << indiceFoto + 1
                             << " de " << cantidadFotos << "\n";
                        cout << "Archivo: " << foto->getNombreArchivo() << "\n";
                        cout << "Fecha de captura: "
                             << foto->getFechaCap().getDia() << "/"
                             << foto->getFechaCap().getMes() << "/"
                             << foto->getFechaCap().getAnio() << "\n";
                        cout << "Tamano: " << foto->getTamano() << " bytes\n";
                        cout << "Likes: " << foto->getLikes() << "\n";
                        cout << "================================\n";

                        cout << "1) Foto siguiente\n";
                        cout << "2) Foto anterior\n";
                        cout << "3) Salir del visor\n";
                        cout << "Selecciona una opcion >> ";
                        cin >> opcionFoto;

                        switch (opcionFoto) {
                        case 1:
                            indiceFoto = (indiceFoto + 1) % cantidadFotos;
                            break;

                        case 2:
                            if (indiceFoto == 0) {
                                indiceFoto = cantidadFotos - 1;
                            } else {
                                indiceFoto--;
                            }
                            break;

                        case 3:
                            cout << "Saliendo del visor de fotos.\n";
                            break;

                        default:
                            cout << "Opcion no valida.\n";
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

            break;
        }

        case 2:{
            Usuario* usuario = sistema.getUsuarioActual();

            if (usuario == nullptr) {
                cout << "No hay un usuario con sesion activa.\n";
                break;
            }

            bool volverMensajes = false;

            while (!volverMensajes) {
                cout << "\n";
                cout << "          Administracion de mensajes\n";
                cout << "          1) Enviar mensaje\n";
                cout << "          2) Ver mensajes recibidos\n";
                cout << "          3) Ver mensajes enviados\n";
                cout << "          0) Volver\n";
                cout << "          >> ";

                unsigned short int opcionMensajes;
                cin >> opcionMensajes;

                switch (opcionMensajes) {
                case 0:
                    volverMensajes = true;
                    break;

                case 1: {
                    string nombreReceptor;
                    string texto;

                    cin.ignore(10000, '\n');

                    cout << "Nombre de usuario del destinatario >> ";
                    getline(cin, nombreReceptor);

                    cout << "Escribe tu mensaje >> ";
                    getline(cin, texto);

                    if (sistema.enviarMensaje(nombreReceptor, texto)) {
                        cout << "Mensaje enviado correctamente.\n";
                    } else {
                        cout << "No se pudo enviar el mensaje.\n";
                        cout << "Verifica que el destinatario exista, "
                             << "que no seas tu mismo y que el mensaje "
                             << "no este vacio.\n";
                    }

                    break;
                }

                case 2:{
                    unsigned int cantidad = usuario->cantidadRecibidos();

                    if (cantidad == 0) {
                        cout << "No tienes mensajes recibidos.\n";
                        break;
                    }

                    cout << "\n          Mensajes recibidos\n";

                    for (unsigned int i = 0; i < cantidad; i++) {
                        Mensaje* mensaje = usuario->obtenerRecibido(i);

                        if (mensaje != nullptr) {
                            mensaje->marcarComoLeido();

                            cout << "\nMensaje " << i + 1 << "\n";
                            mensaje->mostrar();
                            cout << "-----------------------------\n";
                        }
                    }

                    break;
                }

                case 3: {
                    unsigned int cantidad = usuario->cantidadEnviados();

                    if (cantidad == 0) {
                        cout << "No tienes mensajes enviados.\n";
                        break;
                    }

                    cout << "\n          Mensajes enviados\n";

                    for (unsigned int i = 0; i < cantidad; i++) {
                        const Mensaje* mensaje = usuario->obtenerEnviado(i);

                        if (mensaje != nullptr) {
                            cout << "\nMensaje " << i + 1 << "\n";
                            mensaje->mostrar();
                            cout << "-----------------------------\n";
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
