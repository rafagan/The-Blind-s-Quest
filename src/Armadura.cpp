#include "Armadura.h"
#include <iostream>

using namespace std;

Armadura::Armadura(char nome[100])
	   : Personagem(nome)
{
	this->haveArmor = true;
	this->defesa = "Armad";
}

void Armadura::status()
{
	cout << endl << endl << "--------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t" << "Experiencia: " << xp << endl;
	cout << "\t" << "Posicao: " << "(" << pos[0]-2 << "," << pos[1] << ")" << "\t" << "Level: "<< level << endl;
	cout << "Equipamento: "<< arma << " " << defesa << endl; 
	cout << "--------------------------------------------------------------------------------" << endl;
}

void Armadura::attack()
{
	cout << "Atacando com " << arma << endl;
}

void Armadura::defense()
{
	cout << "Defendendo com: " << defesa << endl;
}
