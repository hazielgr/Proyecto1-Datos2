//
// Created by haziel on 26/5/20.
//

#ifndef VSPOINTER_VSPOINTER_H
#define VSPOINTER_VSPOINTER_H

#include <iostream>

using namespace std;

template <typename T>
class VsPointer {
private:
    T* data;
    string type;
    VsPointer<T>* next;
    int id;
    int references;
public:
    static VsPointer<T> New();
    VsPointer& operator=(VsPointer<T> newData);
    VsPointer& operator=(T newData);
    T& operator*();
    T operator&();
    T getData();
    string getType();
    T* getDirection();
    void setNext(VsPointer<T>* nextPtr);
    void setData(VsPointer<T> vsPtr);
    VsPointer<T>* getNext();
    VsPointer();
    int getID();
    void setID(int newID);
    int getRef();
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
    if (typeid(T)== typeid(string)){
        this->type = "string";
    }
    else if (typeid(T)== typeid(int)){
        this->type = "int";
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
void VsPointer<T>::setData(VsPointer<T> vsPtr) {
    this->data = vsPtr.data;
}

template <typename T>
void VsPointer<T>::setNext(VsPointer<T> *nextPtr) {
    this->next = nextPtr;
}

template <typename T>
VsPointer<T>* VsPointer<T>::getNext() {
    return this->next;
}

template <typename T>
int VsPointer<T>::getID(){
    return this->id;
}

template <typename T>
int VsPointer<T>::getRef(){
    return this->references;
}

//elimina el espacio en memerio del puntero data
template <typename T>
void VsPointer<T>::deletePtr() {
    delete this->data;
}

template <typename T>
void VsPointer<T>::setID(int newID) {
    this->id = newID;
}

#endif //VSPOINTER_VSPOINTER_H
