#pragma once
#include <iostream>

class Personagem
{
public:
	//Construtor
	Personagem();
	//Anula o ponteiro do arquivo de texto e desaloca memoria
	~Personagem();

	//Inicializa os atributos iniciais do personagem toda a vez que o jogo comeca
	void inicializa();

	//Move a coordenada para baixo
	void movDown();
	//Move a coordenada para cima
	void movUp();
	//Move a coordenada para a direita
	void movRight();
	//Move a coordenada para a esquerda e verifica se o personagem saiu do escopo do jogo
	void movLeft();
	
	//Informa a sorte
	int getLuck() const;
	//Informa a velocidade
	int getSpeed() const;
	//Informa o level
	int getLevel() const;
	//Informa a experiencia
	int getXP() const;
	//Informa a posicao
	int const *getPosition();
	//Informa o maximo de vida que se pode ter
	int getTotalLife() const;
	//Informa a vida atual
	int getLife() const;
	//Informa o nome
	char const *getName();
	
	//Seta a experiencia
	void setXP(int xp);
	//Seta um novo nome
	void setName(char nome[100]);
	//Seta a posicao
	void setPos(int x,int y);
	//Calcula o valor recuperado de life com o descanso
	int setRest();
	
	//Adiciona o valor de uma pocao a vida
	void usingPotion();
	//Adiciona uma pocao ao estoque
	void addPotion();

	//Metodos para impressao de imagens
	void imgShield();
	void imgSword();
	void imgArmor();
	void imgLevelUp();
	void imgPotion();

	//Seta e gerencia os equipamentos e os seus respectivos atributos
	void equipament(int equip);

	// **METODOS DE BATALHA**
	//Status do personagem
	void status();
	//Gerencia o ataque
	int attack();
	//Gerencia a defesa ao receber um ataque do inimigo
	int defense(int damage);
	//Gerencia a defesa ao utilizar um escudo
	int defense(bool isResting, int &damage);

private:
	//PRIVADO: Seta e gerencia os pontos recebidos
	void setAtributes();
	//Gerencia as configuracoes para a passagem de nivel
	void levelUp();

	//PRIVADO!
	char nome[30];
	//PRIVADO!
	int pos[2];
	//PRIVADO!
	int lifeTotal,life;
	//PRIVADO!
	int xp,xpForNextLevel;
	//PRIVADO!
	int level;
	//PRIVADO!
	int speed,resistance,force,luck;
	//PRIVADO!
	char *arma,*escudo,*armor;
	//PRIVADO!
	bool haveMPunch,haveHPunch;
	//PRIVADO!
	bool haveArmor,haveSword,haveShield,isResting;
	//PRIVADO!
	int bonusArmor,bonusSword,bonusShield;
	//PRIVADO!
	int points;
	//PRIVADO!
	int potions;
	//PRIVADO!
	FILE *file;
};

