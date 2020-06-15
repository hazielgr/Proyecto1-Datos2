//
// Created by heineken97 on 11/6/20.
//
#ifndef CLIENTSIDE_NODO_H
#define CLIENTSIDE_NODO_H
#include <string>

using namespace std;
template <typename T>
class Nodo {
private:
    T* data;
    Nodo<T>* next;
    int id;
    string dataType;
    int references = 1;
public:
    T getData();
    T* getMemDir();
    Nodo* getNext();
    void setData(T* newData);
    void setNext(Nodo* next);
    void setID(int newID);
    int getID();
    void setDataType(string newDataType);
    string getDataType();
    int getReferences();
    void setReferences(int newRef);
};

template <typename T>
T Nodo<T>::getData() {
    return (*this->data);
}

template <typename T>
T* Nodo<T>::getMemDir() {
    return &(*this->data);
}

template <typename T>
Nodo<T>* Nodo<T>::getNext() {
    return this->next;
}

template <typename T>
void Nodo<T>::setData(T* newData) {
    this->data = newData;
}

template <typename T>
void Nodo<T>::setNext(Nodo *next) {
    this->next = next;
}

template <typename T>
int Nodo<T>::getID() {
    return this->id;
}

template <typename T>
void Nodo<T>::setID(int newID) {
    this->id = newID;
}

template <typename T>
void Nodo<T>::setDataType(string newDataType) {
    this->dataType = newDataType;
}

template <typename T>
string Nodo<T>::getDataType()  {
    return this->dataType;
}

template <typename T>
void Nodo<T>::setReferences(int newRef) {
    this->references = newRef;
}

template <typename T>
int Nodo<T>::getReferences() {
    return this->references;
}
#endif //CLIENTSIDE_NODO_H
