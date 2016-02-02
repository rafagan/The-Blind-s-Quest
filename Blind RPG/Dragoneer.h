#pragma once

#include "Inimigo.h"

class Dragoneer : public Inimigo
{
public:
	Dragoneer(void);

	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual bool setNew();

	virtual ~Dragoneer();
private:
	char nome[40];
	int lifeTotal1,life1;
	int force1, resistance1;
	int luck;
	int speed1;
	bool isDefeated;

	FILE *file;
};

