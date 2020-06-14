//
// Created by haziel on 3/6/20.
//

#include <iostream>
#include <thread>
#include <unistd.h>
#include "GarbageCollector.h"

using namespace std;

void run();
GarbageCollector* GarbageCollector::instance = 0;

GarbageCollector::GarbageCollector(){
    this->flag = true;
    this->thrd = thread(run);
}

GarbageCollector* GarbageCollector::getInstance(){
    if (instance == 0)
    {
        instance = new GarbageCollector();

    }
    return instance;
}

void GarbageCollector::addToList(int* data) {
    this->intList.addNode(data);
}

void GarbageCollector::addToList(string* data) {
    this->stringList.addNode(data);
}

void GarbageCollector::addToList(bool* data) {
    this->boolList.addNode(data);
}

void GarbageCollector::copyRef(int* newData, int* oldData) {
    this->intList.copyData(newData,oldData);
}
void GarbageCollector::copyRef(string* newData, string* oldData) {
    this->stringList.copyData(newData,oldData);
}
void GarbageCollector::copyRef(bool* newData, bool* oldData) {
    this->boolList.copyData(newData,oldData);
}

void GarbageCollector::deleteData(int* removeData) {
    this->intList.deleteRef(removeData);
}

void GarbageCollector::deleteData(string* removeData) {
    this->stringList.deleteRef(removeData);
}

void GarbageCollector::deleteData(bool* removeData) {
    this->boolList.deleteRef(removeData);
}
void run() {
    GarbageCollector *gbc = GarbageCollector::getInstance();
    while (gbc->flag) {
        if (gbc->stringList.getSize()!= 0) {
            gbc->stringList.freeMemory();
        }
        if(gbc->intList.getSize()!=0){
            gbc->intList.freeMemory();
        }
        if(gbc->boolList.getSize()!=0){
            gbc->boolList.freeMemory();
        }
        //cout<<"liberando memoria"<<endl;
        sleep(static_cast<unsigned int>(0.3));
    }
}

int GarbageCollector::getDataID(bool* data) {
    return this->boolList.getDataID(data);
}

int GarbageCollector::getDataID(string* data) {
    return this->stringList.getDataID(data);
}

int GarbageCollector::getDataID(int* data) {
    return this->intList.getDataID(data);
}

bool GarbageCollector::searchID(int data) {
    if(intList.searchID(data)){
        return true;
    }
    else if(stringList.searchID(data)){
        return true;
    }
    else return boolList.searchID(data);
}

