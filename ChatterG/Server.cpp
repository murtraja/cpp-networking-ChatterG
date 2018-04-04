#include "stdafx.h"
#include "Server.h"


bool CServer::Initialize()
{
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == INVALID_SOCKET)
	{
		printf("Unable to create server socket\n");
		return false;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(SERVER_PORT);
	if (bind(m_socket, (const sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to bind the server\n");
		return false;
	}

	ULONG mode = 1;
	ioctlsocket(m_socket, FIONBIO, &mode);

	return true;
}

void CServer::ReceiveInputs()
{
	char buffer[SERVER_BUFLEN];
	sockaddr_in clientAddress;
	int addressSize = sizeof(clientAddress);
	int ret = recvfrom(m_socket, buffer, SERVER_BUFLEN, 0, reinterpret_cast<SOCKADDR *>(&clientAddress), &addressSize);
	if (ret > 0)
	{
		char ipAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, (void*)&clientAddress.sin_addr, ipAddress, INET_ADDRSTRLEN);
		buffer[ret] = 0;
		printf("received %s from %s:%d\n", buffer, ipAddress, ntohs(clientAddress.sin_port));
		m_inputProcessor.Queue(buffer);
		StoreClientInfo(clientAddress.sin_addr.s_addr, clientAddress.sin_port);
	}
}

void CServer::ProcessInputs()
{
	m_inputProcessor.ProcessQueue(m_game);
}

void CServer::SendGameState()
{
	int x = m_game.GetX();
	int y = m_game.GetY();
	char buffer[SERVER_BUFLEN];
	snprintf(buffer, SERVER_PORT, "%d,%d", x, y);
	int dataLength = strlen(buffer);

	for (unsigned int i = 0; i < m_clients.size(); i++)
	{
		sockaddr_in clientAddress;
		clientAddress.sin_family = AF_INET;
		clientAddress.sin_addr.S_un.S_addr = m_clients[i].m_nAddress;
		clientAddress.sin_port = m_clients[i].m_nPort;
		int ret = sendto(m_socket, buffer, dataLength, 0, (sockaddr*)&clientAddress, sizeof(clientAddress));
	}
}

CServer::CServer()
	: m_socket(INVALID_SOCKET)
{
}


CServer::~CServer()
{
}

void CServer::Run()
{
	if (!Initialize())
	{
		printf("Failed to initialize winsock\n");
		return;
	}
	while (1)
	{
		ReceiveInputs();
		ProcessInputs();
		SendGameState();
		Sleep(200);
	}
}

void CServer::StoreClientInfo(ULONG clientAddress, u_short clientPort)
{
	for (unsigned int i = 0; i < m_clients.size(); i++)
	{
		if (clientAddress == m_clients[i].m_nAddress
			&& clientPort == m_clients[i].m_nPort)
		{
			return;
		}
	}
	CClientInfo newClient = { clientAddress, clientPort };
	m_clients.push_back(newClient);
}
