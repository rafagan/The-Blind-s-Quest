#pragma once
#include <iostream> 

// **INTERFACE DOS INIMIGOS**

//Todos os inimigos apresentam os metodos aqui apresentados

class Inimigo
{
public:
	//Exibe o status do inimigo
	virtual void status() = 0;
	
	//Gerencia o ataque do inimigo
	virtual int attack() = 0;
	//Gerencia a defesa do inimigo
	virtual int defense(int damage) = 0;

	//Exibe a imagem do inimigo
	virtual void image() = 0;

	//Retorna a velocidade do inimigo
	virtual int getSpeed() = 0;
	//Retorna a sorte do inimigo
	virtual int getLuck() = 0;
	//Retorna a vida do inimigo
	virtual int getLife() = 0;
	//Retorna o nome do inimigo
	virtual char *getName() = 0;

	//Indica se o inimigo esta perseguindo voce ou nao (usado apenas pela Beast)
	virtual bool setPursuit() { return false;};
	//Indica se o inimigo esta drenando sua vida (usado apenas pela Death)
	virtual void setDrainPower(int machineryState,int damage) {};
	//Seta o novo inimigo que sera combatido pelo personagem
	virtual bool setNew() {return false;};

	//Chama o destrutor de todas as classes filhas
	virtual ~Inimigo() {};
};

