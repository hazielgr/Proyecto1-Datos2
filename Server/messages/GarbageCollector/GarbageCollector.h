/**
 *  @file GarbageCollector.h
 *  @version 1.0
 *  @date 11/05/2020
 *  @author Mario Gudino
 *  @title Garbage Collector
 *  @brief Se ejecuta como hilo para buscar referencias que se dejan de usar y asi liberar memoria
 */

#ifndef GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#include "LinkedList.h"
#include <thread>
class GarbageCollector {
private:
    static GarbageCollector *instance;
    /**
     * @brief constructor de la clase Garbage Collector
     */
    GarbageCollector();
public:
    LinkedList<int> intList;
    LinkedList<string> stringList;
    LinkedList<bool> boolList;
    bool flag = false;
    /**
     * @brief getInstance Crea instancia singleton de GarbageCollector
     * @return Singleton de la clase
     */
    static GarbageCollector* getInstance();
    /**
     * @brief addToList Agrega nodo un nuevo nodo de tipo int
     * @param data
     */
    void addToList(int *data);
    /**
     * @brief addToList Agrega nodo un nuevo nodo de tipo string
     * @param data Puntero que se asigna al nuevo nodo como un dato
     */
    void addToList(string *data);
    /**
     * @brief addToList Agrega nodo un nuevo nodo de tipo bool
     * @param data Puntero que se asigna al nuevo nodo como un dato
     */
    void addToList(bool *data);
    /**
     * @brief copyRef Sustituye la informacion de un nodo por newData
     * @param newData Nueva data de tipo string puntero que se asigna al nodo
     * @param oldData Data string puntero que es sustituida por una nueva
     */
    void copyRef(string *newData, string *oldData);
    /**
     * @brief copyRef Sustituye la informacion de un nodo por newData
     * @param newData Nueva data de tipo int puntero que se asigna al nodo
     * @param oldData Data int puntero que es sustituida por una nueva
     */
    void copyRef(int *newData, int *oldData);
    /**
     * @brief copyRef Sustituye la informacion de un nodo por newData
     * @param newData Nueva data de tipo bool puntero que se asigna al nodo
     * @param oldData Data bool puntero que es sustituida por una nueva
     */
    void copyRef(bool *newData, bool *oldData);
    /**
     * @brief deleteData Remueve nodo que guarda un string* y elimina referencias de la lista
     * @param removeData
     */
    void deleteData(string *removeData);
    /**
     * @brief deleteData Remueve nodo que guarda un bool* y elimina referencias de la lista
     * @param removeData
     */
    void deleteData(bool *removeData);
    /**
     * @brief deleteData Remueve nodo queg guarda un int* y elimina referencias de la lista
     * @param removeData
     */
    void deleteData(int *removeData);
    thread thrd;
    /**
     * @brief getDataID Funcion que busca cual nodo tiene el puntero data y retorna el id de dicho nodo
     * @param data puntero bool el cual se utiliza para buscar el nodo
     * @return int que representa un id asiganado a un nodo especifico
     */
    int getDataID(bool* data);
    /**
     * @brief getDataID Funcion que busca cual nodo tiene el puntero data y retorna el id de dicho nodo
     * @param data puntero string el cual se utiliza para buscar el nodo
     * @return int que representa un id asiganado a un nodo especifico
     */
    int getDataID(string* data);
    /**
     * @brief getDataID Funcion que busca cual nodo tiene el puntero data y retorna el id de dicho nodo
     * @param data puntero int el cual se utiliza para buscar el nodo
     * @return int que representa un id asiganado a un nodo especifico
     */
    int getDataID(int* data);
};
#endif //GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
