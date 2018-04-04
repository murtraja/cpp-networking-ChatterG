// ChatterG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "..\Game\Game.h"


int main()
{
	printf("The server\n");
	CServer server;
	server.Run();
	/*CGame game;
	game.PrintBoard();*/
	return 0;
}

