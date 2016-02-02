#include "Giant.h"
#include <ctime>

using namespace std;

Giant::Giant()
	  :lifeTotal(300),life(300),rage(1),isEnraiged(false),speed(3)
{
	char *tmp = "Gigante";
	strcpy(nome,tmp);

	resistance = rand()%41;
	if(resistance < 20)
		resistance += 20;

	force = rand() % 41;
	if(force < 20)
		force += 20;
}

Giant::~Giant()
{
	fclose(file);
}

void Giant::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	if(isEnraiged)
		cout << endl << "\t\t\t         !!!!!!!!COM RAIVA!!!!!!!!" << endl;
	cout << "--------------------------------------------------------------------------------------";
}

int Giant::attack()
{
	luck = rand()%10;
	int tmp;

	this->rage = 1;

	if(rageP >= 5 && isEnraiged == true)
		rage *= 2;

	if(luck == 0)
		return 0;
	else if(luck <= 7){
		tmp = ((force * rage) + luck) % ((force * rage) + luck + 1);
		int damage = (tmp) > (force * rage) ? (tmp) : (force * rage) + 1;
		tmp = damage;
	}
	else if(luck == 8)
		tmp = (force * rage) + (luck * 2);
	else if(luck == 9){
		if(force + (luck * 2) > force * 2)
			tmp = force + (luck * 2) + 2;
		else 
			tmp = force * 2 * rage;
	}

	if(rageP >= 5)
		isEnraiged = false;

	return tmp;
}

int Giant::defense(int damage)
{
	if(damage < resistance/2)
		return 0;
	else if(damage <= resistance){
		life -= damage / 2;
		return 1;
	}
	else if(damage > resistance){
		life -= damage;
		rageP = rand()%8;
		isEnraiged = true;
	}

	return 2;
}

void Giant::image()
{
	int ch;

	if(isEnraiged == false){
		file = fopen("Giant.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
	}
	else if(isEnraiged){
		file = fopen("Giant 2.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
	}
}

int Giant::getSpeed()
{
	return speed;
}

int Giant::getLuck()
{
	return luck;
}

int Giant::getLife()
{
	return life;
}

char *Giant::getName()
{
	return nome;
}