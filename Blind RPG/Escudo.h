#pragma once

#include "Personagem.h"

class Escudo : public Personagem
{
public:
	Escudo(char nome[100]);

	virtual void status();
	virtual void attack();
	virtual void defense();
};

