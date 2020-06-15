#ifndef VSCODEMEM_JSONSERIALIZE_H
#define VSCODEMEM_JSONSERIALIZE_H
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "../../GarbageCollector/Node.h"
#include "../../GarbageCollector/GarbageCollector.h"
#include "../../VsPtr/VsPointer.h"

/**
 * @file jsonSerialize.h
 * @class jsonSerialize
 * @brief for json structure on Client
 * @author Joseph Jimenez
 * @version 3.0
 */
class jsonSerialize{
public:
    /**
     * @brief create_Object this methods creates VsPointer Objects from messages
     * @param DataType
     * @param Data
     * @param ID
     * @param References
     * @return true if was ok creating the Object
     * @version 3.0
     */
    static bool create_Object(std::string DataType, std::string Data, std::string ID, std::string References);
    /**
    * @brief On this method can handle String with json structure
    * @param giveMeString
    * @version 3.0
    */
    static bool deCode(std::string giveMeString);
    /**
    * @brief this methods receive a single node and return  string JSON
    * @param pointer receive a Nodo<string>* nodo
    * @return output
    * @version 3.0
    */
    static std::string enCode(Node<string>* nodo);
    /**
    * @brief this methods receive a single node and return  string JSON
    * @param pointer receive a Nodo<int>* nodo
    * @return output
    * @version 3.0
    */
    static std::string enCode(Node<int>* nodo);
    /**
    * @brief this methods receive a single node and return  string JSON
    * @param pointer receive a Nodo<bool>* nodo)
    * @return output
    * @version 3.0
    */
    static std::string enCode(Node<bool>* nodo);
};

#endif //LABBING_JSONSERIALIZE_H
