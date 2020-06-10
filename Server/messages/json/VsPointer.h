#ifndef VSPOINTER_VSPOINTER_H
#define VSPOINTER_VSPOINTER_H
#include <iostream>
using namespace std;
template <typename T>

class VsPointer {
private:
    T* data;
    VsPointer();
    string type;
public:
   static VsPointer<T> New();
   VsPointer& operator=(VsPointer<T> newData);
   VsPointer& operator=(T newData);
   T& operator*();
   T operator&();
   T getData();
   string getType();
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
//Da return del dato T*
template <typename T>
T VsPointer<T>::getData() {
    return *this->data;
}
template <typename T>
string VsPointer<T>::getType() {
    return this->type;
}
#endif //VSPOINTER_VSPOINTER_H
