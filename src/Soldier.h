#pragma once

#include "Inimigo.h"

//GLOBAL TEMPORÁRIA PARA A MOSTRA!!!
static int counterTMP = 0;

class Soldier : public Inimigo
{
public:
	Soldier();

	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual ~Soldier();
private:
	char nome[20];
	int lifeTotal,life;
	int force, resistance;
	int luck;
	int speed;
	int aleatorio;

	FILE *file;
};

