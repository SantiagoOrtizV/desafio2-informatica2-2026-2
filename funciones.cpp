#include "funciones.h"
#include <iostream>

using namespace std;


bool inicio_sesion(bool& salir){
    cout << "                                                           " << endl;
    cout << "                          UdeaBook                         " << endl;
    cout << "                                                           " << endl;
    cout << "                      Inicio de sesion                     " << endl;
    cout << "                                                           " << endl;
    cout << "          Usuario >> ";

    char usuario[20];
    cin.getline(usuario, 20);
    bool validador_usuario = true; // bool validador de usuario()
    while(!validador_usuario){
        unsigned short int opc_quedarse;
        cout << "                                                           " << endl;
        cout << "          Usuario no existente                             ";
        cout << "          (0)salir (1)volver a intentar                    " << endl;
        cout << "          >> ";
        cin >> opc_quedarse;
        while(opc_quedarse>1){
            cout << "                                                           " << endl;
            cout << "          Ingrese una opcion valida >> ";
            cin >> opc_quedarse;
        }
        if(opc_quedarse==0){
            salir = true;
            return false;
        }
        cout << "                                                           " << endl;
        cout << "          Usuario >> ";
        cin.getline(usuario, 20);
        validador_usuario = true; // bool validador de usuario()
    }
    cout << "                                                           " << endl;
    cout << "          Contrasenia >> ";
    char contrasenia[30];
    cin.getline(contrasenia, 30);
    bool validador_contrasenia = true; // bool validador de contrasena()
    while(!validador_contrasenia){
        unsigned short int opc_quedarse;
        cout << "                                                           " << endl;
        cout << "          Contrasenia incorrecta                           " << endl;
        cout << "          (0)salir (1)volver a intentar (2)otro usuario    " << endl;
        cout << "          >> ";
        cin >> opc_quedarse;
        while(opc_quedarse>2){
            cout << "                                                           " << endl;
            cout << "          Ingrese una opcion valida >> ";
            cin >> opc_quedarse;
        }
        switch(opc_quedarse){
        case 0:
            salir = true;
            return false;
            break;
        case 1:
            salir = false;
            return false;
            break;
        }
        cout << "                                                           " << endl;
        cout << "          Usuario >> ";
        cin.getline(contrasenia, 20);
        validador_contrasenia = true; // bool validador de usuario()
    }

    cout << "                                                           " << endl;

    return true;
}


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
