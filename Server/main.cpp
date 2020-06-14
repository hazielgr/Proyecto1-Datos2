#include "messages/ServerApp.h"

int main(){
    ServerApp server("127.0.0.1", 54000, "password");
    if(server.init()!=0){
        server.run();
    }
}
