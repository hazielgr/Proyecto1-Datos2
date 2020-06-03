#ifndef SERVERMEMORYMANAGER_JSONMACHINE_H
#define SERVERMEMORYMANAGER_JSONMACHINE_H
#include "jsonSerializable.h"

class jsonMachine{
public:
    static bool Serialize(jsonSerializable* pointObj, std::string& giveMeObj);
    static bool Deserialize(jsonSerializable* pointObj, std::string& giveMeStream );
private:
    jsonMachine(void){};
};
#endif //SERVERMEMORYMANAGER_JSONMACHINE_H
