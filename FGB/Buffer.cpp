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
		if (!Inputs.empty() && Inputs.back().GetInputType() == InputToAdd.GetInputType() && !StopHolding) {
			StopHoldingInputs(false);
			return (Inputs.back().Hold());
		}
		StopHolding = false;
		return (Inputs.push_back(InputToAdd));
	}
}

void Buffer::StopHoldingInputs(bool StopHolding)
{
	this->StopHolding = StopHolding;
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

void Buffer::CutInputs(int FrameCounter)
{
	if (Inputs.empty()) {
		return;
	}
	//int LastFrame = Inputs.back().GetFrame();
	for (size_t i = 0; i < Inputs.size();)
	{
		if (!Inputs.empty()
			&& !Inputs[i].IsHeld()
			&& FrameCounter - (Inputs[i].GetFrame() + Inputs[i].GetHeldCounter()) > BUFFER_FRAMES)
		{
			Inputs.erase(Inputs.begin() + i);
		} else {
			++i;
		}
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

std::vector<Input> Buffer::GetInputs() const
{
	return (Inputs);
}
