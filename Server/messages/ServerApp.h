#ifndef SERVERMEMORYMANAGER_SERVERAPP_H
#define SERVERMEMORYMANAGER_SERVERAPP_H
/**
 * @file ServerApp.h
 * @brief Handles messages out from the server
 * @author Joseph Jimenez
 * @version 2.0
 */
#pragma once
#include "../network/ServerListener.h"
#include "json/jsonMachine.h"
#include <fstream>
#include <crypto++/hex.h>
#include <crypto++/md5.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

/**
 * @class ServerApp
 * @brief Define specific answers to the client connected
 */
class ServerApp : public ServerListener{
public:
    ServerApp(const char* ipAddress, int port,const char* password ) : ServerListener(ipAddress, port, password) { }
    int run();
    int ID;
    std::string Data;
    GarbageCollector* gbC;
    std::string confirm = "Connected Successful, I can read your messages \r\n";
protected:
    virtual bool isThisID(const char* msg);
    virtual bool isThisSerializable(const char* msg);
    virtual int onMessageReceived(int clientSocket, const char* msg, int length);
    virtual int onPasswordReceived(int clientSocket, const char* msg, int length);
    virtual void sendMessage(int clientSocket,const char* msg, int length);
    virtual void receivedData(int clientSocket);
    virtual void receivedID(int clientSocket);
    virtual void onClientConnected(int clientSocket);
};
#endif //SERVERMEMORYMANAGER_SERVERAPP_H
