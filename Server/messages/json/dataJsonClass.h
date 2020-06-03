#ifndef SERVERMEMORYMANAGER_DATAJSONCLASS_H
#define SERVERMEMORYMANAGER_DATAJSONCLASS_H
#include <string>
#include "jsonSerializable.h"

class dataJsonClass: public jsonSerializable{
public:
    dataJsonClass(void);
    virtual ~dataJsonClass(void);
    virtual void Serialize( Json::Value& root );
    virtual void Deserialize( Json::Value& root);

private:
    std::string m_TypeOfData;
    std::string m_DataValue;
};

#endif //SERVERMEMORYMANAGER_DATAJSONCLASS_H
