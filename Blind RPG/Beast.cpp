#include "Beast.h"

#include <iostream>

using namespace std;

Beast::Beast()
	  :pursuit(false),haveSpeed(false)
{
	char *tmp = "Besta";
	strcpy_s(nome,tmp);

	force = rand()%21;
	if(force < 10)
		force += 10;

	resistance = rand()%31;
	if(resistance < 15)
		resistance += 15;

	speed = rand()%31;
	if(speed < 15)
		speed += 15;

	lifeTotal = rand()%151;
	if(lifeTotal < 75)
		lifeTotal += 75;
	life = lifeTotal;
}

Beast::~Beast()
{
	fclose(file);
}

void Beast::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	if(pursuit){
		cout << endl << "\t\t     !!!!!!!!PERSEGUINDO VOCE!!!!!!!!" << endl;
	}
	cout << "--------------------------------------------------------------------------------------";
}

int Beast::attack()
{
	luck = rand()%15;

	if(pursuit == true && haveSpeed == false){
		speed = 45;
		haveSpeed = true;
	}

	if(haveSpeed){
		int tmp = rand()%2;
		if(tmp == 0){
			cout << nome <<" esta aumentando sua forca!!!" << endl;
			force += 2;
		}
		else if(tmp == 1){
			cout << nome <<" esta aumentando sua resistencia!!!" << endl;
			resistance += 2;
		}
	}

	if(luck == 0)
		return 0;
	else if(luck <= 12){
		int tmp = ((force + luck) % (force + luck + 1));
		int damage = (tmp) > (8) ? (tmp) : (force + 1);
		luck = 7;
		return  damage;
	}
	else if(luck == 13){
		int tmp = force + luck + 5;
		luck = 8;
		return tmp;
	}
	else if(luck == 14){
		if(force + (luck * 2) > force * 2){
			int tmp = force + (luck * 2);
			luck = 9;
			return tmp;
		}
		else{
			luck = 9;
			return force * 2;
		}
	}

	return -1;
}

int Beast::defense(int damage)
{
	if(damage < resistance/2)
		return 0;
	else if(damage <= resistance){
		life -= damage / 2;
		return 1;
	}
	else if(damage > resistance)
		life -= damage;

	return 2;
}

void Beast::image()
{
	int ch;

	if(pursuit == false)
		file = fopen("Beast1.txt", "r");
	else if(pursuit == true)
		file = fopen("Beast2.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int Beast::getSpeed()
{
	return speed;
}

int Beast::getLuck()
{
	return luck;
}

int Beast::getLife()
{
	return life;
}

char *Beast::getName()
{
	return nome;
}

bool Beast::setPursuit()
{
	if(pursuit == false)
		pursuit = true;
	else
		return true;

	return false;
}