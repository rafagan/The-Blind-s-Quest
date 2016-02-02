#include "Personagem.h"
#include <iostream>
#include <cstring>
#include <conio.h>

using namespace std;

Personagem::Personagem()
{
}
Personagem::~Personagem()
{
	fclose(file);
}

void Personagem::inicializa()
{
	this->lifeTotal = life = 100;
	this->xp = 0;
	this->level = 1;
	this->xpForNextLevel = 20;
	this->haveArmor = this->haveSword = this->haveShield = this->haveMPunch = this->haveHPunch = false;
	this->speed = 1;
	this->force = this->resistance = 5;
	this->points = 0;
	this->bonusArmor = this->bonusSword = 0;
	this->potions = 3;

	this->arma = "Soco fraco";
	this->escudo = "Nenhum";
	this->armor = "Nenhum";

	this->setPos(2,0);
}


void Personagem::movDown()
{
	this->pos[0] += 1;
}
void Personagem::movUp()
{
	this->pos[0] -= 1;
}
void Personagem::movRight()
{
	this->pos[1] += 1;
}
void Personagem::movLeft()
{
	if(this->pos[1] - 1 >= 0)
		this->pos[1] -= 1;
	else{
		cout << "\nEste nao e o caminho correto" << endl;
		_getch();
	}
}


int Personagem::getLuck() const
{
	return luck;
}
int Personagem::getSpeed() const
{
	return speed;
}
int Personagem::getLevel() const
{
	return level;
}
int Personagem::getXP() const
{
	return xp;
}
int const *Personagem::getPosition()
{
	return pos;
}
int Personagem::getTotalLife() const
{
	return lifeTotal;
}
int Personagem::getLife() const
{
	return life;
}
char const *Personagem::getName()
{
	return nome;
}


void Personagem::setXP(int _xp)
{
	this->xp += _xp;

	while(xpForNextLevel <= xp){
		if(this->xpForNextLevel <= xp && level < 6){
			xpForNextLevel*=2;
			this->levelUp();
		}
		else if(this->xpForNextLevel <= xp && level < 9){
			xpForNextLevel += 320;
			this->levelUp();
		}
		else if(this->xpForNextLevel <= xp && level == 9){
			xpForNextLevel += 400;
			this->levelUp();
		}
		else if(level == 10)
			xp -= _xp;
	}
}
void Personagem::setName(char _nome[100])
{
	strcpy_s(nome,_nome);
}
void Personagem::setPos(int x,int y)
{
	this->pos[0] = x;
	this->pos[1] = y;
}
int Personagem::setRest()
{
	if(isResting){
		int tmp = (rand() % (resistance + 1)) + resistance/2;

		life += tmp;

		if(life > lifeTotal)
			life = lifeTotal;

		isResting = false;

		return tmp;
	}

	return 0;
}

void Personagem::usingPotion()
{
	if(potions > 0){
		if(life == lifeTotal)
			cout << "\nVoce esta com a vida maxima, nao precisa usar pocao agora" << endl;
		else{
			life += 50;
			potions--;
			cout << "\nPocao usada com sucesso" << endl;
			if(life > lifeTotal)
				life = lifeTotal;
		}
	}
	else
		cout << "\nVoce nao possui mais pocoes disponiveis" << endl;
}

void Personagem::addPotion()
{
	system("cls");
	potions++;
	this->imgPotion();
}


