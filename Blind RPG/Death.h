#pragma once

#include "Inimigo.h"

class Death: public Inimigo
{
public:
	Death();

	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual void setDrainPower(int machineryState,int damage);

	virtual ~Death();

private:
	char nome[15];
	int lifeTotal,life;
	int force, resistance;
	int luck;
	int speed;

	FILE *file;
};

