#ifndef FECHA_H
#define FECHA_H

#include <string>

using namespace std;

class Fecha {
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;

    bool esBisiesto() const;
    unsigned short int diasDelMes() const;

public:
    // Constructores
    Fecha();
    Fecha(unsigned short int d, unsigned short int m,
          unsigned short int a);
    Fecha(const string& f);
    Fecha(const Fecha& otra);

    // Getters
    unsigned short int getDia() const;
    unsigned short int getMes() const;
    unsigned short int getAnio() const;

    // Setters
    bool setDia(unsigned short int d);
    bool setMes(unsigned short int m);
    bool setAnio(unsigned short int a);
    bool setFecha(const string& f);

    // Operaciones
    bool esValida() const;
    void mostrar() const;

    // Operadores
    Fecha& operator=(const Fecha& otra);
    bool operator<(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;

    // Memoria
    unsigned long int memoriaUsada() const;
};

#endif
