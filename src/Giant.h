#pragma once

#include "Inimigo.h"

class Giant : public Inimigo
{
public:
	Giant();
	
	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual ~Giant();

private:
	char nome[15];
	int lifeTotal,life;
	int rage, rageP, force, resistance;
	int luck;
	int speed;
	bool isEnraiged;

	FILE *file;
};

