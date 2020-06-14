/**
 * @file ServerApp.cpp
 * @brief Handling incoming connections messages
 * @author Joseph Jimenez
 * @version 3.0
 */
#include "ServerApp.h"
void start();
/** @brief handles connection with client
  * @return Successful state
  * When the server's init, will try to accepts the connection
  * and try to handle the bytes incoming
  */
int ServerApp::run() {
    bool security = true;
    bool running = true;
    while (running) {
        gbC = GarbageCollector::getInstance();
        thread thd(start);
        gbC->thrd.join();
        thd.join();
        int client = accept(m_socket, (struct sockaddr *) &client_addr, &clientSize);
        onClientConnected(client);
        int bytesReceived;
        do{
            char buffer[4096];
            memset(buffer, 0,4096);
            bytesReceived=recv(client,buffer, 4096,0);
            if(bytesReceived<0){
                close(m_socket);
                std::cout<< "Bytes Received Error";
            }else{
                if(security==true){
                    if(onPasswordReceived(client,buffer,bytesReceived)==1) {
                        security = false;
                    }else{}
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
/**
 * @brief If cant handle data, sus sendId back
 * @param clientSocket client connected
 */
void ServerApp::sendMessage(int clientSocket,const char* msg, int length) {
    sendToClient(clientSocket, msg, length + 1);
}
/**
 * @brief Sends a message with Data specified
 * @param clientSocket client connected
 */
void ServerApp::receivedID(int clientSocket) {
    sendToClient(clientSocket, Data.c_str(), Data.size() + 1);
}
/**
 * @brief Sends a message with ID generated
 * @param clientSocket client connected
 */
void ServerApp::receivedData(int clientSocket){
    std::string IDtoSend=to_string(ID);
    sendToClient(clientSocket, IDtoSend.c_str(),IDtoSend.size() + 1);
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
 * @brief Lools if it can finds an ID with that msg
 * @param msg
 */
bool ServerApp::isThisID(const char* msg){
    int dataInt=std::stoi( msg );
    if(gbC->intList.searchID(dataInt)){
        Data=jsonMachine::enCode(gbC->intList.getNodeID(dataInt));
        return true;
    }else if(gbC->stringList.searchID(dataInt)){
        Data= jsonMachine::enCode(gbC->stringList.getNodeID(dataInt));
        return true;
    }else if(gbC->boolList.searchID(dataInt)){
        Data=jsonMachine::enCode(gbC->boolList.getNodeID(dataInt));
        return true;
    }
    std::cout << "This is not an ID" << std::endl;
    return false;
}
bool ServerApp::isThisSerializable(const char *msg) {
    if(ID=jsonMachine::Deserialize(msg)){
        return true;
    }else{
        return false;
    }
}
/**
 * @brief handles Messages received by bytesReceived
 * @param clientSocket
 * @param msg
 * @param length
 */
int ServerApp::onMessageReceived(int clientSocket, const char* msg, int length) {
    if(isThisID(msg)){
        std::cout << "ID Recon"<< std::endl;
        receivedID(clientSocket);
        return 0;
    }else if(isThisSerializable(msg)) {
        std::cout << "Serializable Recon"<< std::endl;
        receivedData(clientSocket) ;
        return 0;
    }else{
        printf("-->%s\n", msg);
        sendMessage(clientSocket,msg,length);
        return 0;
    }
}


