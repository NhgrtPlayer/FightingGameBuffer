#pragma once

#include <vector>
#include "Input.h"

class Buffer
{
	const int BUFFER_FRAMES = 5;
	std::vector<Input> Inputs;
	bool StopHolding;

public:
	Buffer();
	~Buffer();

	void AddInput(Input InputToAdd);
	void StopHoldingInputs();
	void Flush();
	void CutInputs(int FrameCounter);
	void PrintBuffer() const;
};

