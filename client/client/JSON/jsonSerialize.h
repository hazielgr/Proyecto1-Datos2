#ifndef LABBING_JSONSERIALIZE_H
#define LABBING_JSONSERIALIZE_H
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "../VsPointer.h"
/**
 * @file jsonSerialize.h
 * @class jsonSerialize
 * @brief for json structure on Client
 * @author Joseph Jimenez
 * @version 3.0
 */
class jsonSerialize{
public:
    static bool create_Object(std::string DataType, std::string Data, std::string ID, std::string References);
    static bool deCode(std::string giveMeString);
    static std::string enCode(VsPointer<string> pointer);
    static std::string enCode(VsPointer<int> pointer);
    static std::string enCode(VsPointer<bool> pointer);
};

#endif //LABBING_JSONSERIALIZE_H
