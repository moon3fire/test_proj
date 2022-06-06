#include "client.h"
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client() {
	memset(m_buffer, 0, 1024);
	
	m_currentIP = "127.0.0.1";
	m_currentIP = "7821";

	std::cout << "IM HERE";	
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket < 0) {
		std::cerr << "Couldn't create socket\n" << std::endl;
		return;
	}

	std::cout << "IM HERE";	
	m_client.sin_family = AF_INET;
	m_client.sin_port = htons(std::atoi(m_currentPortNumber.c_str()));
	m_client.sin_addr.s_addr = inet_addr(m_currentIP.c_str());
}

void Client::Run() {
	int res = connect(m_socket, (sockaddr*)&m_client, sizeof(m_client));
	if (res < 0) {
		std::cerr << "Couldn't connect to server! Exiting..." << std::endl;
		return;
	}
	std::cout << "IM HERE";	
	std::string str;
	
	while(m_socket > 0) {
		std::cout << "Type music name" << std::endl << "$ ";

	std::cout << "IM HERE";	
		std::cin >> str;
		if(str == "1") {
			system("mplayer HXVRMXN-South-ddkissvk.com.mp3");

		}
		send(m_socket, str.c_str(), str.size() + 1, 0);

	std::cout << "IM HERE";	
		memset(m_buffer, 0, 2000);
		int bytesRecieved = recv(m_socket, m_buffer, 1024, 0);
		if(bytesRecieved < 0) {
			std::cerr << "lost connection to the server " << std::endl;
			break;
		}

	std::cout << "IM HERE";	
		if(std::string(m_buffer, strlen(m_buffer)) == "1") {
			system("mplayer HXVRMXN-South-kissvk.com.mp3");
		}
	}
	close(m_socket);
	return;
}

Client* GetClient() {
	std::cout << "IM HERE";	
	static Client s_client;
	return &s_client;
}
