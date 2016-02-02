#include "Escudo.h"
#include <iostream>

using namespace std;

Escudo::Escudo(char nome[100])
	   : Personagem(nome)
{
	this->haveShield = true;
}

void Escudo::status()
{
	cout << endl << endl << "--------------------------------------------------------------------------------";
	cout  <<  nome << ":" << endl << "\t" << "Vida: " << life << "/"  <<  lifeTotal << "\t" << "Experiencia: " << xp << endl;
	cout << "\t" << "Posicao: " << "(" << pos[0]-2 << "," << pos[1] << ")" << "\t" << "Level: "<< level << endl;
	
}

void Escudo::attack()
{
	cout << "Atacando com " << arma << endl;
}

void Escudo::defense()
{
	cout << "Defendendo com: " << defesa << endl;
}