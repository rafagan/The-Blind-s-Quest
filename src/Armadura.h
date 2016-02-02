#pragma once

#include "Personagem.h"

class Armadura : public Personagem
{
public:
	Armadura(char nome[100]);

	virtual void status();
	virtual void attack();
	virtual void defense();
};