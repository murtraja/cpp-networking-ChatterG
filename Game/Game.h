#pragma once
#define GAME_BOARD_WIDTH	5
#define GAME_BOARD_HEIGHT	3
class CGame
{
	int m_x, m_y;

	void PrintTerminalLine();
	void PrintInternalLine(int i);
public:
	CGame();
	~CGame();
	void PrintBoard();
	void SetPosition(int x, int y);
	void ChangeXBy(int dx);
	void ChangeYBy(int dy);
	int GetX() { return m_x; }
	int GetY() { return m_y; }

};

