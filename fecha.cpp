
#include "fecha.h"
#include <iostream>

// Constructor por defecto
Fecha::Fecha() : dia(1), mes(1), anio(2000) {
}

// Constructor con parámetros
Fecha::Fecha(unsigned short int d, unsigned short int m,
             unsigned short int a)
    : dia(d), mes(m), anio(a) {

    if (!esValida()) {
        dia = 1;
        mes = 1;
        anio = 2000;
    }
}

// Constructor desde texto: DD/MM/AAAA
Fecha::Fecha(const string& f) : dia(1), mes(1), anio(2000) {
    if (f.size() != 10 || f[2] != '/' || f[5] != '/') {
        return;
    }

    // Verificar que los demás caracteres sean dígitos.
    for (unsigned int i = 0; i < f.size(); i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (f[i] < '0' || f[i] > '9') {
            return;
        }
    }

    unsigned short int d =
        (f[0] - '0') * 10 + (f[1] - '0');

    unsigned short int m =
        (f[3] - '0') * 10 + (f[4] - '0');

    unsigned short int a =
        (f[6] - '0') * 1000 +
        (f[7] - '0') * 100 +
        (f[8] - '0') * 10 +
        (f[9] - '0');

    if (a == 0 || m < 1 || m > 12) {
        return;
    }

    dia = d;
    mes = m;
    anio = a;

    if (!esValida()) {
        dia = 1;
        mes = 1;
        anio = 2000;
    }
}

// Constructor de copia
Fecha::Fecha(const Fecha& otra)
    : dia(otra.dia), mes(otra.mes), anio(otra.anio) {
}

// Getters
unsigned short int Fecha::getDia() const {
    return dia;
}

unsigned short int Fecha::getMes() const {
    return mes;
}

unsigned short int Fecha::getAnio() const {
    return anio;
}

// Año bisiesto
bool Fecha::esBisiesto() const {
    return anio % 400 == 0 ||
           (anio % 4 == 0 && anio % 100 != 0);
}

// Cantidad de días del mes
unsigned short int Fecha::diasDelMes() const {
    switch (mes) {
    case 2:
        return esBisiesto() ? 29 : 28;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    default:
        return 31;
    }
}

// Validación
bool Fecha::esValida() const {
    if (anio == 0 || mes < 1 || mes > 12) {
        return false;
    }

    return dia >= 1 && dia <= diasDelMes();
}

// Setters
bool Fecha::setDia(unsigned short int d) {
    if (d < 1 || d > diasDelMes()) {
        return false;
    }

    dia = d;
    return true;
}

bool Fecha::setMes(unsigned short int m) {
    if (m < 1 || m > 12) {
        return false;
    }

    unsigned short int maxDias;

    switch (m) {
    case 2:
        maxDias = esBisiesto() ? 29 : 28;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        maxDias = 30;
        break;

    default:
        maxDias = 31;
    }

    if (dia > maxDias) {
        return false;
    }

    mes = m;
    return true;
}

bool Fecha::setAnio(unsigned short int a) {
    if (a == 0) {
        return false;
    }

    unsigned short int anterior = anio;
    anio = a;

    if (!esValida()) {
        anio = anterior;
        return false;
    }

    return true;
}

// Mostrar fecha
void Fecha::mostrar() const {
    if (dia < 10) cout << '0';
    cout << dia << '/';

    if (mes < 10) cout << '0';
    cout << mes << '/' << anio;
}

// Operador de asignación
Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }

    return *this;
}

// Comparaciones cronológicas
bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;

    return dia < otra.dia;
}

bool Fecha::operator<=(const Fecha& otra) const {
    return *this < otra || *this == otra;
}

bool Fecha::operator==(const Fecha& otra) const {
    return dia == otra.dia &&
           mes == otra.mes &&
           anio == otra.anio;
}

// Memoria del objeto
unsigned long int Fecha::memoriaUsada() const {
    return sizeof(*this);
}
