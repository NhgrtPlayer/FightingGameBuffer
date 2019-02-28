#include "Buffer.h"



Buffer::Buffer()
{
}


Buffer::~Buffer()
{
}

void Buffer::AddInput(Input InputToAdd)
{
	if (InputToAdd == EnumInput::NEUTRAL) {
		StopHoldingInput();
	} else {
		Inputs.push_back(InputToAdd);
	}
}

void Buffer::StopHoldingInput()
{
	for (auto &Input : Inputs) {
		if (Input.IsHeld()) {
			Input.StopHolding();
		}
	}
}

void Buffer::Flush()
{
	Inputs.clear();
}
