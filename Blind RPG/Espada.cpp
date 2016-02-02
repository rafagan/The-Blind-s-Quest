#include "Espada.h"
#include <iostream>

using namespace std;

Espada::Espada(char nome[100])
	   : Personagem(nome)
{
	this->haveArmor = true;
}

void Espada::status()
{
	cout << endl << endl << "--------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t" << "Experiencia: " << xp << endl;
	cout << "\t" << "Posicao: " << "(" << pos[0]-2 << "," << pos[1] << ")" << "\t" << "Level: "<< level << endl;
	cout << "Equipamento: "<< arma << " " << defesa << endl; 
	cout << "--------------------------------------------------------------------------------" << endl;
}

void Espada::attack()
{
	cout << "Atacando com " << arma << endl;
}

void Espada::defense()
{
	cout << "Defendendo com: " << defesa << endl;
}
