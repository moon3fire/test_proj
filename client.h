#pragma once
#include <netinet/in.h>
#include <string>

class Client {
public:
	Client();
	void Run();
private:
	char m_buffer[1024];
	bool m_connectStatus;
	std::string m_currentCommand;
	std::string m_currentIP;
	std::string m_currentPortNumber;
	sockaddr_in m_client;
	int m_socket;
};

Client *GetClient();
