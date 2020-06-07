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
 * @version 1.0
 */
class jsonSerialize{
public:
    static void deCode(std::string giveMeString);
    static void enCode(VsPointer<string> pointer);
};

#endif //LABBING_JSONSERIALIZE_H
