//
// Created by haziel on 9/6/20.
//

#ifndef VSPOINTER_LINKEDLIST_H
#define VSPOINTER_LINKEDLIST_H


#include "VsPointer.h"
#include "../JSON/jsonSerialize.h"

using namespace std;

template <typename T>
class LinkedList {
private:
    VsPointer<T> *head,*tail;
    int size;
public:
    LinkedList();
    void addNode(VsPointer<T> vsPtr);
    void display();
    int getSize();
};


using namespace std;

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

//agrega un nuevo nodo a la lista
template <typename T>
void LinkedList<T>::addNode(VsPointer<T> vsPtr) {
    auto *temp = new VsPointer<T>;
    temp->setData(vsPtr);
    temp->setNext(nullptr);
    if (head == nullptr){
        head = temp;
        tail = temp;
    }
    else{
        tail->setNext(temp);
        tail = tail->getNext();
    }
}

//imprime los valores de los nodos de la lista
template <typename T>
void LinkedList<T>::display(){
    VsPointer<T>* temp = head;
    while(temp!= nullptr){
        cout<<temp->getDirection()<<endl;
        jsonSerialize::enCode(temp);
        temp = temp->getNext();
        this->size++;
    }
}

//retorna int tamano de la lista
template <typename T>
int LinkedList<T>::getSize() {
    return this->size;
}

#endif //VSPOINTER_LINKEDLIST_H
