#include "Soldier.h"

using namespace std;



Soldier::Soldier()
{
	if(counterTMP < 10){
		char *tmp = "Soldado";
		strcpy_s(nome,tmp);

		force = rand()%11;
		if(force < 3)
			force += 3;

		resistance = rand()%11;
		if(resistance < 2)
			resistance += 2;

		speed = rand()%6;
		if(speed == 0)
			speed = 1;

		lifeTotal = rand()%31;
		if(lifeTotal < 10)
			lifeTotal = 10 + rand()%10;
		life = lifeTotal;
	}

	else if(counterTMP < 24){
		char *tmp = "Soldado Agressivo";
		strcpy_s(nome,tmp);

		force = rand()%21;
		if(force < 10)
			force += 10;

		resistance = rand()%16;
		if(resistance < 7)
			resistance += 7;

		speed = rand()%13;
		if(speed < 6)
			speed += 6;

		lifeTotal = rand()%51;
		if(lifeTotal < 25)
			lifeTotal = 25 + rand()%21;
		life = lifeTotal;
	}
	else{
		char *tmp = "General";
		strcpy_s(nome,tmp);

		force = rand()%31;
		if(force < 15)
			force += 15;

		resistance = rand()%31;
		if(resistance < 15)
			resistance += 15;

		speed = rand()%21;
		if(speed < 10)
			speed += 10;

		lifeTotal = rand()%101;
		if(lifeTotal < 50)
			lifeTotal = 50 + rand()%21;
		life = lifeTotal;
	}


	aleatorio = rand()%3;

	counterTMP++;
}

Soldier::~Soldier()
{
	fclose(file);
}


void Soldier::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	cout << "--------------------------------------------------------------------------------------";
}

int Soldier::attack()
{
	luck = rand()%10;

	if(luck == 0){
		return 0;
	}
	else if(luck <= 7){
		if(luck > 4)
			luck = 4;
		int tmp = ((force + luck) % (force + luck + 1));
		int damage = (tmp) > (force) ? (tmp) : (force + 1);
		return  damage;
	}
	else if(luck == 8){
		return force + 10;
	}
	else if(luck == 9){
		if(force + (luck * 2) > force * 2)
			return force + (luck * 2) + 2;
		else 
			return force * 2;
	}

	return -1;
}

int Soldier::defense(int damage)
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

void Soldier::image()
{
	int ch;

	if(aleatorio == 0)
		file = fopen("Soldier1.txt", "r");
	else if(aleatorio == 1)
		file = fopen("Soldier2.txt", "r");
	else if(aleatorio == 2)
		file = fopen("Soldier3.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int Soldier::getSpeed()
{
	return speed;
}

int Soldier::getLuck()
{
	return luck;
}

int Soldier::getLife()
{
	return life;
}

char *Soldier::getName()
{
	return nome;
}