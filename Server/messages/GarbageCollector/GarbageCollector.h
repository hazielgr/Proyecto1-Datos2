#ifndef GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#include "LinkedList.h"
#include <thread>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
class GarbageCollector {
private:
    static GarbageCollector *instance;
    GarbageCollector();
public:
    LinkedList<int> intList;
    LinkedList<string> stringList;
    LinkedList<bool> boolList;
    bool flag = false;
    static GarbageCollector *getInstance();
    void addToList(int *data);
    void addToList(string *data);
    void addToList(bool *data);
    void copyRef(string *newData, string *oldData);
    void copyRef(int *newData, int *oldData);
    void copyRef(bool *newData, bool *oldData);
    void deleteData(string *removeData);
    void deleteData(bool *removeData);
    void deleteData(int *removeData);
    thread thrd;
    int getDataID(bool* data);
    int getDataID(string* data);
    int getDataID(int* data);
};
#endif //GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
