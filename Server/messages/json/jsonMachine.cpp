#include <sstream>
#include "jsonMachine.h"
/**
 * @brief this methods creates VsPointer Objects from messages
 * @param DataType
 * @param Data
 * @param ID
 * @param References
 * @return true if was ok creating the VsPointerObject
 * @version 2.0
 */
bool jsonMachine::create_Object(std::string DataType, std::string Data, std::string ID, std::string References) {
    if(DataType=="string"){
        VsPointer<string> myPtr = VsPointer<string>::New();
        *myPtr=Data;
        Id=gbC->getDataID(myPtr.getTdata());
        std::cout << "Created VSPointer<string>" << std::endl;
        return true;
    }else if(DataType=="int"){
        VsPointer<int> myPtr = VsPointer<int>::New();
        int dataInt=std::stoi( Data );
        *myPtr=dataInt;
        Id=gbC->getDataID(myPtr.getTdata());
        std::cout << "Creating VSPointer<int>" << std::endl;
        return true;
    }else if(DataType=="bool"){
        VsPointer<bool> myPtr = VsPointer<bool>::New();
        bool b;
        std::istringstream is(Data);
        is >> std::boolalpha >> b;
        *myPtr=b;
        Id=gbC->getDataID(myPtr.getTdata());
        std::cout << "Creating VSPointer<bool>" << std::endl;
        return true;
    }else {
        return false;
    }
}
/**
 * Reads On this method can handle String with json structure
 * @param giveMeString
 * @return true if could deserialize
 */
int jsonMachine::Deserialize(std::basic_string<char> giveMeString ) {
    Json::Value root;
    Json::Reader reader;
    std::cout << giveMeString << std::endl;
    bool parsingSuccessful = reader.parse(giveMeString.c_str(), root);
    if (!parsingSuccessful) {
        std::cout << "DataNoParceble" << std::endl;
        return 0;
    } else {
        for (Json::Value::const_iterator i = root.begin(); i != root.end(); i++) {
            std::string DataType = root["DataType"].asString();
            std::string Data = root["Data"].asString();
            std::string ID = root["ID"].asString();
            std::string References = root["References"].asString();
            if (jsonMachine::create_Object(DataType, Data, ID, References)) {
                return Id;
            } else {
                return 0;
            }
        }
    }
    return 0;
}
/**
 *@brief this methods receive a single pointer and return  string JSON
 *@param pointer receive a VsPointer<String>
 *@return output
 * @version 2.0
 */
std::string jsonMachine::enCode(Node<basic_string<char>>* nodo) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]=nodo->getID();
    save["References"]=nodo->getReferences();
    save["Data"]=nodo->getData();
    save["DataType"]=nodo->getDataType();
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(save);
    std::string output = fastWriter.write(save);
    std::cout<< output;
    return output;
}
/**
 *@brief this methods receive a single pointer and return  string JSON
 *@param pointer receive a VsPointer<int>
 *@return output
 * @version 2.0
 */
std::string jsonMachine::enCode(Node<int>* nodo) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]=nodo->getID();
    save["References"]=nodo->getReferences();
    save["Data"]=nodo->getData();
    save["DataType"]=nodo->getDataType();
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(save);
    std::string output = fastWriter.write(save);
    std::cout<< output;
    return output;
}
/**
 *@brief this methods receive a single pointer and return  string JSON
 *@param pointer receive a VsPointer<bool>
 *@return output
 * @version 2.0
 */
std::string jsonMachine::enCode(Node<bool>* nodo) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]=nodo->getID();
    save["References"]=nodo->getReferences();
    save["Data"]=nodo->getData();
    save["DataType"]=nodo->getDataType();
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(save);
    std::string output = fastWriter.write(save);
    std::cout<< output;
    return output;
}