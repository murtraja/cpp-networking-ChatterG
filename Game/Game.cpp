#include "stdafx.h"
#include "Game.h"
#include "RandomnessProvider.h"


CGame::CGame()
{
	int x = CRandomnessProvider::GetInstance().GetRandomNumberInclusive(0, GAME_BOARD_WIDTH);
	int y = CRandomnessProvider::GetInstance().GetRandomNumberInclusive(0, GAME_BOARD_HEIGHT);
	SetPosition(x, y);
}


CGame::~CGame()
{
}

void CGame::PrintBoard()
{
	int i;
	PrintTerminalLine();
	for (i = 0; i < GAME_BOARD_HEIGHT; i++)
	{
		PrintInternalLine(i);
	}
	PrintTerminalLine();
}

void CGame::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CGame::ChangeXBy(int dx)
{
	if (dx + m_x >= 0 && dx + m_x <= GAME_BOARD_WIDTH)
	{
		m_x += dx;
	}
}

void CGame::ChangeYBy(int dy)
{
	if (dy + m_y >= 0 && dy + m_y <= GAME_BOARD_HEIGHT)
	{
		m_y += dy;
	}
}

void CGame::PrintTerminalLine()
{
	printf("+");
	for (int i = 0; i < GAME_BOARD_WIDTH; i++)
	{
		printf("-");
	}
	printf("+\n");
}

void CGame::PrintInternalLine(int i)
{
	printf("|");
	for (int j = 0; j < GAME_BOARD_WIDTH; j++)
	{
		if (i == m_y && j == m_x)
		{
			printf("M");
			continue;
		}
		printf(" ");
	}
	printf("|\n");
}
