#include <cstdlib>
#include "conio.h"
#include "Personagem.h"
#include "Soldier.h"
#include "Beast.h"
#include "Giant.h"
#include "Death.h"
#include "Dragoneer.h"
#include "Nilats.h"
#include "finalBoss.h"
#include <ctime>

//P = PAREDE
//C = CAMINHO LIVRE
//J = PERSONAGEM PRINCIPAL
//A = INIMIGO FRACO
//M = INIMIGO MEDIO
//H = INIMIGO FORTE
//B = BOSS1
//G = BOSS2
//N = BOSS3
//K = ESPADA
//Z = ESCUDO
//L = POÇÃO
//D = ARMADURA
//W = POSIÇÃO FINAL

using namespace std;

const int LARGURA = 81;
const int ALTURA = 30;
const char j=2,c=176,p=219,a=15,m=20,h=21,b=1,g=37,n=33,l=3,k=6,z=64,w=4,d=157;

//Configure antes de jogar...
void config();
//Tela de inicio
void abertura(bool opening);
// **FUNCOES PARA O MENU**
//Gerencia o menu
bool Menu(Personagem &pe);
  //Gerencia o inicio do jogo
  bool startGame(Personagem &pe);
  //Gerencia a historia do game
  void history();
  //Gerencia como jogar
  void htp();
  //Gerencia os creditos
  void credits();
//Opcoes de movimentacao
void opcoes();
//***FUNÇÕES PARA O PROCESSAMENTO DA LÓGICA DO JOGO***
//Processa as escolhas realizadas
void escolha(Personagem &pe, int op, char mapa[ALTURA][LARGURA],char blindMap[ALTURA][LARGURA],bool &menu);
  //Auxilia o processamento das escolhas
  void switchOp(Personagem &pe, int op, bool &menu);
  //**PROCESSA O SISTEMA DE BATALHAS***
  bool battleStart(Personagem &pe,char inimigo);
    //Batalha Personagem -> Inimigo
    int combat_P_I(Personagem &pe, Inimigo *e,char inimigo,int damage,int machineryState);
	//Batalha Inimigo -> Personagem
    int combat_I_P(Personagem &pe, Inimigo *e,char inimigo,int damage,int machineryState);
	//Batalha com Personagem usando a defesa
	int combat_Defense(Personagem &pe, Inimigo *e,char inimigo,int damage,int machineryState);

//Exibe o fim do jogo
bool theEnd();

