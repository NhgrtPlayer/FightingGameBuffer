#include "Move.h"


Move::Move(const std::string & Name, Input input, EnumMovePriority Priority, bool FlushBuffer) :
	Name(Name),
	Priority(Priority),
	FlushBuffer(FlushBuffer)
{
	RequiredInputs.push_back(input);
}

Move::Move(const std::string & Name, std::vector<Input> Inputs, EnumMovePriority Priority, bool FlushBuffer) :
	Name(Name),
	RequiredInputs(Inputs),
	Priority(Priority),
	FlushBuffer(FlushBuffer)
{
}

Move::~Move()
{
}

bool Move::CheckMove(const std::vector<Input>& Inputs) const
{
	if (Inputs.empty() || Inputs.size() < RequiredInputs.size()) {
		return (false);
	}

	int i = RequiredInputs.size();
	int j = Inputs.size();

	while (i >= 0)
	{
		if (RequiredInputs[i] != Inputs[j]) {
			return (false);
		}
		--j;
		--i;
	}

	return (true);
}

EnumMovePriority Move::GetPriority() const
{
	return (Priority);
}

std::string Move::ToString() const
{
	return (Name);
}

