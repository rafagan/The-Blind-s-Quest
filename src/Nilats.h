#pragma once

#include "Inimigo.h"

class Nilats : public Inimigo
{
public:
	Nilats(void);

	virtual void status();
	virtual int attack();
	virtual int defense(int damage);

	virtual void image();

	virtual int getSpeed();
	virtual int getLuck();
	virtual int getLife();
	virtual char *getName();

	virtual ~Nilats();

private:
	void setImage();

	char nome[40];
	int lifeTotal,life;
	int force, resistance;
	int luck;
	int speed;

	FILE *file;
};

