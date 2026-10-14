#include "fecha.h"

Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(unsigned short int d, unsigned short int m, unsigned short int a) {
    dia = d;
    mes = m;
    anio = a;
}

Fecha::Fecha(string f) {
    dia = 1;
    mes = 1;
    anio = 2000;
}
