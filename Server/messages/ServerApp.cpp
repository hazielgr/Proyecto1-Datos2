/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 1.0
 */
#include <fstream>
#include "ServerApp.h"
#include "json/jsonMachine.h"
#include <crypto++/hex.h>
#include <crypto++/md5.h>

/** @brief handles connection with client
  * @return Successful state
  * When the server's init, will try to accepts the connection
  * and try to handle the bytes incoming
  */
int ServerApp::run() {
    bool security = true;
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
                if(!security==false){
                    if(onPasswordReceived(client,buffer,bytesReceived)) {
                        sendToClient(client, loginOk.c_str(), loginOk.size() + 1);
                        security = false;
                    }else{
                        std::cout << "WrongPassword" << std::endl;
                        sendToClient(client, loginBad.c_str(), loginBad.size() + 1);
                    }
                }else{
                    if(onMessageReceived(client,buffer,bytesReceived)){
                        sendToClient(client, handledOk.c_str(), handledOk.size() + 1);
                    }else{
                        sendToClient(client, handledBad.c_str(), handledBad.size() + 1);
                    }
                }
            }
        }while(bytesReceived>=0);
        close(client);
        running=false;
    }
}
/**
 * @brief Sends a message to verify connection
 * @param clientSocket client connected
 */
void ServerApp::onClientConnected(int clientSocket){
    sendToClient(clientSocket, confirm.c_str(), confirm.size() + 1);
}
/**
 * @brief Handles the login to the server
 * @param clientSocket
 * @param msg;
 * @param length;
 */
int ServerApp::onPasswordReceived(int clientSocket, const char* msg, int length) {
    CryptoPP::MD5 hashClient;
    CryptoPP::MD5 hashServer;
    byte digestClient[CryptoPP::MD5::DIGESTSIZE];
    byte digestServer[CryptoPP::MD5::DIGESTSIZE];
    std::string messageClient=msg;

    hashClient.CalculateDigest(digestClient,(byte*)messageClient.c_str(),messageClient.length());
    hashServer.CalculateDigest(digestServer,(byte*)m_password.c_str(),m_password.length());

    CryptoPP::HexEncoder encoderClient;
    CryptoPP::HexEncoder encoderServer;
    std::string md5Client;
    std::string md5Server;

    encoderClient.Attach(new CryptoPP::StringSink(md5Client));
    encoderClient.Put(digestClient,sizeof(digestClient));
    encoderClient.MessageEnd();

    encoderServer.Attach(new CryptoPP::StringSink(md5Server));
    encoderServer.Put(digestServer,sizeof(digestServer));
    encoderServer.MessageEnd();

    if (md5Client==md5Server){
        std::cout << "Password Works" << std::endl;
        return 1;
    }else{
        return 0;
    }
}
/**
 * @brief handles Messages received by bytesReceived
 * @param clientSocket
 * @param msg
 * @param length
 */

int ServerApp::onMessageReceived(int clientSocket, const char* msg, int length) {
    std::string messageString=msg;
    if(msg==IDTest){
        return 1;
    }else if( jsonMachine::Deserialize(&saveJsonData,messageString)) {
        return 1;
    }else{
        printf("-->%s\n", msg);
        return 0;
    }
}


/*
char *IP = inet_ntoa(client_addr.sin_addr);
    int Port = ntohs(client_addr.sin_port);*/
