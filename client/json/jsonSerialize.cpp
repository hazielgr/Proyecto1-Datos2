#include "jsonSerialize.h"
/**
 * @brief On this method can handle String with json structure
 * @param giveMeString
 * @version 1.0
 */
void jsonSerialize::deCode(std::string giveMeString) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( giveMeString, root );
    if ( !parsingSuccessful ){
        std::cout << "Error parsing the string" << std::endl;
    }
    for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ ){
        for( Json::Value::const_iterator inner = (*outer).begin() ; inner!= (*outer).end() ; inner++ ){
            std::cout << inner.key() << ": " << *inner << std::endl;
        }
    }
}
/**
 *@brief this methods can receive a object Pointer
 *@param pointer
 * @version 1.0
 */
void jsonSerialize::enCode(VsPointer<string> pointer) {
    //"{ \"ID\": [{\"ReferencesQuantity\": 1, \"DataType\":\"String\",\"Name\":\"Joseph\"}, {\"ReferencesQuantity\": 2, \"DataType\":\"Int\",\"Data\":\"89\"} ]}";
    Json::Value save;
    save["ID"]="ID";
    save["Referencess"]=3;
    save["DataType"]=pointer.getType();
    save["Data"]=pointer.getData();
    Json::StyledWriter styledWriter;
    std::cout << styledWriter.write(save);
}
