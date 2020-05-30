#ifndef SERVERMEMORYMANAGER_SERVERAPP_H
#define SERVERMEMORYMANAGER_SERVERAPP_H
/**
 * @file ServerApp.h
 * @brief Handles messages out from the server
 * @author Joseph Jimenez
 * @version 1.0
 */
#pragma once
#include "../network/ServerListener.h"
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
    ServerApp(const char* ipAddress, int port) : ServerListener(ipAddress, port) { }
    int run();
    //Functions handling messages
protected:
    virtual int onMessageReceived(int clientSocket, const char* msg, int length);
    virtual void onClientConnected(int clientSocket);
};

#endif //SERVERMEMORYMANAGER_SERVERAPP_H
