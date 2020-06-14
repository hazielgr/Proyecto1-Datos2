#ifndef SERVERMEMORYMANAGER_SERVERAPP_H
#define SERVERMEMORYMANAGER_SERVERAPP_H
/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 3.0
 */
#pragma once
#include "../network/ServerListener.h"
#include "json/jsonMachine.h"
#include <crypto++/hex.h>
#include <crypto++/md5.h>
#include <string>
#include <vector>
#include <iterator>
/**
 * @class ServerApp
 * @brief Define specific answers to the client connected
 */
class ServerApp : public ServerListener{
public:
    ServerApp(const char* ipAddress, int port,const char* password ) : ServerListener(ipAddress, port, password) { }
    /**
     * @brief run handles server connection with client
     * @return Successful state
     * When the server's init, will try to accepts the connection
     * and try to handle the bytes incoming
     */
    int run();
    int ID;
    std::string Data ="Data No Parceable";
    std::string confirm = "Connected Successful, I can read your messages \r\n";
protected:
    /**
     * @brief isThisID Lools if it can finds an ID with that msg
     * @param msg
     */
    virtual bool isThisID(int dataInt);
    /**
     * @brief isThisSerializable Looks if it can serializable
     * @param msg
     */
    virtual bool isThisSerializable(const char* msg);
    /**
     * @brief onMessageReceived handles Messages received by bytesReceived
     * @param clientSocket
     * @param msg
     * @param length
     */
    virtual int onMessageReceived(int clientSocket, const char* msg, int length);
    /**
     * @brief onPasswordReceived Handles the login to the server
     * @param clientSocket
     * @param msg;
     * @param length;
     */
    virtual int onPasswordReceived(int clientSocket, const char* msg, int length);
    /**
     * @brief sendMessage If cant handle data, sus sendId back
     * @param clientSocket client connected
     */
    virtual void sendMessage(int clientSocket,const char* msg, int length);
    /**
     * @brief receivedData Sends a message with ID generated
     * @param clientSocket client connected
     */
    virtual void receivedData(int clientSocket);
    /**
     * @brief received ID Sends a message with Data specified
     * @param clientSocket client connected
     */
    virtual void receivedID(int clientSocket);
    /**
     * @brief onClientConnected Sends a message to verify connection
     * @param clientSocket client connected
     */
    virtual void onClientConnected(int clientSocket);
};
#endif //SERVERMEMORYMANAGER_SERVERAPP_H
