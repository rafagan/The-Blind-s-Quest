#include "Dragoneer.h"
#include <conio.h>

using namespace std;

Dragoneer::Dragoneer()
	:isDefeated(false)
{
	char *tmp = "Milus, the Kinight Dragoneer";
	strcpy_s(nome,tmp);

	force1 = 30;
	resistance1 = 35;
	speed1 = 45;
	lifeTotal1 = 200;
	life1 = lifeTotal1;
}

Dragoneer::~Dragoneer()
{
	system("cls");

	cout    << "\n\n    Argorn e Tyson em uma luta de tirar o folego acabam vencendo o braco direito\n"
		    << "     de Nilats e seu poderoso dragao e no topo da colina ja e possivel visualizar\n"
			<< "  o castelo do inimigo. Mas nem tudo e motivo de comemoracao nesse momento de gloria.\n"
			<< "Com a morte de Minus, a regiao esta toda alertada e nao havera caminho percorrivel\n"
			<< "senao pela porta da frente do castelo,onde os desafios do coliseu de Nilats ja esperam\n"
			<< "pelos nossos herois.\n"
		    << "Serao eles capazes de vencer os desafios do coliseu e travarem a sua batalha final?\n\n\n" << endl;

	int ch;

	file = fopen("Vista castelo.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	_getch();system("pause");system("cls");

	fclose(file);
}

void Dragoneer::status()
{
	if(isDefeated == false){
		cout << "--------------------------------------------------------------------------------------";
		cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life1 << "/"  <<  lifeTotal1 << "\t"  <<  endl;
		cout << "\t\t" << "Velocidade: " << speed1 << "\t" << "Forca: " << force1 << "\t" <<  "Resistencia: " << resistance1 << endl;
		cout << "--------------------------------------------------------------------------------------";
	}
	else{
		cout << "--------------------------------------------------------------------------------------";
		cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life1 << "/"  <<  lifeTotal1 << "\t"  <<  endl;
		cout << "\t\t" << "Velocidade: " << speed1 << "\t" << "Forca: " << force1 << "\t" <<  "Resistencia: " << resistance1 << endl;
		cout << "--------------------------------------------------------------------------------------";
	}
}

int Dragoneer::attack()
{
	luck = rand()%10;

	if(luck == 0){
		return 0;
	}
	else if(luck <= 7){
		if(luck > 4)
			luck = 4;
		int tmp = ((force1 + luck) % (force1 + luck + 1));
		int damage = (tmp) > (force1) ? (tmp) : (force1 + 1);
		return  damage;
	}
	else if(luck == 8){
		return force1 + 10;
	}
	else if(luck == 9){
		if(force1 + (luck * 2) > force1 * 2)
			return force1 + (luck * 2) + 2;
		else 
			return force1 * 2;
	}

	return -1;
}

int Dragoneer::defense(int damage)
{
	if(damage < resistance1/2)
		return 0;
	else if(damage <= resistance1){
		life1 -= damage / 2;
		return 1;
	}
	else if(damage > resistance1)
		life1 -= damage;

	return 2;
}

void Dragoneer::image()
{
	int ch;

	if(isDefeated == false)
		file = fopen("Milus.txt", "r");
	else
		file = fopen("Dragon.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int Dragoneer::getSpeed()
{
	return speed1;
}

int Dragoneer::getLuck()
{
	return luck;
}

int Dragoneer::getLife()
{
	return life1;
}

char *Dragoneer::getName()
{
	return nome;
}

bool Dragoneer::setNew()
{
	if(isDefeated == false){
		isDefeated = true;
		char *tmp = "Shruikan, the Milus Dragon";
		strcpy_s(nome,tmp);

		force1 = 35;
		resistance1 = 15;
		speed1 = 30;

		lifeTotal1 = 500;
		life1 = lifeTotal1;
	}
	else if(isDefeated == true){
		isDefeated = false;
	}

	return isDefeated;
}