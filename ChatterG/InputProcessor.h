#pragma once

#define GAME_INPUT_UP	"w"
#define GAME_INPUT_DOWN	"s"
#define GAME_INPUT_RIGHT "d"
#define GAME_INPUT_LEFT "a"
#define GAME_INPUT_SIZE 1

class CGame;

enum EGameInputType
{
	GameInputType_Up,
	GameInputType_Down,
	GameInputType_Right,
	GameInputType_Left
};
class CInputProcessor
{
	std::queue<EGameInputType> m_input;
public:
	CInputProcessor();
	~CInputProcessor();
	void Queue(char buffer[]);
	void ProcessQueue(CGame& game);
};

