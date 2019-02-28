#include "Input.h"



Input::Input() :
	HeldCounter(0)
{
}


Input::~Input()
{
}

int Input::GetFrame() const
{
	return (Frame);
}

EnumInput Input::GetInputType() const
{
	return (InputType);
}

bool Input::IsHeld() const
{
	return (Held);
}

void Input::StartHolding()
{
	Held = true;
}

void Input::Hold()
{
	if (Held) {
		HeldCounter++;
	}
}

void Input::StopHolding()
{
	Held = false;
}

bool Input::operator==(const EnumInput & rhs)
{
	return (InputType == rhs);
}
