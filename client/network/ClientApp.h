#ifndef CLIENTSIDE_CLIENTAPP_H
#define CLIENTSIDE_CLIENTAPP_H
#include "ConnectServer.h"
/**
 * @file ClientApp.h
 * @brief Handles messages to the server and read his answer
 * @author Joseph Jimenez
 * @version 1.0
 */
class ClientApp : public ConnectServer{
public:
    ClientApp(const char* ipAddress, int port) : ConnectServer(ipAddress, port) { }
    int run();
protected:
    // Handler for when a message is received from the client
    virtual int onMessageReceived(int clientSocket, const char* msg, int length);
};

#endif //CLIENTSIDE_CLIENTAPP_H
