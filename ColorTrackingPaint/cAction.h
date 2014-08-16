#pragma once
class cAction
{
public:
	int _ACTION_CODE;
	int X;
	int Y;

	cAction(void)
	{
	}

	cAction(int ACTION_CODE, int posX, int posY) : _ACTION_CODE(ACTION_CODE), X(posX), Y(posY) {
	
	}

	~cAction(void)
	{
	}
};

