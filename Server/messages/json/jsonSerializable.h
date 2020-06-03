#ifndef SERVERMEMORYMANAGER_JSONSERIALIZABLE_H
#define SERVERMEMORYMANAGER_JSONSERIALIZABLE_H

#include <jsoncpp/json/value.h>

class jsonSerializable {
public:
    virtual ~jsonSerializable(void) {};
    virtual void Serialize( Json::Value& root ) =0;
    virtual void Deserialize(Json::Value& root) =0;
};

#endif //SERVERMEMORYMANAGER_JSONSERIALIZABLE_H
