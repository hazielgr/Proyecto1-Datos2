#ifndef SERVERMEMORYMANAGER_JSONMACHINE_H
#define SERVERMEMORYMANAGER_JSONMACHINE_H
#include <jsoncpp/json/json.h>
#include <iostream>
#include <jsoncpp/json/value.h>
#include "VsPointer.h"
/**
 * @file jsonMachine.h
 * @brief Handles json changes
 * @author Joseph Jimenez
 * @version 2.0
 */
class jsonMachine{
public:
    static bool Deserialize(std::basic_string<char> giveMeStream );
    static std::string enCode(VsPointer<std::string> pointer);
    static std::string enCode(VsPointer<int> pointer);
    static std::string enCode(VsPointer<bool> pointer);
    static bool create_Object( std::string DataType, std::string Data,  std::string ID, std::string References);
private:
    jsonMachine(void){};
};
#endif //SERVERMEMORYMANAGER_JSONMACHINE_H
