#include <jsoncpp/json/json.h>
#include <iostream>
#include "jsonMachine.h"
/**
 * Reads from the string all the objects from jsonstring
 * @param giveMeString
 * @return
 */
bool jsonMachine::Deserialize(std::basic_string<char> giveMeString ){
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( giveMeString, root );
    if ( !parsingSuccessful ){
        std::cout << "Error parsing the string" << std::endl;
        return 0;
    }
    for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ ){
        for( Json::Value::const_iterator inner = (*outer).begin() ; inner!= (*outer).end() ; inner++ ){
            std::cout << inner.key() << ": " << *inner << std::endl;
        }
    }
    return 1;
}