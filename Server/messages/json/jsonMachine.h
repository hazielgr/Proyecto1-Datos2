/**
 * @file jsonMachine.h
 * @brief Handles json changes
 * @author Joseph Jimenez
 * @version 3.0
 */
#ifndef SERVERMEMORYMANAGER_JSONMACHINE_H
#define SERVERMEMORYMANAGER_JSONMACHINE_H
#include <sstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include "../GarbageCollector/VsPointer.h"
#include "../GarbageCollector/GarbageCollector.h"
class jsonMachine{
public:
    /**
     * @brief Deserealize Reads On this method can handle String with json structure
     * @param giveMeString
     * @return true if could deserialize
     */
    static int Deserialize(std::basic_string<char> giveMeStream );
    /**
     *@brief enCode this methods receive a single pointer and return  string JSON
     *@param pointer receive a VsPointer<String>
     *@return output
     *@version 2.0
     */
    static std::string enCode(Node<basic_string<char>>* nodo);
    /**
     *@brief enCode this methods receive a single pointer and return  string JSON
     *@param pointer receive a VsPointer<int>
     *@return output
     *@version 2.0
     */
    static std::string enCode(Node<int>* nodo);
    /**
     *@brief enCode this methods receive a single pointer and return  string JSON
     *@param pointer receive a VsPointer<bool>
     *@return output
     *@version 2.0
     */
    static std::string enCode(Node<bool>* nodo);
    /**
     * @brief create_Object this methods creates VsPointer Objects from messages and loads it to garbageC
     * @param DataType
     * @param Data
     * @param ID
     * @param References
     * @return true if was ok creating the VsPointerObject
     * @version 2.0
     */
    static bool create_Object(std::string DataType, std::string Data, std::string ID, std::string References);
};
#endif //SERVERMEMORYMANAGER_JSONMACHINE_H
