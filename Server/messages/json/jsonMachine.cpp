//
// Created by heineken97 on 3/6/20.
//
#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include "jsonMachine.h"
bool jsonMachine::Serialize(jsonSerializable* pObj, std::string& giveMeObj ){
    if (pObj == NULL){
        std::cout<< "No serializable obj" <<std::endl;
        return false;
    }
    Json::Value serializeRoot;
    pObj->Serialize(serializeRoot);
    Json::StyledWriter writer;
    giveMeObj = writer.write( serializeRoot );
    return true;
}
bool jsonMachine::Deserialize(jsonSerializable* pObj, std::string& giveMeStream ){
    if (pObj == NULL) {
        std::cout<< "No serializable obj" <<std::endl;
        return false;
    }
    Json::Value deserializeRoot;
    Json::Reader reader;
    if (!reader.parse(giveMeStream, deserializeRoot) ) {
        return false;
    }
    pObj->Deserialize(deserializeRoot);
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, deserializeRoot);

    std::ofstream saveFile("savedString.txt");
    if (!saveFile) {
        std::cerr<<"Error creating a File.."<<std::endl;
    }else{
        saveFile << json_file;
    }
    return true;

}