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
#include "json/dataJsonClass.h"
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
    std::string IDTest="00001";
    dataJsonClass saveJsonData;
    std::string handledOk="We handled your info :) ";
    std::string handledBad="Data didn't do anything ";
    std::string loginOk="SERVER Password correct ";
    std::string loginBad="SERVER Password incorrect";
    std::string confirm = "Connected Successful, I can read your messages \r\n";
protected:
    // Handler for when a message is received from the client
    virtual int onMessageReceived(int clientSocket, const char* msg, int length);
    //Manage the Password Received
    virtual int onPasswordReceived(int clientSocket, const char* msg, int length);
    // Handler for client connections
    virtual void onClientConnected(int clientSocket);
};
#endif //SERVERMEMORYMANAGER_SERVERAPP_H