int main()
{		
	//****DECLARACAO DAS VARIAVEIS****
	int state = 0;
	int op;
	bool opening = true,menu = true;
	srand((unsigned int) time(NULL)); 
	Personagem personagem;
	const char constMap1[ALTURA][LARGURA] = {
	p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,'\n',
	p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,'\n',
	j,c,c,c,p,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,l,l,l,c,c,c,c,c,p,0,0,p,c,c,c,w,c,c,c,p,p,p,'\n',
	c,c,c,c,p,0,0,0,0,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,c,c,c,c,p,p,p,p,p,p,c,p,p,p,p,p,p,p,p,p,p,p,p,p,c,p,0,0,0,p,c,c,c,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,p,l,p,c,c,c,c,p,h,p,d,p,p,c,p,0,0,0,0,0,0,0,0,0,0,0,p,c,p,0,0,0,0,p,c,n,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,p,p,p,p,p,p,p,l,p,p,p,p,p,p,p,p,p,p,p,p,p,c,c,c,c,p,c,p,c,c,c,c,p,c,c,c,c,p,g,p,0,0,0,0,0,0,0,0,0,0,0,p,c,p,0,0,0,0,0,p,c,p,0,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,0,p,c,p,0,0,0,0,0,0,0,0,0,0,0,p,c,c,c,c,p,c,p,c,c,c,c,p,c,c,c,c,p,c,p,0,0,0,0,0,0,0,0,0,0,0,p,c,p,0,0,0,0,0,p,c,p,0,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,0,p,c,p,0,0,0,0,p,p,p,0,0,0,0,p,a,c,c,c,p,c,p,c,c,c,l,p,c,c,c,c,p,c,p,0,0,0,0,0,0,0,0,0,0,0,p,c,p,0,0,0,0,0,p,c,p,0,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,m,m,p,0,0,0,0,0,0,p,b,p,0,0,0,0,p,l,p,0,0,0,0,p,c,a,c,c,p,h,p,c,c,c,c,p,p,h,c,l,p,c,p,0,0,0,0,0,0,0,0,0,p,p,p,c,p,0,0,0,0,0,p,h,p,0,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,0,p,c,p,0,0,0,0,p,l,p,0,0,0,0,p,c,c,a,c,p,c,p,c,c,c,c,p,p,c,p,p,p,c,p,p,0,0,0,0,0,0,0,0,p,c,c,c,p,0,0,0,0,0,p,m,p,0,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,0,p,c,p,0,0,0,0,p,m,p,0,0,0,0,p,c,c,c,a,p,c,p,p,c,p,p,p,p,c,p,c,c,c,c,p,0,0,0,0,p,p,p,p,p,c,p,p,p,p,0,0,0,p,p,a,p,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,p,p,c,p,p,0,0,0,p,m,p,0,0,0,0,p,c,c,c,c,p,c,c,p,c,p,p,c,c,c,p,p,c,c,p,p,0,0,0,0,p,l,c,c,c,c,c,c,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,p,c,c,p,0,0,0,0,0,p,a,a,a,p,0,0,0,p,c,p,0,0,0,0,p,c,c,m,c,p,c,c,p,c,p,p,c,c,c,l,p,c,c,p,0,0,0,0,0,p,c,c,m,c,c,m,c,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,a,p,0,0,0,0,p,c,c,p,0,0,0,0,0,p,a,a,a,p,0,0,0,p,c,p,0,0,0,0,p,c,c,c,c,p,c,p,p,c,p,p,c,c,c,c,p,c,c,p,0,0,0,0,0,p,c,h,c,c,c,c,m,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,p,p,p,c,c,p,p,p,0,0,0,p,c,c,c,p,0,0,0,p,c,p,0,0,0,0,p,c,c,a,c,p,c,p,c,c,p,c,c,c,c,p,p,c,c,p,p,0,0,0,0,p,c,c,c,c,m,c,c,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,p,c,a,c,c,c,l,p,0,0,0,p,c,c,c,p,0,0,0,p,c,p,p,p,p,p,p,c,c,l,c,p,c,p,c,c,p,c,c,c,c,p,c,m,c,c,p,0,0,0,0,p,c,c,c,c,h,c,h,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,p,c,c,c,c,a,c,p,0,0,0,p,c,c,c,p,0,0,0,p,c,c,c,c,c,c,c,c,m,c,a,p,c,c,c,c,p,c,p,p,c,p,l,a,c,c,p,0,0,0,0,p,m,c,c,c,c,c,c,c,p,0,0,0,p,c,c,c,p,0,0,p,p,'\n',
	p,p,c,c,p,0,0,p,c,a,c,c,c,c,p,0,0,0,p,c,a,c,p,0,0,0,p,c,p,p,p,p,p,p,c,c,c,c,p,p,p,p,c,p,c,p,p,c,p,a,a,m,c,p,0,0,0,0,p,c,h,c,c,h,c,c,c,p,0,0,p,p,c,l,c,p,p,0,p,p,'\n',
	p,p,a,c,p,0,0,p,c,c,c,a,c,l,p,0,0,0,p,c,c,c,p,0,0,0,p,c,p,0,0,0,0,p,c,c,a,c,p,c,c,p,c,p,c,p,p,c,p,l,a,c,c,p,0,0,0,0,p,c,c,c,m,c,c,m,l,p,0,0,p,c,c,l,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,p,c,c,a,c,c,a,p,0,0,0,p,c,c,c,p,0,0,0,p,c,p,p,p,p,0,p,c,c,c,c,p,c,c,c,c,c,c,p,p,c,p,m,m,m,m,p,0,0,0,0,p,c,l,c,c,c,c,c,c,p,0,0,p,c,c,l,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,p,a,c,c,c,c,c,p,0,0,0,p,c,c,c,p,0,0,0,p,c,m,h,k,p,0,p,c,a,c,c,p,c,c,p,c,p,p,p,p,c,p,c,c,c,c,p,0,0,0,0,p,c,c,h,c,h,c,h,c,p,0,0,p,c,c,l,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,p,c,c,z,c,a,c,p,0,0,0,p,a,c,a,p,0,0,0,p,p,p,p,p,p,0,p,c,c,c,c,p,c,c,c,c,p,l,p,p,h,p,c,m,m,c,p,0,0,0,0,p,m,c,c,c,c,m,c,c,p,0,0,p,c,c,l,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,p,p,p,p,p,p,p,p,0,0,0,p,c,c,c,p,0,0,0,0,0,0,0,0,0,0,p,c,c,m,c,p,c,c,p,p,p,h,p,p,c,p,c,c,c,c,p,0,0,0,0,p,c,h,c,c,c,c,m,c,p,0,0,p,c,c,l,c,c,p,0,p,p,'\n',
	p,p,c,c,p,0,0,0,0,0,0,0,0,0,0,0,0,0,p,c,c,c,p,0,p,p,p,p,p,0,0,0,0,p,p,c,c,c,p,p,c,c,c,c,c,p,p,l,p,m,c,c,m,p,0,0,0,0,p,c,c,c,h,h,h,c,c,p,0,0,p,c,c,c,c,c,p,0,p,p,'\n',
	p,p,c,c,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,c,c,c,p,0,p,l,a,l,p,0,0,0,p,p,c,c,c,c,c,p,p,p,p,p,p,p,p,p,p,c,c,c,c,p,0,0,0,0,p,p,p,p,h,h,h,p,p,p,p,p,p,c,c,c,c,c,p,0,p,p,'\n',
	p,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,a,c,c,c,p,0,p,m,a,m,p,p,p,p,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,p,0,0,0,0,0,0,0,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,p,0,p,p,'\n',
	p,p,c,c,c,c,c,c,a,c,c,c,c,c,c,c,c,c,c,c,c,c,p,0,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,p,0,0,0,0,0,0,0,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,0,p,p,'\n',
	p,p,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,a,c,c,c,p,0,p,l,l,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,p,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,p,p,'\n',
	p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,'\n',
	p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,'\n'};
	char mapa[ALTURA][LARGURA];
	char blindMap[ALTURA][LARGURA];
	//***FIM DA DECLARACAO DE VARIAVEIS****

	//Configure a tela...
	config();

	//GAME LOOP
	do{
		//***MENU***
		while(menu){
			//Abertura
			if(state == 0){
				abertura(opening);
				state = 1;
			}

			system("cls");
			menu = Menu(personagem);

			//Inicializa as configuracoes basicas do jogo caso o processamento do menu tenha acabado
			if(menu == false){
				//Inicializa o personagem
				personagem.inicializa();

				//Inicializa o mapa usado para a logica
				for(int i=0;i<ALTURA;i++){
					for(int i2=0,count=0;i2<LARGURA;i2++)
						mapa[i][i2] = constMap1[i][i2];
				}
				//Inicializa o mapa usado apra desenho
				for(int i=0;i<ALTURA;i++){
					for(int i2=0,count=0;i2<LARGURA;i2++){
						if(mapa[i][i2] == j)
							blindMap[i][i2] = 1;
						else
							blindMap[i][i2] = 0;
					}
				}
				//Identifica e exibe os limites do mapa
				for(int i=0;i<ALTURA;i++){
					for(int i2=0,count=0;i2<LARGURA;i2++){
						if(i == 0)
							blindMap[i][i2] = 1;
						if(i == ALTURA-1)
							blindMap[i][i2] = 1;
						if(i2 == LARGURA-2)
							blindMap[i][i2] = 1;
					}
				}
			
			state = 0;
			}
		}
		//***FIM DO MENU***

		//DESENHA O MAPA NA TELA
		for(int i=0;i<ALTURA;i++){
			for(int i2=0,count=0;i2<LARGURA;i2++,count++){
				if(count % LARGURA == 0){
					if(i == 2 || i == 3)
						printf("%c%c%c",c,c,c);
					else
						printf("  %c",p);
				}
				if(mapa[i][i2] == '\n')
					cout << mapa[i][i2];
				else if(blindMap[i][i2] == 1)
					cout << mapa[i][i2];
				else
					cout << '?';
			}
		}

		//CALCULA E PROCESSA A LOGICA
		personagem.status();
		opcoes();
		op = _getch();
		if(op == 27)
			exit(1);
		else if(op == 49){
			cout << '\7';
			escolha(personagem,op,mapa,blindMap,menu);
		}
		else if(op == 224){
			op = _getch(); //setas pegam dois bytes. O primeiro tem valor 224, e o segundo o código da seta
			escolha(personagem,op,mapa,blindMap,menu);
		}
		system("cls");

	}while(true);

	//FINALIZA O PROGRAMA
	return 0;
}


