/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 2.0
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
        //Conecta al Ciente
        int client = accept(m_socket, (struct sockaddr *) &client_addr, &clientSize);
        //Envia un mensaje que confirma comunicacion
        onClientConnected(client);
        //Al recibir un mensaje
        int bytesReceived;
        do{
            char buffer[4096];
            memset(buffer, 0,4096); //space for the bytes received
            bytesReceived=recv(client,buffer, 4096,0);
            //Si el mensaje es un error -1
            if(bytesReceived<0){
                close(m_socket);
                std::cout<< "Bytes Received Error";
            }else{
                //Un mensaje correcto procede a revisar si ya envio el password del server, sino pasa al manejador de mensajes
                if(security==true){
                    if(onPasswordReceived(client,buffer,bytesReceived)==1) {
                        security = false;
                        //Enviando mensaje de LogIn correcto
                        sendLoginOk(client);
                    }else{
                        //Enviando mensaje LogIn incorrecto
                        sendLoginBad(client);}
                }else{
                    onMessageReceived(client,buffer,bytesReceived);
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
void ServerApp::sendLoginOk(int clientSocket) {
    sendToClient(clientSocket, loginOk.c_str(), loginOk.size() + 1);
}
void ServerApp::sendLoginBad(int clientSocket) {
    sendToClient(clientSocket, loginBad.c_str(), loginBad.size() + 1);
}
void ServerApp::sendMessage(int clientSocket,const char* msg, int length) {
    sendToClient(clientSocket, msg, length + 1);
}
void ServerApp::receivedID(int clientSocket) {
    std::string message=Data;
    if(jsonMachine::Deserialize(Data)) {
        sendToClient(clientSocket, message.c_str(), message.size() + 1);
    }
}
void ServerApp::receivedData(int clientSocket){
    sendToClient(clientSocket, IDTest.c_str(), IDTest.size() + 1);
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
    std::string messageString= msg;
    //Al encontrar que pertene al grupo de IDs que tenemos
    if(messageString=="1"){
        //procedemos a buscar la data del ID y Enviarla
        std::cout << "ID Recon"<< std::endl;
        receivedID(clientSocket);
        return 0;
    //Si el mensaje esta en un formato JSON serializable
    }else if( jsonMachine::Deserialize(msg)) {
        //procedemos a deserealizar esa data, guardarla y enviar su ID
        std::cout << "Json Recon"<< std::endl;
        receivedData(clientSocket) ;
        return 0;
    }else{
        //Si recibe un mensaje que no es un ID o un tipo de mensaje Deserealizable, imprime y envia el mensaje recibido
        printf("-->%s\n", msg);
        sendMessage(clientSocket,msg,length);
        return 0;
    }
}


