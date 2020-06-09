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
    std::string confirm = "Connected Successful, I can read your messages \r\n";
    std::string password="password";
    std::string Data="{ \"ID\": [{\"ReferencesQuantity\": 1, \"DataType\":\"String\",\"Name\":\"Joseph\"}, {\"ReferencesQuantity\": 2, \"DataType\":\"Int\",\"Data\":\"89\"} ]}";
    std::string ID="00001";
    static int connectServer(const char *IP, int Port );
protected:
    // Handler for when a message is received from the server
    virtual int onMessageReceived(int serverSocket, const char* msg, int length);
    //Handles sending messages
    virtual int sendPassword(int serverSocket);
    virtual int sendConfirm(int serverSocket);
    virtual int sendID(int serverSocket);
    virtual int sendData(int serverSocket, const char *i);
};
#endif //CLIENTSIDE_CLIENTAPP_H
