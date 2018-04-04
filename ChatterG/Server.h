#pragma once
#include "ServerDefs.h"
#include "InputProcessor.h"
#include "..\Game\Game.h"

class CServer
{
	struct CClientInfo
	{
		ULONG m_nAddress;
		u_short m_nPort;
	};
	SOCKET m_socket;
	CInputProcessor m_inputProcessor;
	CGame m_game;
	std::vector<CClientInfo> m_clients;

	bool Initialize();
	void ReceiveInputs();
	void ProcessInputs();
	void SendGameState();
public:
	CServer();
	~CServer();
	void Run();
	void StoreClientInfo(ULONG sin_addr, u_short sin_port);
};

