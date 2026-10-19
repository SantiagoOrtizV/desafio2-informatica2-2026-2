#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
private:
    T* datos; //plantilla que puede almacenar cualquier tipo de dato
    unsigned int cantidad;
    unsigned int capacidad;

    void ampliarCapacidad() { //funcion que aumenta el doble la capacidad del arreglo pero solo cuando este se llena
        //copia los punteros a los datos pero conserva un poco de eficiencia
        unsigned int nuevaCapacidad;

        if (capacidad == 0) {
            nuevaCapacidad = 2;
        } else {
            nuevaCapacidad = capacidad * 2; //duplicamos el doble
        }

        T* nuevosDatos = new T[nuevaCapacidad];

        for (unsigned int i = 0; i < cantidad; i++) {
            nuevosDatos[i] = datos[i];
        }

        delete[] datos; //liberacion de los datos anteriores

        datos = nuevosDatos; //sobreescrbir los mismos datos
        capacidad = nuevaCapacidad;
    }

public:
    // Constructor
    Lista()
        : datos(nullptr), cantidad(0), capacidad(0) {
    }

    // Agregar un elemento
    void agregar(const T& elemento) {
        if (cantidad == capacidad) {
            ampliarCapacidad();
        }

        datos[cantidad] = elemento;
        cantidad++;
    }

    // Acceso modificable a un elemento
    T& operator[](unsigned int i) {
        return datos[i];
    }

    // Acceso de solo lectura a un elemento
    const T& operator[](unsigned int i) const {
        return datos[i];
    }

    // Cantidad de elementos almacenados
    unsigned int tamano() const {
        return cantidad;
    }

    unsigned long int memoriaReservada() const {
        return static_cast<unsigned long int>(capacidad) //calcular espacio del arreglo de punteros
        * sizeof(T);
    }

    // Constructor de copia
    Lista(const Lista& otra)
        : datos(nullptr),
        cantidad(otra.cantidad),
        capacidad(otra.capacidad) {

        if (capacidad > 0) {
            datos = new T[capacidad];

            for (unsigned int i = 0; i < cantidad; i++) {
                datos[i] = otra.datos[i];
            }
        }
    }

    // Operador de asignación
    Lista& operator=(const Lista& otra) {
        if (this != &otra) {
            T* nuevosDatos = nullptr;

            if (otra.capacidad > 0) {
                nuevosDatos = new T[otra.capacidad];

                for (unsigned int i = 0;
                     i < otra.cantidad; i++) {
                    nuevosDatos[i] = otra.datos[i];
                }
            }

            delete[] datos;

            datos = nuevosDatos;
            cantidad = otra.cantidad;
            capacidad = otra.capacidad;
        }

        return *this;
    }

    bool quitarUltimo() { //funcion por si falla el envio de un mensaje, quitamos ese puntero del Usuario emisor
        if (cantidad == 0) {
            return false;
        }

        cantidad--;
        return true;
    }


    // Destructor
    ~Lista() {
        delete[] datos;
    }
};

#endif
