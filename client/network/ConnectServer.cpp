/**
 * @file ServerListener.cpp
 * @brief Defining Client Network's Layer
 * @author Joseph Jimenez
 * @version 1.0
 */
#include <arpa/inet.h>
#include "ConnectServer.h"
/** @brief Starts the client info
  * @return m_socket the state of the socket
  * This method creates a socket to listen for incoming connections
  * needed to fill up the structure of the serverStructure
  */
int ConnectServer::init() {
    sock= socket( AF_INET, SOCK_STREAM,0);
    // Create a hint structure for the server we are connecting it
    client_addr.sin_family=AF_INET;
    client_addr.sin_port= htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &client_addr.sin_addr);
    return sock;
}
/** @brief Sends message to server
  * @param serverSocket the client
  * @param msg the message
  * @param length size of message
  */
void ConnectServer::sendToServer(int serverSocket, const char *msg, int length) {
    send(serverSocket, msg, length, 0);
}
void ConnectServer::onMessageReceived(int serverSocket, const char* msg, int length){
}
