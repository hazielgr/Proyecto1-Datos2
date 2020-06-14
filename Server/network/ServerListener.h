#ifndef SERVERMEMORYMANAGER_SERVERLISTENER_H
#define SERVERMEMORYMANAGER_SERVERLISTENER_H
/**
 * @file ServerListener.h
 * @brief Handles server Behavior
 * @author Joseph Jimenez
 * @version 1.0
 */
#pragma once
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
/**
 * @class ServerListener
 * @brief Represents a class that handles server's Runtime
 */
class ServerListener;

class ServerListener{
public:
/**
 * Building the server
 * @param ipAddress
 * @param port
 * @param password
 */
        ServerListener(const char* ipAddress, int port, const char* password) : m_ipAddress(ipAddress), m_port(port), m_password(password) { }
    int init();
protected:
    void sendToClient(int clientSocket, const char* msg, int length);
    void onMessageReceived(int clientSocket, const char* msg, int length);
    virtual void onClientConnected(int clientSocket);
    int                   m_socket;           /// State of socket
    sockaddr_in           client_addr{};      /// Handles Clients socket structure
    socklen_t             clientSize;         /// Client Size
    std::string           m_password;         /// Server Password
private:
    sockaddr_in           server_addr{};      /// Handles Server sockets structure
    std::string           m_ipAddress;        /// IPAddress of server="127.0.0.1"
    int                   m_port;             /// Port for server use= 54000

};
#endif //SERVERMEMORYMANAGER_SERVERLISTENER_H
