#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

Server* GetServer() {
	static Server s_server;
	return &s_server;
}

Server::Server() {
	//default parameters
	
	m_ipAddr = "127.0.0.1";
	m_port = "7821";
	
	m_listenerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenerSock < 0) {
		std::cerr << "Couldn't create socket" << std::endl;
		return;
	}

	m_server.sin_family = AF_INET;
	m_server.sin_addr.s_addr = INADDR_ANY;
	m_server.sin_port = htons(std::atoi(m_port.c_str()));

	int opt = 1;
	setsockopt(m_listenerSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	int res = bind(m_listenerSock, (sockaddr*)&m_server, sizeof(sockaddr_in));
	if(res < 0) {
		std::cerr << "Couldn't bind server to given ip or port" << std::endl;
		shutdown(m_listenerSock, SHUT_RDWR);
		close(m_listenerSock);
		return;
	}

	res = listen(m_listenerSock, 5);
	if (res < 0) {
		std::cerr << "Couldn't start listening" << std::endl;
		shutdown(m_listenerSock, SHUT_RDWR);
		close(m_listenerSock);
		return;
	}

	m_ready = true;
}

void Server::RunServer() {
	if (!m_ready) {
		std::cerr << "Couldn't initialize needed parameters" << std::endl;
		return;
	}

	std::cout << "Server has started working..." << std::endl;
	int size = sizeof(m_client);
	while (m_clientSock = accept(m_listenerSock, (struct sockaddr*)&m_client, (socklen_t*)&size)) {
		pthread_t clientThread;
		newClientSock = (int*)malloc(1);
		*newClientSock = m_clientSock;
		int res = pthread_create(&clientThread, NULL, ClientServant, (void*)newClientSock);
		if (res < 0) {
			std::cerr << "Couldn't create thread" << std::endl;
			break;
		}
	}

	shutdown(m_listenerSock, SHUT_RDWR);
	shutdown(m_clientSock, SHUT_RDWR);
	close(m_listenerSock);
	close(m_clientSock);
}

void *Server::ClientServant(void *socket) {
	int sock = *(int*)(socket);
	char buffer[1024];
	while (sock > 0) {
		memset(buffer, 0, 1024);

		int bytesRecieved = recv(sock, buffer, 1024, 0);
		if (bytesRecieved < 0) {
			std::cerr << "A client send wrong message" << std::endl;
			free(socket);
			return 0;
		}

		if(std::string(buffer, strlen(buffer)) == "1")
		{
			send(sock, "1", 1, 0);
			continue;
		}

		send(sock, buffer, strlen(buffer), 0);
	}

	shutdown(sock, SHUT_RDWR);
	close(sock);
	free(socket);
	return 0;
}
