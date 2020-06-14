/**
 *  @file VsPointer.h
 *  @version 1.0
 *  @date 11/05/2020
 *  @author Mario Gudino
 *  @title VsPointer
 *  @brief Clase que define un nuevo tipo de puntero para almacenar datos mediante sobrecarga de operadores
 */

#ifndef VSPOINTER_VSPOINTER_H
#define VSPOINTER_VSPOINTER_H

#include <iostream>
#include "../GarbageCollector/GarbageCollector.h"
using namespace std;

template <typename T>
class VsPointer {
private:
    T* data;
public:
    /**
     * @brief New metodo estatico para instanciar nuevos vspointers
     * @return VsPointer
     */
    static VsPointer<T> New();

    /**
     * @brief Sobrecarga de operador "=', copia la direccion de memoria
     * @param newData VsPointer<T> el cual es copiado
     * @return direccion de memoria del vspointer
     */
    VsPointer& operator=(VsPointer<T> newData);

    /**
     * @brief Sobrecarga de operador = para asignar un nuevo dato
     * @param newData Dato el cual es asignado
     * @return direccion de memoria del vspointer
     */
    VsPointer& operator=(T newData);

    /**
     * @brief Sobrecarga de operador * para asignar un nuevo dato
     * @return direccion de memoria de T generico
     */
    T& operator*();

    /**
     * @brief Sobrecarga de operador & para asignar un nuevo dato
     * @return dato guardo en el vspointer
     */
    T operator&();

    /**
     * @brief VsPointer Constructor de la clase VsPointer
     */
    VsPointer();

    /**
     * @brief VsPointer Destructor de la clase VsPointer
     */
    ~VsPointer();

    /**
     * @brief getTdata Se utiliza para obtener dato guardado generico guardo en puntero
     * @return Puntero generico que almacena dato
     */
    T* getTdata();
};


template <class T>
VsPointer<T> VsPointer<T>::New() {
    return VsPointer();
}

template <class T>
VsPointer<T>::VsPointer() {
    this->data = new T;
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->addToList(this->data);
}


template <class T>
T& VsPointer<T>::operator*() {
    return *data;
}

template <typename T>
T VsPointer<T>::operator&() {
    return *data;
}


template <class T>
VsPointer<T>& VsPointer<T>::operator=(VsPointer<T> newData) {
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->copyRef(newData.data, this->data);
    this->data = newData.data;
}

template <class T>
VsPointer<T>& VsPointer<T>::operator=(T newData) {
    *this->data = newData;
}

template <typename T>
VsPointer<T>::~VsPointer() {
    /*
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->deleteData(this->data);
     */

}

template <typename T>
T* VsPointer<T>::getTdata() {
    return this->data;
}
#endif //VSPOINTER_VSPOINTER_H
