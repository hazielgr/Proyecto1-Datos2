#include <iostream>
using namespace std;
template <typename T>

class VsPointer {
private:
    T* data;
    VsPointer();
public:
   static VsPointer<T> New();
   void operator=(VsPointer<T> data);
   void operator=(T data);
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
//sobrecarga operador "=" para poder asignar datos a la instancia
template <class T>
void VsPointer<T>::operator=(T newData) {
    *(this->data) = newData;
    cout<<"Se asigna dato"<<endl;
}

//sobrecarga el operador "=" para igualar dos VsPointers
template <class T>
void VsPointer<T>::operator=(VsPointer<T> newData) {
    this->data = newData.data;
    cout<<"Se asigna un puntero"<<endl;
}