void config()
{
	FILE *file;
	int ch;

	cout << "Voce esta quase pronto...\n" << endl;
	cout << "Antes de comecar, clique com o botao direito encima da barra do seu prompt de comando" << 
		    " e certifique-se de que seu layout esta com as seguntes configuracoes:\n" << endl;
	cout << "   Largura do buffer: 86" << endl;
	cout << "   Altura do buffer:  120" << endl;
	cout << "   Largura da janela: 86" << endl;
	cout << "   Altura da janela:  70" << endl << endl;
	cout << "   Centralize sua tela configurando a posicao da janela nessa mesma aba\n" << endl;
	cout << "          Agora voce ja pode se divertir sem mais complicacoes! \n                    Obrigado por jogar e boa aventura!!!" << endl;
	cout << "\n\n\n           COPYRIGHT: ALL RIGHTS RESERVED TO RAFAGAN SEBASTIAN DE ABREU\n\n\n" << endl;
	file = fopen("Rafagan Simbol.txt", "r");
	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	_getch();
	system("cls");
}

void abertura(bool opening)
{
	FILE *file;
	int ch;

	while(opening){
		cout << "Rafagan Sebastian de Abreu apresenta:\n\n\n\n\n";
		file = fopen("Opening.txt", "r");
		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}

		cout << "\n\n\n\n\n\n";

		file = fopen("Dragon.txt", "r");
		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}

		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t   PRESSIONE QUALQUER TECLA PARA COMECAR" << endl;
		_getch();
		cout << '\7';

		opening = false;
	}
}

