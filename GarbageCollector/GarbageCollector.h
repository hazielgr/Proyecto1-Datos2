//
// Created by haziel on 3/6/20.
//

#ifndef GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_GARBAGECOLLECTOR_H


#include "../VsPtr/LinkedList.h"
#include <thread>

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
};
#endif //GARBAGECOLLECTOR_GARBAGECOLLECTOR_H