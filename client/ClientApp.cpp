/**
 * @file ClientApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 2.0
 */
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "ClientApp.h"
#include "JSON/jsonSerialize.h"

/** @brief handles connection with client
  * @return Successful state
  * When the server's init, will try to accepts the connection
  * and try to handle the bytes incoming
  */
int ClientApp::run() {
    running = true;
    while (running) {
        int connectResponse=connect(sock,(sockaddr*)&client_addr,sizeof(client_addr));
        if(connectResponse==-1)std::cerr<< "Error.Connecting server socket ";
        int bytesReceived;
        char buf[4096];
        std::string userInput;
        do{
            sendPassword(sock);
            // Prompt the user for some text
            getline(std::cin, userInput);
            if (userInput.size() > 0) {
                // Send the text
                int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
                if (sendResult != -1){
                    memset(buf, 0,4096);
                    int bytesReceived = recv(sock, buf, 4096, 0);
                    if(bytesReceived > 0){
                        sendConfirm(sock);
                        onMessageReceived(sock,buf,bytesReceived);
                    }
                }
            }

        } while (userInput.size() > 0);
        running=false;
    }
    return true;
}
/**
 * @brief begins conection
 * @param IP
 * @param Port
 * @return
 */
int ClientApp::connectServer(const char *IP, int Port) {
    ClientApp clientApp(IP,Port);
    if(clientApp.init()!=0){
        clientApp.run();
    }
}
int ClientApp::sendPassword(int serverSocket) {
    sendToServer(serverSocket,password.c_str(),password.size()+1);
}
int ClientApp::sendConfirm(int serverSocket) {
    sendToServer(serverSocket,confirm.c_str(),confirm.size()+1);
}
int ClientApp::sendID(int serverSocket) {
    sendToServer(serverSocket,ID.c_str(),ID.size()+1);
}
int ClientApp::sendData(int serverSocket, const char *jsonData) {
    Data=jsonData;
    sendToServer(serverSocket,Data.c_str(),Data.size()+1);
}
/**
 *
 * @param serverSocket
 * @param msg
 * @param length
 */
int ClientApp::onMessageReceived(int serverSocket, const char* msg, int length) {
    std::string messageString=msg;
    if(msg==ID){
        sendID(serverSocket);
    }else if(msg=="2") {
        if(jsonSerialize::deCode(Data)) {
            sendData(serverSocket, msg);
            printf("DeCodeCool");
        }
    }else{
        printf("-->%s\n", msg);
        sendToServer(serverSocket, messageString.c_str(), messageString.size() + 1);
    }
}

