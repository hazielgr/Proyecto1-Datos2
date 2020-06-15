#include "ClientApp.h"
int ClientApp::run() {
    running = true;
    while (running) {
        int connectResponse=connect(sock,(sockaddr*)&client_addr,sizeof(client_addr));
        if(connectResponse==-1)std::cerr<< "Error.Connecting server socket ";
        char buf[4096];
        std::string userInput;
        sendPassword(sock);
        do{
            getline(std::cin, userInput);
            if (userInput.size() > 0) {
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
int ClientApp::connectServer(const char *IP, int Port) {
    ClientApp clientApp(IP,Port);
    if(clientApp.init()!=0){
        clientApp.run();
    }
    return 0;
}
int ClientApp::sendPassword(int serverSocket) {
    sendToServer(serverSocket,password.c_str(),password.size()+1);
}
int ClientApp::sendID(int serverSocket) {
    sendToServer(serverSocket,ID.c_str(),ID.size()+1);
}
int ClientApp::sendData(int serverSocket) {
    sendToServer(serverSocket,Data.c_str(),Data.size()+1);
}
int ClientApp::onMessageReceived(int serverSocket, const char* msg, int length) {
    if(msg=="1") {
        sendID(serverSocket);
        return 0;
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
