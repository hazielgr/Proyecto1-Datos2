#ifndef CLIENTSIDE_CLIENTAPP_H
#define CLIENTSIDE_CLIENTAPP_H
#include "network/ConnectServer.h"
/**
 * @file ClientApp.h
 * @brief Handles messages from/to the server
 * @author Joseph Jimenez
 * @version 2.0
 */
class ClientApp : public ConnectServer{
public:
    ClientApp(const char* ipAddress, int port) : ConnectServer(ipAddress, port) { }
    int run();
    bool running=true;
    std::string password="password";
    std::string Data;
    std::string ID="00001";
    static int connectServer(const char *IP, int Port );
protected:
    // Handler for when a message is received from the server
    virtual int onMessageReceived(int serverSocket, const char* msg, int length);
    //Handles sending messages
    virtual int sendPassword(int serverSocket);
    virtual int sendID(int serverSocket);
    virtual int sendData(int serverSocket);
};
#endif //CLIENTSIDE_CLIENTAPP_H
