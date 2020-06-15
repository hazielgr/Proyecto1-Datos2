/**
 * @file ServerListener.h
 * @brief Handles client Behavior
 * @author Joseph Jimenez
 * @version 1.0
 */
#ifndef CLIENTSIDE_CONNECTSERVER_H
#define CLIENTSIDE_CONNECTSERVER_H
#include <string>
#include <arpa/inet.h>
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
    /**
     * @brief init Starts the client info
     * @return m_socket the state of the socket
     * This method creates a socket to listen for incoming connections
     * needed to fill up the structure of the serverStructure
     */
    int init();
    /** @brief Sends message to server
      * @param serverSocket the client
      * @param msg the message
      * @param length size of message
      */
    void sendToServer(int serverSocket, const char* msg, int length);
    void onMessageReceived(int serverSocket, const char* msg, int length);
private:
    std::string           m_ipAddress;        /// IPAddress of server="127.0.0.1"
    int                   m_port;             /// Port for server use= 54000
protected:
    int                   sock;
    sockaddr_in           client_addr;
};
#endif //CLIENTSIDE_CONNECTSERVER_H
