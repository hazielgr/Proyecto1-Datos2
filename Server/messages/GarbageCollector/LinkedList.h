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
    void freeMemory();
    int getDataID(T* data);
};
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}
template <typename T>
void LinkedList<T>::addNode(T* n) {
    auto *temp = new Node<T>;
    if (typeid(T)== typeid(string)){
        temp->setDataType("string");
    }
    else if (typeid(T)== typeid(int)){
        temp->setDataType("int");
    }
    else if (typeid(T)== typeid(bool)){
        temp->setDataType("boolean");
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
template <typename T>
void LinkedList<T>::display(){
    Node<T>* temp = head;
    while(temp != nullptr){
        cout<<temp->getData()<<endl;
        temp = temp->getNext();
    }
}
template <typename T>
int LinkedList<T>::getSize(){
    return this->size;
}
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
template <typename T>
void LinkedList<T>::copyData(T* newData, T* oldData){
    Node<T>* temp = head;
    Node<T>* temp2 = head;
    while(temp != nullptr){
        if(temp->getMemDir() == newData){
            while(temp2->getMemDir()!=oldData){
                temp2 = temp2->getNext();
            }
            temp->setReferences(temp->getReferences()+1);
            if(temp2->getReferences()>1){
                temp->setReferences(temp->getReferences()-1);
            }
            else{
                temp2->setReferences(-1);
            }
            deleteRef(oldData);
            return;
        }
        temp = temp->getNext();
    }
}
template <typename T>
void LinkedList<T>::deleteRef(T* removeData){
    auto* temp = new Node<T>;
    temp = this->head;
    while(temp!=nullptr){
        if(temp->getMemDir() == removeData && temp->getReferences()>=1){
            temp->setReferences(temp->getReferences()-1);
            return;
        }
        temp = temp->getNext();
    }
    temp = this->head;
    if(temp->getMemDir()==removeData){
        temp = temp->getNext();
        head = temp;
    }
    else {
        while (temp != nullptr) {
            if (temp->getNext() == this->tail && temp->getNext()->getMemDir() == removeData) {
                this->tail = temp;
                tail->setNext(temp->getNext()->getNext());
                break;
            }
            if (temp->getNext()->getMemDir() == removeData) {
                temp->setNext(temp->getNext()->getNext());
                break;
            }
            temp = temp->getNext();
        }
    }
    size--;
}
template <typename T>
void LinkedList<T>::freeMemory(){
    Node<T>* temp = head;
    if(temp->getReferences()==0){
        delete (temp->getMemDir());
        head = temp->getNext();
        size--;
    }
    else {
        while (temp->getNext()!= nullptr) {
            if (temp->getNext()->getReferences() == 0) {
                delete (temp->getNext()->getMemDir());
                temp->setNext(temp->getNext()->getNext());
                size--;
                break;
            }
            temp = temp->getNext();
        }
    }
}
template <typename T>
int LinkedList<T>::getDataID(T* data){
    Node<T>* temp = head;
    while(temp!= nullptr){
        if(temp->getMemDir() == data){
            return temp->getID();
        }
        temp = temp->getNext();
    }
}
#endif //VSPOINTER_LINKEDLIST_H