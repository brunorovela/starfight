#include <allegro.h>
// Classe nave
#include "nave.h"

// Funções referente a nave do jogador.

/*********************/
/* CONTRUTOR DA NAVE */
/*********************/
CNave::CNave()
{
	this->bmpnave = NULL;
	this->bmpnave = load_bitmap("nave.bmp",NULL);
	this->posx = 320;
	this->posy = 400;
	this->energia = 9;
	this->pontos = 0;
	this->altura = 24;
	this->largura = 28;
}

/*********************/
/* DESTRUTOR DA NAVE */
/*********************/
CNave::~CNave(void)
{
	this->bmpnave = NULL;
	delete this->bmpnave;
}

/**********************/
/* OBTEM O VALOR DE X */
/**********************/
int CNave::pegax(void)
{
	return this->posx;
}

/**********************/
/* OBTEM O VALOR DE Y */
/**********************/
int CNave::pegay(void)
{
	return this->posy;
}

/*********************/
/* SETA O VALOR DE X */
/*********************/

void CNave::setax(int x)
{
	this->posx = x;
}

/*********************/
/* SETA O VALOR DE Y */
/*********************/
void CNave::setay(int y)
{
	this->posy = y;
}

/*************************/
/* SETA O VALOR DE X E Y */
/*************************/
void CNave::setaxy(int x,int y)
{
	if ((this->posy+24) <= SCREEN_H)
		this->posy += y;
	else
		posy = SCREEN_H-24;
	
	if ((this->posy) >= 0)
		this->posy += y;
	else
		this->posy = 0;
		
	if ((this->posx+28) <= 640)
		this->posx += x;
	else
		this->posx = 640-28;
	
	if ((this->posx) >= 0)
		this->posx += x;
	else
		this->posx = 2;
}

/*******************/
/* DESENHA NA TELA */
/*******************/
void CNave::atualiza(BITMAP *buffer)
{
	draw_sprite(buffer, this->bmpnave,this->posx,this->posy); 	
}

/******************/
/* RETORNA A VIDA */
/******************/
int CNave::pegaenergia(void)
{
	return this->energia;
}