//***MENU***
bool Menu(Personagem &pe)
{
	FILE *file;
	int ch;
	char op;

	file = fopen("Menu.txt", "r");
		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}

	cout << "1- Novo jogo" << endl;
	cout << "2- Historia" << endl;
	cout << "3- Como Jogar" << endl;
	cout << "4- Creditos" << endl;
	cout << ":";

	/*cout << "\n\n\n\n\n\n\nESTA VERSAO AINDA NAO POSSUI OS SEGUINTES RECURSOS IMPLEMENTADOS:\n"
		 << "1- Passwords\n"
		 << "2- Chefes completos\n"
		 << "3- Balanceamento entre inimigos e personagem\n"
		 << "4- Final do jogo completo\n"
		 << "5- Habilidade de fuga do personagem\n" << endl;*/

	op = _getch();
	system("cls");
	cout << '\7' << endl;

	switch(op){
	case '1':
		if(startGame(pe) == false)
			return false;
		return true;
	case '2':
		history();
		return true;
	case '3':
		htp();
		return true;
	case '4':
		credits();
		return true;
	default :
		cout << "Opcao invalida" << endl;
		_getch();
		system("cls");
		return true;
	}
}
bool startGame(Personagem &pe)
{
	FILE *file;
	int ch;
	char op2;
	char nome[100];
	char tmp;

	while(true){
		cout << "Qual e o seu nome?" << endl;
		gets_s(nome);
		if(strlen(nome) > 25){
			cout << "Nome invalido. O maximo de caracteres possiveis e de 25" << endl;
			getch();
		}
		else
			break;
	}
	pe.setName(nome);
	system("cls");

	while(true){
		cout << "Escolha seu personagem:\n" << endl;
		cout << "1- Argorn" << endl;
		cout << "2- Tyson" << endl;
		op2 = _getch();

		switch(op2){

		case '1':
			file = fopen("Argorn.txt", "r");
			while((ch=fgetc(file))!=EOF) {
				printf("%c", ch);
			}
			cout << "Tem certeza? (S/N)" << endl;
			tmp = _getch();
			if(tmp == 's' || tmp == 'S'){
				system("cls");
				break;
			}
			else if(tmp == 'n' || tmp == 'N'){
				system("cls");
				continue;
			}
			else{
				cout << "Opcao invalida" << endl;
				_getch();
				system("cls");
				continue;
			}
			break;
		case '2':
			file = fopen("Tyson.txt", "r");
			while((ch=fgetc(file))!=EOF) {
				printf("%c", ch);
			}
			cout << "TEM CERTEZA? (S/N)" << endl;
			tmp = _getch();
			if(tmp == 's' || tmp == 'S'){
				system("cls");
				break;
			}
			else{
				system("cls");
				continue;
			}
			break;
		default:
			cout << "\n Opcao invalida" << endl;
			getch();
			system("cls");
			continue;
		}

		if(tmp == 's' || tmp == 'S'){
			break;
		}
	}

	cout << "   Infelizmente, o momento da partida de Argorn e Tyson de seus vilarejos rumo a uma\n"
	     << "        jornada em busca da derrota do inimigo se tornou inevitavel...\n"
	     << "    Saindo de suas casas com o brilho e confianca nos olhos, sera que nossos herois\n"
	     << "        conseguirao resistir aos perigos que lhes esperam?\n\n\n" << endl;

	file = fopen("Home.txt", "r");
	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	getch();system("pause");
	system("cls");

	return false;
}
void history()
{
	FILE *file;
	int ch;

	cout << "    Bem vindo ao mundo de Darken Spells... Um mundo que ja foi pacifico antes de\n" 
		 << "  Nilats, um demonio muito poderoso e cruel, invadir a cidade e deixar quase toda a\n"
		 << " populacao sucumbida ao seu exercito de criaturas malignas. Com sua frota infernal e\n"
		 << "  seus dragoes flamejantes, aos poucos foi conquistando cidade a cidade, reinado a\n"
		 << "   reinado, ate tomar conta de praticamente tudo o que existia. Sua presenca e tao\n" 
		 << "     repugnante que ate mesmo as plantas apodrescem ao presenciarem seu toque.\n\n";

	file = fopen("BossF.txt", "r");
	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	_getch();
	system("cls");

	cout << "\nOs passarinhos pararam de cantar,  As criancas nao sorriem mais e tudo o que resta as\n"
		 << "pessoas e esperar que suas mortes sejam o menos dolorosas possiveis...\n\n" 
		 << "Bem, na verdade quase tudo...\n" << endl << endl;
	cout << "Em um vilarejo, no canto da colina de rosan,  existe um ultimo suspiro de resistencia!\n"
	     << " Dois homens, Argorn e Tyson, clamam pelo mesmo objetivo: Aniquilar as forcas inimigas!\n"
		 << "  Ainda que seja uma missao impossivel derrotarem o execito de Nilats sozinhos, nada\n"
		 << "impede o desejo de batalha desses dois guerreiros que clamam pela vinganca de seu povo"
		 << "   e pelo mais que demorado colapso de seu poderoso inimigo!" << endl << endl;

	file = fopen("Home.txt", "r");
	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}
	_getch();
	system("cls");

	cout << "\n  Sera que a coragem desses dois guerreiros podera conter a furia de Nilats e impedir\n"
			<< "                    a completa extincao da humanidade?\n\n\n" << endl << endl;

	file = fopen("Personagens.txt", "r");
	while((ch=fgetc(file))!=EOF) {
		printf("%c", ch);
	}

	_getch();
	system("cls");
}
void htp()
{
	cout << "\n\n      Seu objetivo e percorrer o cenario em busca da derrota do demonio Nilats.\n"
		 << "  Voce comeca no canto superior esquerdo da tela.Use as direcionais para caminhar.\n\n"
		 << "    Caso encontrar um inimigo, insira o numero da opcao desejada para combate-lo.\n\n"
		 << "  Sua barra de XP mostra o quanto de experiencia voce ja tem e quanto mais precisara\n"
		 << "     para chegar ao proximo level.\n\n"
		 << "   O atributo forca definira a intensidade do dano de seu personagem. Ja o atributo\n"
		 << "  resistencia definine o quanto seu personagem consegue resistir a um ataque inimigo.\n\n"
		 << " O que define quem atacara primeiro ou a probabilidade de se conseguir fugir de uma\n"
		 << "    batalha e o atributo velocidade.\n\n"
		 << "Se sua vida chegar a zero,voce morrera e eventualmente voltara para o comeco do jogo.\n"
		 << "Se voce encontrar um equipamento, este sera sinalizado na aba de equipamentos, bem\n"
		 << "      como os beneficios que estes trazem junto aos valores de seus atributos.\n\n"
		 << " Quando evoluir de nivel, uma tela de level up ira sinalizar os pontos recebidos para\n"
		 << "     que voce os distribua entre os seus atributos de acordo com sua preferencia.\n\n"
		 << "\n     Agora voce ja esta preparado para tentar a sorte no mundo de Darken Spells\n\n"
		 << "                                      BOA SORTE!!!" << endl;

	_getch();
	system("cls");
}
void credits()
{
	system("cls");

	cout << "\nPensado, produzido, arquitetado, elaborado e programado por Rafagan Sebastia de Abreu!\n"
		 << "\nAgradecimentos a:\n"
		 << "\nMaicris Fernandes: Por ter me ensinado a programar. A ele sou eternamente grato.\n"
		 << "\nVinicius Godoy de Mendonca: Pela paciencia e clareza de centenas de e-mails recebidos\ncom todas minhas duvidas respondidas. Uma vez mestre, sempre mestre!\n"
		 << "\nKeli DarkLua: Pela maozinha com as artes e por me aturar!\n"
		 << "\nBruno Campagnolo de Paula: Por me deixar faltar uma semana de trabalho para a \nrealizacao  desse projeto.\n"
		 << "\n" << endl;
	cout << "                                  DIREITOS RESERVADOS!!!\n\n\n" << endl;
	cout << "Pressione qualquer tecla para continuar..." << endl;

	_getch();
	system("cls");
}

