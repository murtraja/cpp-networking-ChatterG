#include "stdafx.h"
#include "InputProcessor.h"
#include "..\Game\Game.h"


CInputProcessor::CInputProcessor()
{
}


CInputProcessor::~CInputProcessor()
{
}

void CInputProcessor::Queue(char buffer[])
{
	if (strncmp(buffer, GAME_INPUT_UP, GAME_INPUT_SIZE) == 0)
	{
		m_input.push(GameInputType_Up);
	}
	else if (strncmp(buffer, GAME_INPUT_DOWN, GAME_INPUT_SIZE) == 0)
	{
		m_input.push(GameInputType_Down);
	}
	else if (strncmp(buffer, GAME_INPUT_LEFT, GAME_INPUT_SIZE) == 0)
	{
		m_input.push(GameInputType_Left);
	}
	else if (strncmp(buffer, GAME_INPUT_RIGHT, GAME_INPUT_SIZE) == 0)
	{
		m_input.push(GameInputType_Right);
	}
}

void CInputProcessor::ProcessQueue(CGame &game)
{
	while (!m_input.empty())
	{
		EGameInputType inputType = m_input.front();
		switch (inputType)
		{
		case GameInputType_Up:
			game.ChangeYBy(-1);
			break;
		case GameInputType_Down:
			game.ChangeYBy(1);
			break;
		case GameInputType_Left:
			game.ChangeXBy(-1);
			break;
		case GameInputType_Right:
			game.ChangeXBy(1);
			break;
		}
		m_input.pop();
	}
}
