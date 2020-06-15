/**
 * @file ClientApp.h
 * @brief Handles messages from/to the server
 * @author Joseph Jimenez
 * @version 2.0
 */
#ifndef CLIENTSIDE_CLIENTAPP_H
#define CLIENTSIDE_CLIENTAPP_H
#include "network/ConnectServer.h"
#include "JSON/jsonSerialize.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
class ClientApp : public ConnectServer{
public:
    ClientApp(const char* ipAddress, int port) : ConnectServer(ipAddress, port) { }
    /** @brief run handles connection with client
      * @return Successful state
      * When the server's init, will try to accepts the connection
      * and try to handle the bytes incoming
      */
    int run();
    bool running=true;
    std::string password="password";
    std::string Data;
    std::string ID;
    /**
    * @brief connectServer begins conection
    * @param IP
    * @param Port
    */
    static int connectServer(const char *IP, int Port );
protected:
    /**
     * @brief onMessageReceived handles all the messages from server
     * @param serverSocket
     * @param msg
     * @param length
     */
    virtual int onMessageReceived(int serverSocket, const char* msg, int length);
    /**
     * @brief handle sending Password;
     * @param serverSocket
     */
    virtual int sendPassword(int serverSocket);
    /**
     * SendsID to the server
     * @param serverSocket
     */
    virtual int sendID(int serverSocket);
    /**
     * Sends Data to the server
     * @param serverSocket
     */
    virtual int sendData(int serverSocket);
};
#endif //CLIENTSIDE_CLIENTAPP_H
