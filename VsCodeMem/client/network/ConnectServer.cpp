#include "ConnectServer.h"
int ConnectServer::init() {
    sock= socket( AF_INET, SOCK_STREAM,0);
    // Create a hint structure for the server we are connecting it
    client_addr.sin_family=AF_INET;
    client_addr.sin_port= htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &client_addr.sin_addr);
    return sock;
}
void ConnectServer::sendToServer(int serverSocket, const char *msg, int length) {
    send(serverSocket, msg, length, 0);
}
void ConnectServer::onMessageReceived(int serverSocket, const char* msg, int length){
}
