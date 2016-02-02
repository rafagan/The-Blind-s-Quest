#include "Death.h"
#include <conio.h>

using namespace std;

Death::Death()
{
	char *tmp = "Death";
	strcpy_s(nome,tmp);

	force = 20;
	resistance = 15;
	speed = 10;
	lifeTotal = 200;
	life = lifeTotal;
}

Death::~Death()
{
	system("cls");

	cout    << "\n\n       Apos uma intensa batalha com a morte, nossos herois partem em busca de uma\n"
		    << "        entrada em meio as montanhas para garantirem o acesso ao caminho que leva\n"
		    << "                 para o palacio de Nilats. Sera que eles vao conseguir?\n\n\n" << endl;

	int ch;

	file = fopen("Mountains.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	_getch();system("pause");system("cls");

	fclose(file);
}


void Death::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	if(life <= 50){
		cout << endl << "\t\t     !!!!!!!!DEATH ESTA ATRAS DE SUA ALMA!!!!!!!!" << endl;
	}
	cout << "--------------------------------------------------------------------------------------";
}

int Death::attack()
{
	if(life <= 50){
		luck = rand()%10;
		if(luck == 0){
			return 0;
		}
		else if(luck <= 7){
			int tmp = ((force + luck) % (force + luck + 1));
			int damage = ((tmp) > (force) ? (tmp) : (force + 1));
			return  damage;
		}
		else if(luck >= 8){
			int tmp = rand() % 21;
			if(tmp < 10)
				tmp += 10;
			tmp *= (luck - 7);
			return tmp;
		}
	}
	else if(life > 50){
		luck = rand()%10;

		if(luck == 0){
			return 0;
		}
		else if(luck <= 7){
			int tmp = ((force + luck) % (force + luck + 1));
			int damage = ((tmp) > (force) ? (tmp) : (force + 1));
			return  damage;
		}
		else if(luck == 8){
			return (force + (luck * 2));
		}
		else if(luck == 9){
			if(force + (luck * 2) > force * 2)
				return (force + (luck * 2) + 2);
			else 
				return (force * 2);
		}
	}

	return -1;
}

int Death::defense(int damage)
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

void Death::image()
{
	int ch;

	if(life > 100)
		file = fopen("Death 1.txt", "r");
	else if(life <= 100 && life > 50)
		file = fopen("Death 2.txt", "r");
	else if(life <= 50)
		file = fopen("Death 3.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int Death::getSpeed()
{
	return speed;
}

int Death::getLuck()
{
	return luck;
}

int Death::getLife()
{
	return life;
}

char *Death::getName()
{
	return nome;
}

void Death::setDrainPower(int machineryState,int damage)
{
	if(this->life <= 50){
		if(machineryState == 1)
			life += damage/2;
		else
			life += damage;
	}
}