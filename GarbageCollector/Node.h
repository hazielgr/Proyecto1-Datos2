//
// Created by haziel on 5/6/20.
//

#ifndef GARBAGECOLLECTOR_NODE_H
#define GARBAGECOLLECTOR_NODE_H

#include <string>

using namespace std;
template <typename T>
class Node {
private:
    T* data;
    Node<T>* next;
    int id;
    string dataType;
    int references = 1;
public:
    T getData();
    T* getMemDir();
    Node* getNext();
    void setData(T* newData);
    void setNext(Node* next);
    void setID(int newID);
    int getID();
    void setDataType(string newDataType);
    string getDataType();
    int getReferences();
    void setReferences(int newRef);
};


template <typename T>
T Node<T>::getData() {
    return (*this->data);
}

template <typename T>
T* Node<T>::getMemDir() {
    return (this->data);
}

template <typename T>
Node<T>* Node<T>::getNext() {
    return this->next;
}

template <typename T>
void Node<T>::setData(T* newData) {
    this->data = newData;
}

template <typename T>
void Node<T>::setNext(Node *next) {
    this->next = next;
}

template <typename T>
int Node<T>::getID() {
    return this->id;
}

template <typename T>
void Node<T>::setID(int newID) {
    this->id = newID;
}

template <typename T>
void Node<T>::setDataType(string newDataType) {
    this->dataType = newDataType;
}

template <typename T>
string Node<T>::getDataType()  {
    return this->dataType;
}

template <typename T>
void Node<T>::setReferences(int newRef) {
    this->references = newRef;
}

template <typename T>
int Node<T>::getReferences() {
    return this->references;
}

#endif //GARBAGECOLLECTOR_NODE_H
