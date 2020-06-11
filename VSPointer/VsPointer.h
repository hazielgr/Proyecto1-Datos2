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
    string type;
public:
    static VsPointer<T> New();
    VsPointer& operator=(VsPointer<T> newData);
    VsPointer& operator=(T newData);
    T& operator*();
    T operator&();
    T getData();
    string getType();
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
    if (typeid(T)== typeid(string)){
        this->type = "string";
    }
    else if (typeid(T)== typeid(int)){
        this->type = "int";
        gbC->intList.addNode(this->data);
    }
    else if (typeid(T)== typeid(bool)){
        this->type = "bool";
    }
    else if (typeid(T)== typeid(char)){
        this->type = "char";
    }
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
    gbC->intList.copyData(newData.data, this->data);
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

//retorna en un string el tipo de dato almanecado en vsPtr
template <typename T>
string VsPointer<T>::getType() {
    return this->type;
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
    gbC->intList.deleteRef(this->data);
}
#endif //VSPOINTER_VSPOINTER_H