void Personagem::imgLevelUp()
{
	int ch;

	file = fopen("Level up.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	cout << "\n\n" << endl;

	file = fopen("Personagens.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
}
void Personagem::imgShield()
{
	int ch;

	cout << "Voce encontrou: \n\t\t\t\t   AEGIS SHIELD" << endl << endl;

	file = fopen("Shield.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	cout << endl << endl << "\t\tEste escudo foi forjado com um metal ancestral\n\t magico manipulado por anoes. Sera perfeito para sua missao!" << endl;
}
void Personagem::imgSword()
{
	int ch;

	cout << "Voce encontrou: \n\t\t\t\t   KUSANAGI SWORD" << endl << endl;

	file = fopen("Sword.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	cout << endl << endl << "\t  Espada lendaria usada para combater o Deus serpente Orochi\n\t Leve-a com voce para poder combater inimigos mais perigosos!" << endl;
}
void Personagem::imgArmor()
{
	int ch;

	cout << "Voce encontrou: \n\t\t\t\tSIEGFRIED'S ARMOR" << endl << endl;

	file = fopen("Armor.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	cout << endl << endl << "\t  A armadura indestrutivel que foi banhada com o sangue de um dragao\n\t\t\t Use-a para ficar mais protegido!" << endl;
}
void Personagem::imgPotion()
{
	int ch;

	cout << "Voce encontrou: \n\t\t\t\t    POCAO" << endl << endl;

	file = fopen("Potion.txt", "r");

	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	cout << endl << endl << "   Pocao provavelmente derrubada por um mercador ou esquecida por alguma infantaria\n\t\t\tAumenta seus lifepoints em 50" << endl;
}


void Personagem::equipament(int equip)
{
	if(equip == 0){
		escudo = NULL;
		escudo = "Aegis";
		system("cls");
		this->imgShield();
		_getch();
		this->haveShield = true;

		if(level <= 3)
			bonusShield = 5;
		else if(level <= 6)
			bonusShield = 10;
		else if(level <= 9)
			bonusShield = 15;
		else if(level == 10)
			bonusShield = 20;
	}
	else if(equip == 1){
		arma = NULL;
		arma = "Kusanagi    ";
		system("cls");
		this->imgSword();
		_getch();
		this->haveSword = true;
		this->haveMPunch = this->haveHPunch = false;

		if(level <= 3)
			bonusSword = 5;
		else if(level <= 6)
			bonusSword = 10;
		else if(level <= 9)
			bonusSword = 15;
		else if(level == 10)
			bonusSword = 20;
	}
	else if(equip == 2){
		armor = NULL;
		armor = "Siegfried";
		this->haveArmor = true;
		system("cls");
		this->imgArmor();
		_getch();

		if(level <= 8)
			bonusArmor = 10;
		else if(level >= 9)
			bonusArmor = 20;
	}
}


void Personagem::status()
{
	cout << endl << endl << "--------------------------------------------------------------------------------------";
	cout << nome << ":" << endl;
	cout << "\t\t" << "Vida: " << life << "/" << lifeTotal;
	cout << "\t\t" << "Level: "<< level;
	if(speed < 50)
		cout << "\t\t" << "Velocidade: " << speed << endl;
	else
		cout << "\t\t" << "Velocidade: " << "MAX" << endl;
	cout << "\t\t" << "Posicao: " << "(" << pos[0]-2 << "," << pos[1] << ")"; 
	if(level != 10)
		cout << "         " << "Experiencia: " << xp << "/" << xpForNextLevel;
	else if(level == 10)
		cout << "\t\t" << "Experiencia: MAX";
	if(force < 50)
		cout << "\t" << "Forca: " << force;
	else
		cout << "\t" << "Forca: " << "MAX"; 
	if(haveSword)
		cout << " + " << bonusSword << endl;
	else if(haveHPunch)
		cout << " + 5" << endl;
	else if(haveMPunch)
		cout << " + 3" << endl;
	else
		cout << endl;
	if(resistance < 50)
		cout << "\t\t\t\t\t\t\t\t"  <<  "Resistencia: " << resistance;
	else
		cout << "\t\t\t\t\t\t\t\t"  <<  "Resistencia: " << "MAX";
	if(haveArmor)
		cout << " + " << bonusArmor << endl;
	else
		cout << endl;
	cout << "Equipamento: "<< endl << "\t\t" << "Arma: "<< arma << "\t" << "Armadura: " << armor << "\t" << "Escudo: " << escudo << endl; 
	cout << "\nPocoes: " << potions << endl;
	if(haveShield)
		cout << "\nHabilidade com o escudo: " << bonusShield << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;
}

int Personagem::attack()
{
	cout << endl;
	cout << "Atacando com " << arma << endl;

	int forceArm = 0;

	if(this->haveMPunch)
		forceArm = 3;
	else if(this->haveHPunch)
		forceArm = 5;
	else if(this->haveSword)
		forceArm = this->bonusSword;

	luck = rand()%10;

	if(luck == 0){
		return 0;
	}
	else if(luck <= 7){
		int tmp = ((force + luck) % (force + luck + 1));
		int damage = ((tmp) > (force) ? (tmp) : (force + 1)) + forceArm;
		return  damage;
	}
	else if(luck == 8){
		return (force + (luck * 2)) + forceArm;
	}
	else if(luck == 9){
		if(force + (luck * 2) > force * 2)
			return (force + (luck * 2) + 2) + forceArm;
		else 
			return (force * 2) + forceArm;
	}

	return -1;
}

int Personagem::defense(bool _isResting,int &damage)
{
	int armorResist = 0;

	if(haveArmor){
		armorResist = this->bonusArmor;
	}

	isResting = _isResting;

	if(isResting){
		int realDamage = damage - bonusShield;

		if(haveShield){
			cout << "\nDefendendo com " << escudo << endl;

			if(realDamage < (resistance/2) + armorResist)
				return 0;
			else if(realDamage <= resistance + armorResist){
				damage = (damage - bonusShield) / 2;
				life -= damage;
				return 1;
			}
			else if(realDamage > resistance + armorResist){
				life -= damage;
				return 2;
			}
		}
		else{
			cout << nome << " nao possui nenhum escudo no momento. Com um escudo tera mais chances de ter\numa defesa mais efetiva!" << endl;
			return (this->defense(damage));
		}
	}

	return -1;
}

int Personagem::defense(int damage)
{
	int armorResist = 0;

	if(haveArmor){
		armorResist = this->bonusArmor;
	}

	if(damage < (resistance/2) + armorResist)
		return 0;
	else if(damage <= resistance + armorResist){
		life -= damage / 2;
		return 1;
	}
	else if(damage > resistance + armorResist){
		life -= damage;
	}

	return 2;
}

//***MÉTODOS PRIVADOS***

void Personagem::setAtributes()
{
	char op;
	bool isOnFirst = true;

	while(points > 0){

		this->imgLevelUp();
		if(isOnFirst){
			_getch();
			isOnFirst = false;
		}
		cout << "\n\n" << endl;
		cout << "\t\t\t\tVOCE ESTA NO LEVEL: " << level << endl;
		cout << endl << "Quantidades de pontos recebidos: " << points << endl << endl;
		cout << "Em qual atributo voce deseja investir? " << endl << endl;
		if(force < 50)
			cout << "1- Forca: " << this->force << endl;
		else
			cout << "1- Forca: " << "MAXIMO ALCANCADO" << endl;
		if(resistance < 50)
			cout << "2- Resistencia: " << this->resistance << endl;
		else
			cout << "2- Resistencia: " << "MAXIMO ALCANCADO" << endl;
		if(speed < 50)
			cout << "3- Velocidade: " << this->speed << endl;
		else
			cout << "3- Velocidade: " << "MAXIMO ALCANCADO" << endl;
	
		op = _getch();

		switch(op){
		case '1':
			force++;
			if(force > 50){
				cout << "Forca Maxima alcancada" << endl;
				_getch();
				force--;
				points++;
			}
			points--;
			break;
		case '2':
			resistance++;
			if(resistance > 50){
				cout << "Resistencia Maxima alcancada" << endl;
				_getch();
				resistance--;
				points++;
			}
			points--;
			break;
		case '3':
			speed++;
			if(speed > 50){
				cout << "Velocidade Maxima alcancada" << endl;
				_getch();
				speed--;
				points++;
			}
			points--;
			break;
		default:
			cout << "Opcao invalida" << endl;
		}
		
		system("cls");
	}
}

void Personagem::levelUp()
{
	if(level < 11){
		level += 1;

		if(level <= 3){
			this->lifeTotal += 25;
			life = lifeTotal;
			points = 5;
			bonusSword = 5;
			bonusShield = 5;
			bonusArmor = 10;
		}
		else if(level <= 6){
			lifeTotal += 50;
			life = lifeTotal;
			points = 10;
			bonusSword = 10;
			bonusShield = 10;
			bonusArmor = 10;
		}
		else if(level == 7){
			lifeTotal += 100;
			life = lifeTotal;
			points = 15;
			bonusSword = 15;
			bonusShield = 15;
			bonusArmor = 10;
		}
		else if(level == 8){
			lifeTotal += 200;
			life = lifeTotal;
			points = 15;
			bonusSword = 15;
			bonusShield = 15;
			bonusArmor = 10;
			bonusArmor = 10;
		}
		else if(level == 9){
			lifeTotal += 250;
			life = lifeTotal;
			points = 30;
			bonusSword = 15;
			bonusShield = 15;
			bonusArmor = 10;
			bonusArmor = 20;
		}
		else if(level == 10){
			lifeTotal = 1000;
			life = lifeTotal;
			force = resistance = 130;
			speed = 150; 
			bonusSword = 20;
			bonusShield = 20;
			bonusArmor = 20;
		}

		if(level == 3 && haveSword == false){
			this->haveMPunch = true;
			arma = NULL;
			arma = "Soco Medio";
		}
		if(level == 5 && haveSword == false){
			this->haveHPunch = true;
			this->haveMPunch = false;
			arma = NULL;
			arma = "Soco Forte";
		}
	}

	this->setAtributes();
}