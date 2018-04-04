#include "stdafx.h"
#include "ClientG.h"
#include "..\ChatterG\ServerDefs.h"


bool CClientG::Initialize()
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

	m_serverSocketAddress.sin_family = AF_INET;
	inet_pton(AF_INET, m_hostAddress, &(m_serverSocketAddress.sin_addr));
	m_serverSocketAddress.sin_port = htons(m_serverPort); 

	ULONG mode = 1;
	ioctlsocket(m_socket, FIONBIO, &mode);

	return true;
}

void CClientG::SetParams(char* hostIp, int port)
{
	strncpy_s(m_hostAddress, hostIp, INET_ADDRSTRLEN);
	m_serverPort = port;
}

CClientG::CClientG()
{
	SetParams("localhost", 8080);
}


CClientG::CClientG(char* hostIp, int port)
{
	SetParams(hostIp, port);
}

CClientG::~CClientG()
{
}

void CClientG::Run()
{
	if (!Initialize())
	{
		printf("The client failed to initalize.\n");
	}
	SendInputToServer('#');
	while (1)
	{
		ReceiveAndUpdateGameState();
		system("cls");
		m_game.PrintBoard();
		
		ReadInputAndSendToServer();		
	}
}

void CClientG::ReadInputAndSendToServer()
{
	if (_kbhit())
	{
		char inputKey = _getch();
		inputKey = tolower(inputKey);
		if (inputKey == 'w')
		{
			SendInputToServer(inputKey);
		}
		else if (inputKey == 's')
		{
			SendInputToServer(inputKey);
		}
		else if (inputKey == 'a')
		{
			SendInputToServer(inputKey);
		}
		else if (inputKey == 'd')
		{
			SendInputToServer(inputKey);
		}
	}
}

void CClientG::ReceiveAndUpdateGameState()
{
	char buffer[SERVER_BUFLEN];
	sockaddr_in serverAddress;
	int addressSize = sizeof(serverAddress);
	int ret = recvfrom(m_socket, buffer, SERVER_BUFLEN, 0, reinterpret_cast<SOCKADDR *>(&serverAddress), &addressSize);
	if (ret > 0)
	{
		char ipAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, (void*)&serverAddress.sin_addr, ipAddress, INET_ADDRSTRLEN);
		buffer[ret] = 0;
		printf("received %s from %s:%d\n", buffer, ipAddress, ntohs(serverAddress.sin_port));
		UpdateGameState(buffer);
	}
}

void CClientG::SendInputToServer(char inputKey)
{
	char inputBuffer[30];
	snprintf(inputBuffer, 30, "%c", inputKey);
	int length = strlen(inputBuffer);
	int ret = (sendto(m_socket, inputBuffer, length, 0, (sockaddr*)&m_serverSocketAddress, sizeof(m_serverSocketAddress)));
	if(!ret)
	{
		printf("sendto() failed with error code : %d %d ", WSAGetLastError(), ret);
	}
}

void CClientG::UpdateGameState(char buffer[])
{
	int x, y;
	char *next;
	char* ptr = strtok_s(buffer, ",", &next);
	if (ptr)
	{
		x = atoi(ptr);
		ptr = strtok_s(NULL, ",", &next);
	}
	if (ptr)
	{
		y = atoi(ptr);
	}
	m_game.SetPosition(x, y);
}
