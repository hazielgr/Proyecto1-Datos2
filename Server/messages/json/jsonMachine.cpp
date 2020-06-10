#include <sstream>
#include "jsonMachine.h"
/**
 * @brief this methods creates VsPointer Objects from messages
 * @param DataType
 * @param Data
 * @param ID
 * @param References
 * @return true if was ok creating the Object
 * @version 1.0
 */
bool jsonMachine::create_Object(std::string DataType, std::string Data, std::string ID, std::string References) {
    if(DataType=="string"){
        VsPointer<string> myPtr = VsPointer<string>::New();
        *myPtr=Data;
        std::cout << myPtr.getData() << std::endl;
        std::cout << myPtr.getType() << std::endl;
        std::cout << "Created VSPointer<string>" << std::endl;
    }else if(DataType=="int"){
        VsPointer<int> myPtr = VsPointer<int>::New();
        int dataInt=std::stoi( Data );
        *myPtr=dataInt;
        std::cout << myPtr.getData() << std::endl;
        std::cout << myPtr.getType() << std::endl;
        std::cout << "Creating VSPointer<int>" << std::endl;
    }else if(DataType=="bool"){
        VsPointer<bool> myPtr = VsPointer<bool>::New();
        bool b;
        std::istringstream is(Data);
        is >> std::boolalpha >> b;
        *myPtr=b;
        std::cout << myPtr.getData() << std::endl;
        std::cout << myPtr.getType() << std::endl;
        std::cout << "Creating VSPointer<bool>" << std::endl;
    }else{
        return false;
    }
    return true;
}
/**
 * Reads On this method can handle String with json structure
 * @param giveMeString
 * @return true if could deserialize
 */
bool jsonMachine::Deserialize(std::basic_string<char> giveMeString ){
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
 *@brief this methods receive a single pointer and return  string JSON
 *@param pointer receive a VsPointer<String>
 *@return output
 * @version 1.0
 */
std::string jsonMachine::enCode(VsPointer<string> pointer) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]="ID";
    save["Referencess"]=3;
    save["DataType"]=pointer.getType();
    save["Data"]=pointer.getData();
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
 * @version 1.0
 */
std::string jsonMachine::enCode(VsPointer<int> pointer) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]="ID";
    save["Referencess"]=3;
    save["DataType"]=pointer.getType();
    save["Data"]=pointer.getData();
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
 * @version 1.0
 */
std::string jsonMachine::enCode(VsPointer<bool> pointer) {
    Json::Value save;
    Json::FastWriter fastWriter;
    save["ID"]="ID";
    save["Referencess"]=3;
    save["DataType"]=pointer.getType();
    save["Data"]=pointer.getData();
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(save);
    std::string output = fastWriter.write(save);
    std::cout<< output;
    return output;
}

