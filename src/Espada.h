#pragma once

#include "Personagem.h"

class Espada : public Personagem
{
public:
	Espada(char nome[100]);
	
	virtual void status();
	virtual void attack();
	virtual void defense();
};

