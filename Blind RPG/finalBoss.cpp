#include "finalBoss.h"


#include <conio.h>

using namespace std;

finalBoss::finalBoss()
{
	char *tmp = "Nilats - Dragon Mode";
	strcpy_s(nome,tmp);

	force = 100;
	resistance = 100;
	speed = 100;
	lifeTotal = 10000;
	life = lifeTotal;
}

finalBoss::~finalBoss()
{
	system("cls");

	cout    << "\n\n\n   O castelo comeca a se render ao meio da destruicao causada pelo combate.\n"
		    << "   Aos poucos, Nilats ia retornando a sua forma demoniaca, porem sem vida.\n"
			<< "  Suas ultimas palavras amaldicoariam todas as proximas geracoes de nossos\n"
			<< "    herois, mas nesse momento nada importava senao escapar daquele local\n"
			<< "     repugnante. Em um ato inusitado, Argorn e Tyson capturam o bau que\n"
			<< "         se encontrava no fim do corredor e partem em retirada.\n\n"
			<< "Olhando para os escombros do castelo, os herois finalmente tem a certeza\n"
			<< "de que tudo acabou e que poderao voltar para casa...\n\n"
			<< "Mas antes de partirem, resolvem conferir o conteudo do bau. Eis entao que\n"
			<< "se surpreendem com o conteudo! Era um ovo de dragao... E estava prestes a\n"
		    << "nascer!!!\n\n\n" << endl;

	int ch;

	file = fopen("End bau.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	printf("\n");
	_getch();system("pause");system("cls");

	fclose(file);
}


void finalBoss::status()
{
	cout << "--------------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t\t\t\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t"  <<  endl;
	cout << "\t\t" << "Velocidade: " << speed << "\t" << "Forca: " << force << "\t" <<  "Resistencia: " << resistance << endl;
	cout << "--------------------------------------------------------------------------------------";
}

int finalBoss::attack()
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

int finalBoss::defense(int damage)
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

void finalBoss::image()
{
	int ch;

	file = fopen("Boss Fm.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}

int finalBoss::getSpeed()
{
	return speed;
}

int finalBoss::getLuck()
{
	return luck;
}

int finalBoss::getLife()
{
	return life;
}

char *finalBoss::getName()
{
	return nome;
}
