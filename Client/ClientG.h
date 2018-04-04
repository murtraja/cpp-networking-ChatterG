#pragma once
#include "..\Game\Game.h"
class CClientG
{
	int m_serverPort;
	char m_hostAddress[INET_ADDRSTRLEN];
	SOCKET m_socket;
	sockaddr_in m_serverSocketAddress;
	CGame m_game;

	bool Initialize();
	void SetParams(char* hostIp, int port);

	void ReadInputAndSendToServer();
	void ReceiveAndUpdateGameState();
	void SendInputToServer(char inputKey);

	void UpdateGameState(char buffer[]);
public:
	CClientG();
	CClientG(char* hostIp, int port);
	~CClientG();
	void Run();
};

