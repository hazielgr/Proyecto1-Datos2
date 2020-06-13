//
// Created by haziel on 9/6/20.
//

#ifndef VSPOINTER_LINKEDLIST_H
#define VSPOINTER_LINKEDLIST_H

#include "Node.h"
#include<cstdlib>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T> *head,*tail;
    int size;
    int ids[1000];
public:
    LinkedList();
    void addNode(T* n);
    void display();
    int getSize();
    int generateID();
    void copyData(T* newData, T* oldData);
    void deleteRef(T* removeData);
    int cantRef(T* data);
    void updateCanRef(T* data, int cantData);
    void freeMemory();
};

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

//Agrega un nuevo nodo a lista y asiga al nodo un tipo de dato(dataType)
template <typename T>
void LinkedList<T>::addNode(T* n) {
    auto *temp = new Node<T>;
    if (typeid(T)== typeid(string)){
        temp->setDataType("string");
    }
    else if (typeid(T)== typeid(int)){
        temp->setDataType("int");
    }
    temp->setID(this->generateID());
    temp->setData(n);
    temp->setNext(nullptr);

    if (head == nullptr){
        head = temp;
        tail = temp;
    }
    else{
        tail->setNext(temp);
        tail = tail->getNext();
    }
    size++;
}

//Muestra todos los datos de la lista
template <typename T>
void LinkedList<T>::display(){
    Node<T>* temp = head;
    while(temp != nullptr){
        cout<<temp->getData()<<endl;
        temp = temp->getNext();
    }
}

//retorna el tamano de lista, es decir la cantidad de elementos de la lista
template <typename T>
int LinkedList<T>::getSize(){
    return this->size;
}

//genera un int aleatorio y lo retorna, tambien guarda el numero generado en un array para que no se repitan los id
template <typename T>
int LinkedList<T>::generateID(){
    int i = 0;
    int num = rand()%100;
    while(ids[i]!=0){
        if(ids[i]==num) {
            num = rand() % 1000;
        }
        else{
            i++;
        }
    }
    ids[i]=num;
    return num;
}

//Primero encuentra cual es el id del nodo que posee el dato newData, una vez que encuentra ese id
//sustituye el id del nodo con el dato oldData por el id encontrado, despues de esto sustituye al nodo con oldData
//se le da el nuevo valor de newData, es decir en resumen hace un copiado completo del nodo.
//Y por ultimo cuenta cuantos nodos poseen el mismo valor de newData y dicha cantidad se utiliza para actualizar
//la cantidad de referencias de los nodos con esa newData.
template <typename T>
void LinkedList<T>::copyData(T* newData, T* oldData){
    Node<T>* temp = head;
    Node<T>* temp2 = head;
    int id;
    while(temp != nullptr){
        if(temp->getMemDir() == newData){
            while(temp2->getMemDir()!=oldData){
                temp2 = temp2->getNext();
            }
            id = temp->getID();
            temp2->setID(id);
            temp2->setData(newData);
            break;
        }
        temp = temp->getNext();
    }
    int cantRef = this->cantRef(newData);
    updateCanRef(newData,cantRef);
}

//elimina un nodo que posea el dato removeData y al finalizar hace un conteo de cuales nodos poseen removeDate
//y actualiza la cantidad de referencias de esos nodos.
template <typename T>
void LinkedList<T>::deleteRef(T* removeData){
    auto* temp = new Node<T>;
    temp = this->head;
    if(temp->getMemDir()==removeData){
        if(temp->getReferences() == 1){
            temp->setReferences(0);
            return;
        }
        else {
            head = temp->getNext();
            size--;
            delete(temp);
            int cantRef = this->cantRef(removeData);
            updateCanRef(removeData,cantRef);
        }
    }
    else {
        while (temp != nullptr) {
            if (temp->getNext() == this->tail && temp->getNext()->getMemDir() == removeData) {
                if(temp->getNext()->getReferences()==1){
                    temp->getNext()->setReferences(0);
                    break;
                }
                this->tail = temp;
                tail->setNext(temp->getNext()->getNext());
                size--;
                int cantRef = this->cantRef(removeData);
                updateCanRef(removeData,cantRef);
                break;
            }
            if (temp->getNext()->getMemDir() == removeData) {
                if(temp->getNext()->getReferences()==1){
                    temp->getNext()->setReferences(0);
                    break;
                }
                temp->setNext(temp->getNext()->getNext());
                size--;
                int cantRef = this->cantRef(removeData);
                updateCanRef(removeData,cantRef);
                break;
            }
            temp = temp->getNext();
        }
    }
}

//devuelve un int que indica la cantidad de nodos que poseen el valor de data
template <typename T>
int LinkedList<T>::cantRef(T *data) {
    Node<T>* temp = head;
    int ref=0;
    while(temp != nullptr){
        if(temp->getMemDir() == data){
            ref++;
        }
        temp = temp->getNext();
    }
    return ref;
}

//actualiza la cantidad de referencias que tiene cada nodo
//es decir si hay 3 nodos con el valor de data entonces a cada uno de esos nodos
//se le asigna el valor de 3 referencias
template <typename T>
void LinkedList<T>::updateCanRef(T* data, int cantData){
    Node<T>* temp = head;
    while(temp != nullptr){
        if(temp->getMemDir() == data){
            temp->setReferences(cantData);
        }
        temp = temp->getNext();
    }
}

template <typename T>
void LinkedList<T>::freeMemory(){
    Node<T>* temp = head;
    if(temp->getReferences()==0){
        delete (temp->getMemDir());
        head = temp->getNext();
        delete(temp);
        size--;
        return;
    }
    else {
        while (temp->getNext()!= nullptr) {
            if (temp->getNext()->getReferences() == 0) {
                delete temp->getNext()->getMemDir();
                temp->setNext(temp->getNext()->getNext());
                delete(temp);
                size--;
                break;
            }
            temp = temp->getNext();
        }
    }
}

#endif //VSPOINTER_LINKEDLIST_H
