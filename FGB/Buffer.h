#pragma once

#include <vector>
#include "Input.h"

class Buffer
{
	const int BUFFER_FRAMES = 4;
	std::vector<Input> Inputs;

public:
	Buffer();
	~Buffer();

	void AddInput(Input InputToAdd);
	void StopHoldingInput();
	void Flush();
};

