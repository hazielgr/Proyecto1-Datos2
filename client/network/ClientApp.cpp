/**
 * @file ClientApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 1.0
 */
#include <iostream>
#include <cstring>
#include "ClientApp.h"
/** @brief handles connection with client
  * @return Successful state
  * When the server's init, will try to accepts the connection
  * and try to handle the bytes incoming
  */
int ClientApp::run() {
    bool running = true;
    while (running) {
        int connectResponse=connect(sock,(sockaddr*)&client_addr,sizeof(client_addr));
        if(connectResponse==-1)std::cerr<< "Error.Connecting server socket ";
        int bytesReceived;
        char buf[4096];
        std::string userInput;
        do{
            // Prompt the user for some text
            getline(std::cin, userInput);
            if (userInput.size() > 0) {
                // Send the text
                int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
                if (sendResult != -1){
                    memset(buf, 0,4096);
                    int bytesReceived = recv(sock, buf, 4096, 0);
                    if(bytesReceived > 0){
                        onMessageReceived(sock,buf,bytesReceived);
                    }
                }
            }

        } while (userInput.size() > 0);
        running=false;
    }
    return true;
}
int ClientApp::onMessageReceived(int serverSocket, const char* msg, int length) {
    std::cout << "SERVER> " << std::string(msg, 0, length+1) << std::endl;
    return 1;

}