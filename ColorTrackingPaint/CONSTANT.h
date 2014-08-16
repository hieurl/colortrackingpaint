#pragma once
#include <string>
using namespace std;
class CONSTANT
{
public:
	
	CONSTANT(void)
	{
	}

	~CONSTANT(void)
	{
	}

	static const int ACTION_SHOW_MENU = 1;
	static const int ACTION_SHOW_COLOR_TABLE = 2;

	static const int ACTION_MOUSE = 3;
	
	static const int ACTION_CHOOSE_COLOR = 4;
	static const int ACTION_CHOOSE_PEN = 5;
	static const int ACTION_CHOOSE_BRUSH = 6;
	static const int ACTION_CHOOSE_RECT = 7;
	static const int ACTION_CHOOSE_CIR = 8;
	static const int ACTION_CHOOSE_ERASER = 9;
	static const int ACTION_CHOOSE_COLOR_RED = 10;
	static const int ACTION_CHOOSE_COLOR_YELLOW = 11;
	static const int ACTION_CHOOSE_COLOR_BLUE = 12;
	static const int ACTION_CHOOSE_COLOR_GREEN = 13;
	static const int ACTION_CHOOSE_COLOR_PURPLE = 14;
	static const int ACTION_CHOOSE_COLOR_CUSTOM = 15;

	static const int ACTION_DRAW = 16;

	static const int CURSOR_PEN = 1;
	static const int CURSOR_BRUSH = 2;
	static const int CURSOR_RECT = 3;
	static const int CURSOR_CIR = 4;

	static const int COLOR_RED = 1;
	static const int COLOR_YELLOW = 2;
	static const int COLOR_BLUE = 3;
	static const int COLOR_GREEN = 4;
	static const int COLOR_PURPLE = 5;
	static const int COLOR_CUSTOM = 6;
};

