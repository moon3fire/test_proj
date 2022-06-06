#pragma once

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <string>

class Server {
public:
	Server();
	Server(std::string, std::string);
	void RunServer();
private:
	std::string m_port;
	std::string m_ipAddr;
	bool m_ready;
	static void *ClientServant(void*);
	int m_listenerSock;
	int m_clientSock;
	int *newClientSock;
	sockaddr_in m_client;
	sockaddr_in m_server;
};

Server* GetServer();
