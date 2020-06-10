#include "jsonSerialize.h"
/**
 * @brief On this method can handle String with json structure
 * @param giveMeString
 * @version 2.0
 */
int jsonSerialize::deCode(std::string giveMeString) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( giveMeString, root );
    if ( !parsingSuccessful ){
        std::cout << "DataNoParceble" << std::endl;
        return 0;
    }
    //al parcear el mensaje recibido, se itera para obtener cada valor
    for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ ){
        for( Json::Value::const_iterator inner = (*outer).begin() ; inner!= (*outer).end() ; inner++ ){
            std::cout << inner.key() << ": " << *inner << std::endl;
        }
    }
    return 1;
}
/**
 *@brief this methods can receive a object Pointer
 *@param pointer
 * @version 1.0
 */
std::string jsonSerialize::enCode(VsPointer<string> pointer) {
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
std::string jsonSerialize::enCode(VsPointer<int> pointer) {
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
std::string jsonSerialize::enCode(VsPointer<bool> pointer) {
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

