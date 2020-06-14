#ifndef VSPOINTER_VSPOINTER_H
#define VSPOINTER_VSPOINTER_H
#include <iostream>
#include "../GarbageCollector/GarbageCollector.h"
template <typename T>
class VsPointer {
private:
    T* data;
public:
    static VsPointer<T> New();
    VsPointer& operator=(VsPointer<T> newData);
    VsPointer& operator=(T newData);
    T& operator*();
    T operator&();
    VsPointer();
    ~VsPointer();
    void deletePtr();
    T* getTdata();
};
template <class T>
VsPointer<T> VsPointer<T>::New() {
    return VsPointer();
}
template <class T>
VsPointer<T>::VsPointer() {
    this->data = new T;
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->addToList(this->data);
}
template <class T>
T& VsPointer<T>::operator*() {
    return *data;
}
template <typename T>
T VsPointer<T>::operator&() {
    return *data;
}
template <class T>
VsPointer<T>& VsPointer<T>::operator=(VsPointer<T> newData) {
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->copyRef(newData.data, this->data);
    this->data = newData.data;
}
template <class T>
VsPointer<T>& VsPointer<T>::operator=(T newData) {
    *this->data = newData;
}
template <typename T>
VsPointer<T>::~VsPointer() {
    /*
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->deleteData(this->data);
     */
}
template <typename T>
void VsPointer<T>::deletePtr() {
    GarbageCollector* gbC = GarbageCollector::getInstance();
    gbC->deleteData(this->data);
}
template <typename T>
T* VsPointer<T>::getTdata() {
    return this->data;
}
#endif //VSPOINTER_VSPOINTER_H
