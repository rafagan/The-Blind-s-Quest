#include "Nilats.h"
#include <conio.h>

using namespace std;

Nilats::Nilats()
{
	char *tmp = "Nilats, The Evil";
	strcpy_s(nome,tmp);

	force = 50;
	resistance = 50;
	speed = 40;
	lifeTotal = 1000;
	life = lifeTotal;
}

Nilats::~Nilats()
{
	system("cls");

	cout    << "\n\n     Nilats, como um verme nojento e desprezivel comeca a exibir os principais\n"
		    << "          sinais da morte. Nem mesmo chegou a se debrucar ao chao e ja e possivel\n"
			<< "        sentir o cheiro putrefato de morte exalado pelo seu corpo. Mas antes que\n"
			<< "        nossos herois pudessem se orgulhar, Nilats retoma a postura e foge para\n"
		    << "              o interior do castelo. E o fim???\n\n\n" << endl;

	int ch;

	file = fopen("Corredor.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	_getch();system("pause");system("cls");

	fclose(file);
}


void Nilats::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	cout << "--------------------------------------------------------------------------------------";
}

int Nilats::attack()
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

int Nilats::defense(int damage)
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

void Nilats::image()
{
	int ch;

	file = fopen("BossFst.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int Nilats::getSpeed()
{
	return speed;
}

int Nilats::getLuck()
{
	return luck;
}

int Nilats::getLife()
{
	return life;
}

char *Nilats::getName()
{
	return nome;
}