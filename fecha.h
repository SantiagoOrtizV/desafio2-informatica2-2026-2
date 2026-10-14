#ifndef FECHA_H
#define FECHA_H
#include <string>

using namespace std;

class Fecha
{
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;

public:
    Fecha();
    Fecha(unsigned short int, unsigned short int, unsigned short int);
    Fecha(string);
};

#endif