void opcoes()
{
	char setas[] = {24,25,26,27};

	cout << '\n' << "O que deseja fazer?" << endl << endl;
	cout << setas[0] << "- Mover para cima" << endl;
	cout << setas[1] << "- Mover para baixo" << endl;
	cout << setas[2] << "- Mover para a direita" << endl;
	cout << setas[3] << "- Mover para a esquerda" << endl;
	cout << "1- Usar uma pocao" << endl;
	cout << ":";
}

void escolha(Personagem &pe, int op, char mapa[ALTURA][LARGURA], char blindMap[ALTURA][LARGURA], bool &menu)
{
	char tmp;

	switch(op){
		//Andar para cima
		case 72 :
			tmp = mapa [ pe.getPosition()[0] -1 ] [ pe.getPosition()[1] ];
			
			if(tmp == p){
				cout << "\nVoce bateu na parede" << endl;
				blindMap [ pe.getPosition()[0] -1 ] [ pe.getPosition()[1] ] = 1;
				_getch();
				break;
			}
			else
				switchOp(pe,tmp,menu);

			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = c;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			pe.movUp();
			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = j;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			break;
		//Andar para baixo
		case 80 : 
			tmp = mapa [ pe.getPosition()[0] +1 ] [ pe.getPosition()[1] ];
			
			if(tmp == p){
				cout << "\nVoce bateu na parede" << endl;
				blindMap [ pe.getPosition()[0] +1 ] [ pe.getPosition()[1] ] = 1;
				_getch();
				break;
			}
			else
				switchOp(pe,tmp,menu);

			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = c;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			pe.movDown();
			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = j;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			break;
		//Andar para a direita
		case 77 :
			tmp = mapa [ pe.getPosition()[0] ] [ pe.getPosition()[1] +1 ];
			
			if(tmp == p){
				cout << "\nVoce bateu na parede" << endl;
				blindMap [ pe.getPosition()[0] ] [ pe.getPosition()[1] +1 ] = 1;
				_getch();
				break;
			}
			else
				switchOp(pe,tmp,menu);

			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = c;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			pe.movRight();
			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = j;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			break;
		//Andar para a esquerda
		case 75 : 
			tmp = mapa [ pe.getPosition()[0] ] [ pe.getPosition()[1] -1];
			
			if(tmp == p){
				cout << "\nVoce bateu na parede" << endl;
				blindMap [ pe.getPosition()[0] ] [ pe.getPosition()[1] -1 ] = 1;
				_getch();
				break;
			}
			else
				switchOp(pe,tmp,menu);

			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = c;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			pe.movLeft();
			mapa[pe.getPosition()[0] ] [ pe.getPosition()[1]] = j;
			blindMap[pe.getPosition()[0] ] [ pe.getPosition()[1]] = 1;
			break;
		case 49:
			pe.usingPotion();
			getch();
			break;
		default:
			cout << endl << "\nOpcao invalida" << endl;
			_getch();
	}
}

