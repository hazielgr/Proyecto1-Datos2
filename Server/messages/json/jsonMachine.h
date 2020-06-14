#ifndef SERVERMEMORYMANAGER_JSONMACHINE_H
#define SERVERMEMORYMANAGER_JSONMACHINE_H
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include "../GarbageCollector/VsPointer.h"
#include "../GarbageCollector/GarbageCollector.h"
/**
 * @file jsonMachine.h
 * @brief Handles json changes
 * @author Joseph Jimenez
 * @version 3.0
 */
class jsonMachine{
public:
    static GarbageCollector* gbC;
    static int Id;
    static int Deserialize(std::basic_string<char> giveMeStream );
    static std::string enCode(Node<basic_string<char>>* nodo);
    static std::string enCode(Node<int>* nodo);
    static std::string enCode(Node<bool>* nodo)  ;
    static bool create_Object(std::string DataType, std::string Data, std::string ID, std::string References);
private:
    jsonMachine(void){};
};
#endif //SERVERMEMORYMANAGER_JSONMACHINE_H
