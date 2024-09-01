#ifndef CMeteoro_H
#define CMeteoro_H

#include <allegro.h>
/*
Definição do Status:
0-Parado
1-Monimento
2-Morto

Definição da direção:
0-Reto
1-Diagonal direita
2-Diagonal esquerda
*/
class CMeteoro
{
private:
	BITMAP *imgMeteoro;
	int iPosx;
	int iPosy;
	int iVelocidade;

public:	
	int status;	
	int direcao;
	int largura;
	int altura;
	int vida;

 	CMeteoro();
	~CMeteoro();

	void Atualiza(BITMAP *);
	int Pegax();
	int Pegay();
	void Setax(int);
	void Setay(int);
	void Setaxy(int,int);
	int Colisao(int,int,int,int);
};

#endif
