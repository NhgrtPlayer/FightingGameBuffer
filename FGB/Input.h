#pragma once

enum EnumInput
{
	NEUTRAL,
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
	EnumInput InputType;
	bool Held;
	int HeldCounter;

public:
	Input();
	~Input();

	int GetFrame() const;
	EnumInput GetInputType() const;
	bool IsHeld() const;
	void StartHolding();
	void Hold();
	void StopHolding();

	bool operator == (const EnumInput & rhs);
};

