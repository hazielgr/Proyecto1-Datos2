/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 1.0
 */
#include <fstream>
#include "ServerApp.h"
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
                        sendToClient(client, loginBad.c_str(), loginBad.size() + 1);
                    }
                }else{}
                onMessageReceived(client,buffer,bytesReceived);
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
    }
}