void switchOp(Personagem &pe, int tmp, bool &menu)
{
	bool isDead = false;
	FILE *file;

	if(tmp == a){
		isDead = battleStart(pe,a);
	}
	else if(tmp == m){
		isDead = battleStart(pe,m);
	}
	else if(tmp == h){
		isDead = battleStart(pe,h);
	}
	else if(tmp == b){
		system("cls");
		cout << "\n\nArgorn e Tyson chegam a regiao mais obscura da floresta. O climax do momento era\n"
		     << "   de aflicao. Eles sabiam que aqui e que os desafios comecariam, e nao estavam\n"
		     << "       errados... Quando menos esperavam, foram emboscados pelo principal e mais\n"
		     << "             agressivo demonio do exercito de Nilats: -A Morte!!!-.\n"
		     << "E tempo de batalha e de mostrar que ambos nao vieram ate aqui para brincar...\n\n\n" << endl;
		int ch;

		file = fopen("Death 3.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
		getch();system("pause");system("cls");
		isDead = battleStart(pe,b);
	}
	else if(tmp == z){
		pe.equipament(0);
	}
	else if(tmp == k){
		pe.equipament(1);
	}
	else if(tmp == d){
		pe.equipament(2);
	}
	else if(tmp == l){
		pe.addPotion();
		getch();
	}
	else if(tmp == w){
		system("cls");
		cout << "\n     Argorn e Tyson percorrem o fim do corredor da sala principal do castelo e\n"
		     << "     se deparam com os tesouros escondidos por Nilats. Dentre todos eles, e um\n"
		     << "       bau no fim da sala que chama suas atencoes. Mas antes que pudessem se\n"
		     << "     aproximar muito, Nilats apresenta-se com uma pocao escura e azulada. Com\n"
			 << "          um olhar desprezivel, arranca a rolha que trancafiava o conteudo e a\n"
			 << "         ingere em poucos goles. O castelo treme, as paredes comecam a cair, e\n"
			 << "           aos poucos a identidade de um dragao gigantesco toma o corpo do\n"
		     << "              demonio. A verdadeira batalha final esta para comecar!\n\n\n" << endl;
		int ch;

		file = fopen("Boss Final Form.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
		getch();system("pause");system("cls");
		isDead = battleStart(pe,w);
		if(isDead == false)
			theEnd();
	}
	else if(tmp == g){
		system("cls");
		cout << "\n\n     Argorn e Tyson estavam seguindo para o palacio de Nilats quando, de repente,\n"
		     << "       foram emboscados pelo subordinado mais poderoso do exercito rival. O braco\n"
		     << "           direito de Nilats: Minus, e seu fiel dragao Shruikan.\n"
		     << "      Com essa oportunidade unica e ao mesmo tempo desesperadora, nossos herois\n"
		     << "          terao que enfrentar a batalha mais desafiadora de suas vidas!!!\n\n\n" << endl;
		int ch;

		file = fopen("Minus h.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
		getch();system("pause");system("cls");
		isDead = battleStart(pe,g);
	}
	else if(tmp == n){
		system("cls");
		cout << "\n\n     Finalmente o momento de mostrar toda a bravura e coragem chegou para Argorn e\n"
		     << "        Tyson. Logo a sua frente estava ele... Nilats ja os aguardava com ar de\n"
		     << "      deboche nos olhos. Para ele aquela luta seria apenas uma piada, ou nao...\n"
		     << "\nSera que nossos herois estarao preparados para enfrentar a furia do mais poderoso ser\n"
		     << "que ja cruzou os seus caminhos?\n\n\n" << endl;
		int ch;

		file = fopen("BossF2.txt", "r");

		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
		getch();system("pause");system("cls");
		isDead = battleStart(pe,n);
	}


	if(isDead)
		menu = true;
}

bool battleStart(Personagem &pe,char inimigo)
{
	system("cls");

	//***POLIMORFISMO***
	Inimigo *enemy;
	if(inimigo == a)
		enemy = new Soldier();
	else if(inimigo == m)
		enemy = new Beast();
	else if(inimigo == h)
		 enemy = new Giant();
	else if(inimigo == b)
		enemy = new Death();
	else if(inimigo == g)
		enemy = new Dragoneer();
	else if(inimigo == n)
		enemy = new Nilats();
	else if(inimigo == w)
		enemy = new finalBoss();

	char op = 0;
	int machineryState;
	int damage;

	do{
		cout << "VOCE ENCONTROU UM INIMIGO:" << endl << endl;
		enemy->image();
		cout << endl << endl;
		enemy->status();
		pe.status();

		cout << "O que deseja fazer?" << endl << endl;
		cout << "1- Atacar" << endl;
		cout << "2- Defender" << endl;
		cout << "3- Usar uma pocao" << endl;
		cout << "4- Escapar" << endl;
		cout << ":";
		op = _getch();

		cout << endl;

		switch(op){

		//ATACAR
		case '1' : 
			// PERSONAGEM -> INIMIGO
			if(pe.getSpeed() >= enemy->getSpeed()){
				damage = pe.attack();
				machineryState = enemy->defense(damage);
				_getch();
				op = combat_P_I(pe,enemy,inimigo,damage,machineryState);

				if(op == 0 || op == 2)
					break;

				damage = enemy->attack();
				machineryState = pe.defense(damage);
				op = combat_I_P(pe,enemy,inimigo,damage,machineryState);
			}

			// INIMIGO -> PERSONAGEM
			else if(pe.getSpeed() < enemy->getSpeed()){
				cout << endl;
				damage = enemy->attack();
				machineryState = pe.defense(damage);
				op = combat_I_P(pe,enemy,inimigo,damage,machineryState);

				if(op == 0 || op == 2)
					break;

				damage = pe.attack();
				machineryState = enemy->defense(damage);
				_getch();
				op = combat_P_I(pe,enemy,inimigo,damage,machineryState);
			}

			_getch();
			break;

		//DEFENDER
		case '2':
			if(inimigo == b && enemy->getLife() <= 50){
				cout << "Voce nao pode defender esse tipo de ataque" << endl;
				_getch();
				break;
			}
			else{
				damage = enemy->attack();
				machineryState = pe.defense(true,damage);
				combat_Defense(pe,enemy,inimigo,damage,machineryState);
				_getch();
				break;
			}
		case '3':
			pe.usingPotion();
			getch();
			break;
		case '4':
			cout << "\nIndisponivel nessa versao" << endl;
			getch();
			break;
		}

		system("cls");
	}while(op != 0);


	//***GAME OVER***
	if(pe.getLife() <= 0){
		char ch;
		FILE *file;
		file = fopen("Game Over.txt", "r");
		while((ch=fgetc(file))!=EOF) {
			printf("%c", ch);
		}
		_getch();
		counterTMP = 0;
		system("cls");
		return true;
	}

	//***CASO O INIMIGO SEJA DERROTADO, AUMENTA-SE A EXPERIENCIA
	if(inimigo == a)
		pe.setXP(10);
	else if(inimigo == m)
		pe.setXP(30);
	else if(inimigo == h)
		 pe.setXP(60);
	else if(inimigo == b)
		pe.setXP(100);
	else if(inimigo == g)
		pe.setXP(300);
	else if(inimigo == n)
		pe.setXP(500);


	delete enemy;
	return false;
}

int combat_P_I(Personagem &pe, Inimigo *enemy, char inimigo,int damage,int machineryState)
{
	if(pe.getLuck() == 0)
			cout << pe.getName() << " errou o ataque" << endl;

	else if(machineryState == 0 && damage != 0)
		cout << enemy->getName() << " desviou de seu ataque" << endl;

	else if(machineryState == 1){
		if(pe.getLuck() <= 7)
			cout << pe.getName() << " causou um dano pouco efetivo de " << damage/2 << endl;
		else if(pe.getLuck() == 8)
			cout << pe.getName() << " causou um dano critico, mas pouco efetivo de " << damage/2 << endl;
		else if(pe.getLuck() == 9)
			cout << pe.getName() << " causou um dano extremo, mas pouco efetivo de " << damage/2 << endl;
	}

	else if(machineryState == 2){
		if(pe.getLuck() <= 7)
			cout << pe.getName() << " causou " << damage << " de dano" << endl;
		else if(pe.getLuck() == 8){
			cout << pe.getName() << " causou um dano critico de " << damage << endl;

			if(inimigo == m && enemy->getLife() > 0 && enemy->setPursuit())
				cout << pe.getName() << " assustou a " << enemy->getName() << ". Ela nao vai descansar ate mata-lo" << endl;
		}
		else if(pe.getLuck() == 9){
			cout << pe.getName() << " causou um dano extremo de " << damage << endl;

			if(inimigo == m && enemy->getLife() > 0 && enemy->setPursuit())
				cout << pe.getName() << " assustou a " << enemy->getName() << ". Ela nao vai descansar ate mata-lo" << endl;
		}

		if(inimigo == h && enemy->getLife() > 0)
			cout << enemy->getName() << " entrou em estado de raiva" << endl;
	}

	if(enemy->getLife() <= 0){
		if(inimigo == g && enemy->setNew()){
			cout << enemy->getName() << " Foi derrotado!!!" << endl;
			cout << "Espere... O dragao de Milus esta lhe encurralando. Voce tera que batalhar novamente!" << endl;
			_getch();
			return 2;
		}

		else{
			cout << pe.getName() << " derrotou o inimigo!!!" << endl;
			_getch();
			return 0;
		}
	}

	return 1;
}

int combat_I_P(Personagem &pe, Inimigo *enemy,char inimigo,int damage,int machineryState)
{
	if(enemy->getLuck() == 0)
		cout << enemy->getName() << " errou o ataque" << endl;

	else if(machineryState == 0 && damage != 0)
		cout << pe.getName() << " desviou do ataque de " << enemy->getName() << endl;

	else if(machineryState == 1){
		if(inimigo == b && enemy->getLife() <= 50){
			if(enemy->getLuck() >= 8){
				cout << enemy->getName() << " esta tentando sugar sua alma, mas voce esta resistindo " << endl;
				_getch();
				cout << enemy->getName() << " conseguiu retirar " << damage/2 << " lifepoints de sua forca vital" << endl;

				enemy->setDrainPower(machineryState,damage);
			}
			else{
				cout << enemy->getName() << " esta tentando sugar sua alma, mas voce esta resistindo " << endl;
				_getch();
				cout << enemy->getName() << " nao conseguiu sugar sua alma " << endl;
				cout << enemy->getName() << " causou um dano pouco efetivo de " << damage/2 << endl;
				_getch();
			}
		}
		else{
			if(enemy->getLuck() <= 7)
				cout << enemy->getName() << " causou um dano pouco efetivo de " << damage/2 << endl;
			else if(enemy->getLuck() >= 8)
				cout << enemy->getName() << " causou um dano critico, mas pouco efetivo de " << damage/2 << endl;
			else if(enemy->getLuck() == 9)
				cout << enemy->getName() << " causou um dano extremo, mas pouco efetivo de " << damage/2 << endl;
		}
	}

	else if(machineryState == 2){
		if(inimigo == b && enemy->getLife() <= 50){
			if(enemy->getLuck() >= 8){
				cout << enemy->getName() << " esta sugando sua alma " << endl;
				_getch();
				cout << enemy->getName() << " conseguiu retirar " << damage << " lifepoints de sua forca vital" << endl;

				enemy->setDrainPower(machineryState,damage);
			}
			else{
				cout << enemy->getName() << " esta tentando sugar sua alma, mas voce esta resistindo " << endl;
				_getch();
				cout << enemy->getName() << " nao conseguiu sugar sua alma " << endl;
				cout << enemy->getName() << " causou " << damage << " de dano em seus pontos de vida" << endl;
				_getch();
			}
		}
		else{
			if(enemy->getLuck() <= 7)
				cout << enemy->getName() << " causou " << damage << " de dano em seus pontos de vida" << endl;
			else if(enemy->getLuck() == 8)
				cout << enemy->getName() << " causou um dano critico de " << damage << " em seus pontos de vida" << endl;
			else if(enemy->getLuck() == 9)
				cout << enemy->getName() << " causou um dano extremo de " << damage << " em seus pontos de vida" << endl;
		}
	}

	if(pe.getLife() <= 0){ 
		cout << pe.getName() << " Foi derrotado!!!" << endl;
		_getch();
		return 0;
	}

	return 1;
}

int combat_Defense(Personagem &pe, Inimigo *enemy,char inimigo,int damage,int machineryState)
{
	if(enemy->getLuck() == 0)
		cout << enemy->getName() << " errou o ataque" << endl;

	else if(machineryState == 0 && damage != 0)
		cout << "A sua defesa foi super efetiva contra o ataque de " << enemy->getName() << endl;

	else if(machineryState == 1){
		cout << pe.getName() << " conseguiu defender o ataque, mas seu corpo sentiu um pouco do impacto" << endl;
		if(enemy->getLuck() <= 7)
			cout << enemy->getName() << " causou um dano pouco efetivo de " << damage << endl;
		else if(enemy->getLuck() >= 8)
			cout << enemy->getName() << " causou um dano critico, mas pouco efetivo de " << damage << endl;
		else if(enemy->getLuck() == 9)
			cout << enemy->getName() << " causou um dano extremo, mas pouco efetivo de " << damage << endl;
	}

	else if(machineryState == 2){
		cout << pe.getName() << " nao conseguiu defender o ataque" << endl;
		if(enemy->getLuck() <= 7)
			cout << enemy->getName() << " causou " << damage << " de dano em seus pontos de vida" << endl;
		else if(enemy->getLuck() == 8)
			cout << enemy->getName() << " causou um dano critico de " << damage << " em seus pontos de vida" << endl;
		else if(enemy->getLuck() == 9)
			cout << enemy->getName() << " causou um dano extremo de " << damage << " em seus pontos de vida" << endl;
	}

	//Calculo da vida recuperada

	int lpr = pe.setRest();
	cout << pe.getName() << " recuperou " << lpr << " de vida com o descanso" << endl;
	_getch();

	if(pe.getLife() <= 0){ 
		cout << pe.getName() << " Foi derrotado!!!" << endl;
		_getch();
		return 0;
	}

	return 1;
}

bool theEnd()
{
	system("cls");
	cout << "Esta versao ainda nao possui o final completo implementado" << endl;
	getch();

	return true;
}