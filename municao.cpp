#include <allegro.h>
#include "CMunicao.h"

CMunicao::CMunicao()
{
	this->imgmunicao = NULL;
	this->imgmunicao = load_bitmap("municao.bmp",NULL);
	this->posx = 0;
	this->posy = 0;
	this->status = 0;
 	this->largura = 5;
	this->altura = 16;
}

CMunicao::~CMunicao(void)
{
	this->imgmunicao = NULL;
	delete this->imgmunicao;
}

int CMunicao::pegax(void)
{
	return this->posx;
}

int CMunicao::pegay(void)
{
	return this->posy;
}

void CMunicao::setax(int x)
{
	this->posx = x;
}

void CMunicao::setay(int y)
{
	this->posy = y;
}

void CMunicao::setaxy(int x,int y)
{
	if (this->posy > -32) 
 	{
		this->posy += y;
		this->posx += x;
	} else this->status = 0;
}

void CMunicao::atualiza(BITMAP *buffer)
{
	draw_sprite(buffer, this->imgmunicao,this->posx,this->posy); 
 	this->setaxy(0,-10);
}

