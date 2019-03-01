#include "Input.h"



Input::Input() :
	Frame(0),
	InputType(EnumInput::NEUTRAL),
	Held(false),
	HeldCounter(0)
{
}

Input::Input(int Frame, EnumInput InputType) :
	Frame(Frame),
	InputType(InputType),
	Held(false),
	HeldCounter(0)
{
}


Input::~Input()
{
}

Input::Input(const Input & rhs) :
	Frame(rhs.GetFrame()),
	InputType(rhs.GetInputType()),
	Held(rhs.IsHeld()),
	HeldCounter(rhs.GetHeldCounter())
{
}

Input & Input::operator=(const Input & rhs)
{
	Frame = rhs.GetFrame();
	InputType = rhs.GetInputType();
	Held = rhs.IsHeld();
	HeldCounter = rhs.GetHeldCounter();
	return (*this);
}

int Input::GetFrame() const
{
	return (Frame);
}

EnumInput Input::GetInputType() const
{
	return (InputType);
}

int Input::GetHeldCounter() const
{
	return (HeldCounter);
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
	if (!Held) {
		StartHolding();
	}
	HeldCounter++;
}

void Input::StopHolding()
{
	Held = false;
	//HeldCounter = 0;
}

bool Input::operator == (const EnumInput & rhs)
{
	return (InputType == rhs);
}

bool Input::operator == (const Input & rhs)
{
	return (InputType == rhs.GetInputType());
}

bool Input::operator != (const Input & rhs)
{
	return (InputType != rhs.GetInputType());
}

std::string InputToString(const Input & InputToString)
{
	std::string ToReturn = "";

	switch (InputToString.GetInputType())
	{
	case NEUTRAL:
		break;
	case UP:
		ToReturn = "Up";
		break;
	case UP_LEFT:
		ToReturn = "Up-Left";
		break;
	case UP_RIGHT:
		ToReturn = "Up-Right";
		break;
	case DOWN:
		ToReturn = "Down";
		break;
	case DOWN_LEFT:
		ToReturn = "Down-Left";
		break;
	case DOWN_RIGHT:
		ToReturn = "Down-Right";
		break;
	case LEFT:
		ToReturn = "Left";
		break;
	case RIGHT:
		ToReturn = "Right";
		break;
	case A_BUTTON:
		ToReturn = "A";
		break;
	case B_BUTTON:
		ToReturn = "B";
		break;
	case C_BUTTON:
		ToReturn = "C";
		break;
	case D_BUTTON:
		ToReturn = "D";
		break;
	default:
		break;
	}
	if (InputToString.GetHeldCounter() > 0) {
		ToReturn += " ";
		ToReturn += std::to_string(InputToString.GetHeldCounter());
	}
	return (ToReturn);
}

std::ostream & operator << (std::ostream & os, const Input & rhs)
{
	os << InputToString(rhs);
	return (os);
}

EnumInput FlipInput(EnumInput Input)
{ // Reminder: Horizontal Flip, Right becomes Left but Up stays Up
	EnumInput ToReturn = EnumInput::NEUTRAL;

	switch (Input)
	{
	case UP_LEFT:
		ToReturn = EnumInput::UP_RIGHT;
		break;
	case UP_RIGHT:
		ToReturn = EnumInput::UP_LEFT;
		break;
	case DOWN_LEFT:
		ToReturn = EnumInput::DOWN_RIGHT;
		break;
	case DOWN_RIGHT:
		ToReturn = EnumInput::DOWN_LEFT;
		break;
	case LEFT:
		ToReturn = EnumInput::RIGHT;
		break;
	case RIGHT:
		ToReturn = EnumInput::LEFT;
		break;
	default:
		break;
	}
	return (ToReturn);
}
