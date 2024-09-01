// Classe meteoro
#include "CMeteoro.h"

// Funcões referente aos meteoros.

/************************/
/* CONTRUTOR DO METEORO */
/************************/
CMeteoro::CMeteoro()
{
	this->iVelocidade = (2 + (rand() % 5));
	this->imgMeteoro = NULL;
	this->imgMeteoro = load_bitmap("Meteoro.bmp",NULL);
	this->status = 0;
	this->direcao = 0;
	this->largura = 34;
 	this->altura = 24;
 	this->vida = (1 + (rand() % 2));
}

/************************/
/* DESTRUTOR DO METEORO */
/************************/
CMeteoro::~CMeteoro(void)
{
	delete this->imgMeteoro;
	// FINALIZA OBJETO
}

/**********************/
/* OBTEM O VALOR DE X */
/**********************/
int CMeteoro::Pegax(void)
{
	return this->iPosx;
}

/**********************/
/* OBTEM O VALOR DE Y */
/**********************/
int CMeteoro::Pegay(void)
{
	return this->iPosy;
}
void CMeteoro::Setax(int x)
{
	this->iPosx = x;
}
void CMeteoro::Setay(int y)
{
	this->iPosy = y;
}
void CMeteoro::Setaxy(int x,int y)
{
	this->iPosx += x;
	this->iPosy += y;
}
/**************************************/
/* ATUALIZA O METEORO NA TELA NA TELA */
/**************************************/
void CMeteoro::Atualiza(BITMAP *buffer)
{
	if (this->direcao==0) //reto
 	{
		Setaxy(0,1*this->iVelocidade);
	}
	if (this->direcao==1) // diagonal direita
 	{
		Setaxy(-1,1*this->iVelocidade);
	}
	if (this->direcao==2) // diagonal esquerda
 	{
		Setaxy(1,1*this->iVelocidade);
	}
	draw_sprite(buffer,this->imgMeteoro,this->iPosx,this->iPosy);
	if (this->vida <= 0)
	{
		this->status=3;
	}
}

int CMeteoro::Colisao(int obj2x,int obj2y, int obj2a, int obj2l) 
{
	if (this->iPosx+this->largura > obj2x && this->iPosx < obj2x+obj2l && this->iPosy+this->altura > obj2y && this->iPosy < obj2y+obj2a)
 	{
		return 1; // colidiu
	} else return 0; // não colidiu
}
