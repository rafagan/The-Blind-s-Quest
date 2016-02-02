#pragma once

#include "Inimigo.h"

class Beast : public Inimigo
{
public:
	Beast();

	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual bool setPursuit();

	virtual ~Beast();

private:
	char nome[15];
	int lifeTotal,life;
	int speed, addSpeed, force, resistance;
	int luck;
	bool pursuit;
	bool haveSpeed;

	FILE *file;
};

