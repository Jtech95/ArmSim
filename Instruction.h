#pragma once

#include "askapi.h"

class Instruction {
protected:
	word raw_;
public:
	Instruction();
	Instruction(word);
	~Instruction();

	int decode();
	int execute();
};

