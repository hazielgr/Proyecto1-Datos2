#ifndef LABBING_JSONSERIALIZE_H
#define LABBING_JSONSERIALIZE_H
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "Nodo.h"
#include <iostream>
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
    static std::string enCode(Nodo<string>* nodo);
    static std::string enCode(Nodo<int>* nodo);
    static std::string enCode(Nodo<bool>* nodo);
};

#endif //LABBING_JSONSERIALIZE_H
