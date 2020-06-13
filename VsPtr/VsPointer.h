//
// Created by haziel on 26/5/20.
//

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
    static VsPointer<T> New();
    VsPointer& operator=(VsPointer<T> newData);
    VsPointer& operator=(T newData);
    T& operator*();
    T operator&();
    T getData();
    T* getDirection();
    VsPointer();
    ~VsPointer();
    void deletePtr();
};


template <class T>
VsPointer<T> VsPointer<T>::New() {
    return VsPointer();
}

//asigna memoria para el dato T* mediante new
template <class T>
VsPointer<T>::VsPointer() {
    this->data = new T;
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->addToList(this->data);
}

//sobrecarga operador * para poder asignar datos a la instancia
template <class T>
T& VsPointer<T>::operator*() {
    return *data;
}

template <typename T>
T VsPointer<T>::operator&() {
    return *data;
}

//sobrecarga el operador "=" para igualar dos VsPointers, es decir hacer un copy de la primera instancia
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

//Retorna el dato almacenado en T* vsPtr
template <typename T>
T VsPointer<T>::getData() {
    return *this->data;
}

//retorna la direccion de memorias de T* vsPtr;
template <typename T>
T* VsPointer<T>::getDirection(){
    return &(*this->data);
}

template <typename T>
VsPointer<T>::~VsPointer() {
}

template <typename T>
void VsPointer<T>::deletePtr() {
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->deleteData(this->data);
}
#endif //VSPOINTER_VSPOINTER_H
