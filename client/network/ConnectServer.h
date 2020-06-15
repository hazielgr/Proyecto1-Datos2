/**
 * @file ServerListener.h
 * @brief Handles client Behavior
 * @author Joseph Jimenez
 * @version 1.0
 */
#ifndef CLIENTSIDE_CONNECTSERVER_H
#define CLIENTSIDE_CONNECTSERVER_H

#include <string>
#include <netinet/in.h>
class ConnectServer;
/**
 * Building the client
 * @param ipAddress
 * @param port
 */
class ConnectServer{
public:
    ConnectServer(const char* ipAddress, int port) : m_ipAddress(ipAddress), m_port(port) { }
    int init();
    void sendToServer(int serverSocket, const char* msg, int length);
    void onMessageReceived(int serverSocket, const char* msg, int length);
private:
    /// Handles Client sockets structure
    std::string           m_ipAddress;        /// IPAddress of server="127.0.0.1"
    int                   m_port;             /// Port for server use= 54000
protected:
    int                   sock;
    sockaddr_in           client_addr;
};

#endif //CLIENTSIDE_CONNECTSERVER_H
