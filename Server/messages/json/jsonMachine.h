#ifndef SERVERMEMORYMANAGER_JSONMACHINE_H
#define SERVERMEMORYMANAGER_JSONMACHINE_H
#include "jsonSerializable.h"

/**
 * @file jsonMachine.h
 * @brief Handles json changes
 * @author Joseph Jimenez
 * @version 2.0
 */
class jsonMachine{
public:
    static bool Deserialize(std::basic_string<char> giveMeStream );
    static Json::Value saveJsonData;

private:
    jsonMachine(void){};
};
#endif //SERVERMEMORYMANAGER_JSONMACHINE_H
