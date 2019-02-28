#pragma once

#include <vector>

enum EnumInput
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	A_BUTTON,
	B_BUTTON,
	C_BUTTON,
	D_BUTTON
};

class Input
{
	int Frame;
	std::vector<EnumInput> Inputs;

public:
	Input();
	~Input();
};

