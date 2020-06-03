#include "dataJsonClass.h"

dataJsonClass::dataJsonClass() {}
dataJsonClass::~dataJsonClass() throw(){}
void dataJsonClass::Serialize(Json::Value &root) {
    root["TypeOfData"]=m_TypeOfData;
    root["Data"]=m_DataValue;
}
void dataJsonClass::Deserialize(Json::Value &root) {
    m_DataValue=root.get("TypeOfData","").asString();
    m_DataValue=root.get("Data","").asString();
}

