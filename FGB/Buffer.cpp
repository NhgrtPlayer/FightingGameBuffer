#include <iostream>
#include "Buffer.h"

Buffer::Buffer():
	StopHolding(false)
{
}


Buffer::~Buffer()
{
}

void Buffer::AddInput(Input InputToAdd)
{
	if (InputToAdd == EnumInput::NEUTRAL) {
		StopHoldingInputs();
	} else {
		if (!Inputs.empty() && Inputs.back() == InputToAdd && !StopHolding) {
			return (Inputs.back().Hold());
		}
		StopHolding = false;
		return (Inputs.push_back(InputToAdd));
		/*if (Inputs.empty()
			|| Inputs.back() != InputToAdd
			|| StopHolding) {
		}*/
	}
}

void Buffer::StopHoldingInputs()
{
	StopHolding = true;
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

void Buffer::CutInputs()
{
	if (Inputs.empty()) {
		return;
	}
	int LastFrame = Inputs.back().GetFrame();

	while (LastFrame - Inputs.front().GetFrame() > BUFFER_FRAMES) {
		Inputs.erase(Inputs.begin());
	}
}

void Buffer::PrintBuffer() const
{
	std::cout << "INPUTS SIZE : " << Inputs.size() << '\n';
	for (auto &Input : Inputs) {
		std::cout << Input;
		std::cout << '\n';
	}
}
