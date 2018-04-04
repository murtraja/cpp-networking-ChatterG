// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientG.h"
#include "..\ChatterG\ServerDefs.h"


int main(int argc, char* argv[])
{
	printf("This is the client\n");
	CClientG client("127.0.0.1", SERVER_PORT);
	client.Run();
	return 0;
}

