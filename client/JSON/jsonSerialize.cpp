#include <sstream>
#include "jsonSerialize.h"

/**
 * @brief this methods creates VsPointer Objects from messages
 * @param DataType
 * @param Data
 * @param ID
 * @param References
 * @return true if was ok creating the Object
 * @version 3.0
 */
bool jsonSerialize::create_Object(std::string DataType, std::string Data, std::string ID, std::string References) {
    if(DataType=="string"){
        Nodo<string>* nodo;
        int IDInt=std::stoi(ID);
        int ReferencesInt=std::stoi(References);
        nodo->setDataType(DataType);
        //nodo->setData(DataString);
        nodo->setID(IDInt);
        nodo->setReferences(ReferencesInt);
        std::cout << "Created Nodo<string>*" << std::endl;
    }else if(DataType=="int"){
        Nodo<int>* nodo;
        int *DataInt= reinterpret_cast<int *>(std::stoi(Data));
        int IDInt=std::stoi(ID);
        int ReferencesInt=std::stoi(References);
        nodo->setDataType(DataType);
        nodo->setData(DataInt);
        nodo->setID(IDInt);
        nodo->setReferences(ReferencesInt);
        std::cout << "Creating VSPointer<int>" << std::endl;
    }else if(DataType=="bool"){
        Nodo<bool>* nodo;
        bool b;
        std::istringstream is(Data);
        is >> std::boolalpha >> b;
        int IDInt=std::stoi(ID);
        int ReferencesInt=std::stoi(References);
        nodo->setDataType(DataType);
        nodo->setData(reinterpret_cast<bool *>(b));
        nodo->setID(IDInt);
        nodo->setReferences(ReferencesInt);
        std::cout << "Creating VSPointer<bool>" << std::endl;
    }else{
        return false;
    }
    return true;

}
/**
 * @brief On this method can handle String with json structure
 * @param giveMeString
 * @version 3.0
 */
bool jsonSerialize::deCode(std::string giveMeString) {
    Json::Value root;
    Json::Reader reader;
    std::cout<< giveMeString<< std::endl;
    bool parsingSuccessful = reader.parse( giveMeString.c_str(), root );
    if ( !parsingSuccessful ){
        std::cout << "DataNoParceble" << std::endl;
        return 0;
    }else {
        for(Json::Value::const_iterator i = root.begin(); i!= root.end(); i++)  {
            std::string DataType = root["DataType"].asString();
            std::string Data = root["Data"].asString();
            std::string ID = root["ID"].asString();
            std::string References = root["References"].asString();
            if(create_Object(DataType,Data,ID,References)){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}
/**
 *@brief this methods receive a single node and return  string JSON
 *@param pointer receive a Nodo<string>* nodo
 *@return output
 * @version 2.0
 */
std::string jsonSerialize::enCode(Nodo<string>* nodo) {
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
 *@brief this methods receive a single node and return  string JSON
 *@param pointer receive a Nodo<int>* nodo
 *@return output
 * @version 2.0
 */
std::string jsonSerialize::enCode(Nodo<int>* nodo) {
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
 *@brief this methods receive a single node and return  string JSON
 *@param pointer receive a Nodo<bool>* nodo)
 *@return output
 * @version 2.0
 */
std::string jsonSerialize::enCode(Nodo<bool>* nodo) {
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

