#pragma once

#include <sstream>

enum EnumInput
{
	NEUTRAL,
	UP,
	UP_LEFT,
	UP_RIGHT,
	DOWN,
	DOWN_LEFT,
	DOWN_RIGHT,
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
	EnumInput InputType;
	bool Held;
	int HeldCounter;

public:
	Input();
	Input(int Frame, EnumInput InputType);
	~Input();
	Input(const Input & rhs);
	Input & operator = (const Input & rhs);

	int GetFrame() const;
	EnumInput GetInputType() const;
	int GetHeldCounter() const;
	bool IsHeld() const;
	void StartHolding();
	void Hold();
	void StopHolding();

	bool operator == (const EnumInput & rhs);
	bool operator == (const Input & rhs);
	bool operator != (const Input & rhs);
};

std::string InputToString(const Input & InputToString);
std::ostream & operator << (std::ostream & os, const Input & rhs);
EnumInput FlipInput(EnumInput Input);
