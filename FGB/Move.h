#pragma once

#include <string>
#include <vector>
#include "Input.h"
#include "MovePriority.h"

class Move
{
	std::string Name;
	std::vector<Input> RequiredInputs;
	EnumMovePriority Priority;
	bool FlushBuffer;

public:
	Move(const std::string & Name, Input input, EnumMovePriority Priority, bool FlushBuffer = false);
	Move(const std::string & Name, std::vector<Input> Inputs, EnumMovePriority Priority, bool FlushBuffer = false);
	~Move();

	bool CheckMove(const std::vector<Input> & Inputs) const;
	EnumMovePriority GetPriority() const;
	std::string ToString() const;
};

