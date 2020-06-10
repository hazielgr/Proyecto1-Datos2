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
        //Creamos Pointers de prueba para enviar la Data
        std::string userInput;
        VsPointer<string> myPtr = VsPointer<string>::New();
        *myPtr = "Haziel";
        std::string pointerOne =jsonSerialize::enCode(myPtr);
        //Enviamos el password directamente
        sendPassword(sock);
        do{
            Data= pointerOne;
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
    return 0;
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
    //Funcion de prueba enviar ID, habilitar al cliente enviado
    if(msg=="1") {
        sendID(serverSocket);
        return 0;
        //Funcion de prueba enviar Data, habilitar al cliente enviado
    }else if(msg=="2"){
        sendData(serverSocket);
        return 0;
    }else if(jsonSerialize::deCode(msg)) {
        printf("I can decode you JSON");
        return 1;
    }else{
        printf("-->This is your ID:%s\n", msg);
        return 1;
    }
}

