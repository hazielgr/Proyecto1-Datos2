/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 1.0
 */
#include <fstream>
#include "ServerApp.h"

/** @brief handles connection with client
  * @return Successful state
  * When the server's init, will try to accepts the connection
  * and try to handle the bytes incoming
  */
int ServerApp::run() {
    bool running = true;
    while (running) {
        int client = accept(m_socket, (struct sockaddr *) &client_addr, &clientSize); //Accepts client and keeps his info
        onClientConnected(client);
        int bytesReceived;
        do{
            char buffer[4096];
            memset(buffer, 0,4096); //space for the bytes received
            bytesReceived=recv(client,buffer, 4096,0);
            if(bytesReceived<0){
                close(m_socket);
                std::cout<< "Bytes Received Error";
            }else{
                onMessageReceived(client,buffer,bytesReceived);
            }
        }while(bytesReceived>=0);
        close(client);
        running=false;
    }
}
/**
 * @brief Throws a message to verify connection
 * @param clientSocket client connected
 */

void ServerApp::onClientConnected(int clientSocket){
    std::string confirm = "AlreadyReceivedYourMessage\r\n";
    sendToClient(clientSocket, confirm.c_str(), confirm.size() + 1);
}
/**
 * @brief handles Messages received by bytesReceived
 * @param clientSocket
 * @param msg
 * @param length
 */
int ServerApp::onMessageReceived(int clientSocket, const char* msg, int length) {
    std::string test = "test\r\n";
    sendToClient(clientSocket, test.c_str(), test.size() + 1);
}


