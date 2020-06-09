/**
 * @file ServerListener.cpp
 * @brief Defining server Network's Layer
 * @author Joseph Jimenez
 * @version 1.0
 */
#include "ServerListener.h"
/** @brief Starts the server
  * @return m_socket the state of the socket
  * This method creates a socket to listen for incoming connections
  * needed to fill up the structure of the serverStructure
  */
int ServerListener::init(){
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket<=0) std::cerr << "ERROR. Can't create socket";
    //Filling Structure
    server_addr.sin_family= AF_INET;
    server_addr.sin_port= htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &server_addr.sin_addr);
    //Binding
    if(bind(m_socket,(struct sockaddr*) &server_addr, sizeof(server_addr)) ==-1)std::cerr << "ERROR. Can't bind to IP/PORT";
    //Listen
    if(listen(m_socket,SOMAXCONN)==-1) std::cerr<<"Can't Listen!";
    return m_socket;
}
/** @brief Sends message to client
  * @param clientSocket the client
  * @param msg the message
  * @param length size of message
  */
void ServerListener::sendToClient(int clientSocket, const char *msg, int length) {
    send(clientSocket, msg, length, 0);
}
void ServerListener::onClientConnected(int clientSocket){
}
void ServerListener::onMessageReceived(int clientSocket, const char* msg, int length){
}