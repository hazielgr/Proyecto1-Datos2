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
    VsPointer();
public:
   static VsPointer<T> New();
   void operator=(VsPointer<T> newdata);
    void operator=(T newdata);
   T& operator*();
   T operator&();
   T getData();
};

//Ejecuta el constructor de la clase para instanciar la clase
template <class T>
VsPointer<T> VsPointer<T>::New() {
    return VsPointer();
}

//asigna memoria para el dato T* mediante new
template <class T>
VsPointer<T>::VsPointer() {
    this->data = new T;
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
void VsPointer<T>::operator=(VsPointer<T> newData) {
    this->data = newData.data;
}
template <class T>
void VsPointer<T>::operator=(T newData) {
    *this->data = newData;
}
//Da return del dato T*
template <typename T>
T VsPointer<T>::getData() {
    return *this->data;
}

#endif //VSPOINTER_VSPOINTER_H
