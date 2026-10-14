#include "funciones.h"
#include "udeabook.h"
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
        cin.ignore();
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
