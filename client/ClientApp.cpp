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
        //Inicia la conexion con el server
        int connectResponse=connect(sock,(sockaddr*)&client_addr,sizeof(client_addr));
        if(connectResponse==-1)std::cerr<< "Error.Connecting server socket ";
        int bytesReceived;
        char buf[4096];
        std::string userInput;
        do{
            //Enviamos el password directamente
            sendPassword(sock);
            // Prompt the user for some text
            getline(std::cin, userInput);
            //Mientras el usuario escriba y logre un input >0
            if (userInput.size() > 0) {
                // Send the text
                int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
                if (sendResult != -1){
                    memset(buf, 0,4096);
                    //Manejando las respuestas de los mensajes
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
//Estos manejan los mensajes que estamos enviando
int ClientApp::sendPassword(int serverSocket) {
    sendToServer(serverSocket,password.c_str(),password.size()+1);
}
int ClientApp::sendID(int serverSocket) {
    sendToServer(serverSocket,ID.c_str(),ID.size()+1);
}
int ClientApp::sendData(int serverSocket) {
    sendToServer(serverSocket,Data.c_str(),Data.size()+1);
}
/**
 *
 * @param serverSocket
 * @param msg
 * @param length
 */
int ClientApp::onMessageReceived(int serverSocket, const char* msg, int length) {
    //debido a que el server nos responde con lo que escribimos si no logra manejar el dato
    //En el caso de recibir un 1 se habilita el lograr probar enviar 1 ID
    if(msg=="1") {
        sendID(serverSocket);
        return 0;
        //En el caso de enviar un 2 podemos probar que pasa al Enviar un string con Data
    }else if(msg=="2"){
        sendData(serverSocket);
        return 0;
        //En el caso de recibir data en formato json
    }else if(jsonSerialize::deCode(msg)) {
        printf("DeCodeCool");
        sendData(serverSocket);
        return 0;
    }else{
        printf("-->%s\n", msg);
        return 0;
    }
}

