#include "CChefe.h"

CChefe::CChefe()
{
	this->imgchefe = NULL;
	this->imgchefe = load_bitmap("chefe.bmp",NULL);
	this->status = 0;
	this->largura = 650;
 	this->altura = 420;
}

CChefe::~CChefe(void)
{
	this->imgchefe = NULL;
	delete this->imgchefe;
	// FINALIZA OBJETO
}

/**********************/
/* OBTEM O VALOR DE X */
/**********************/
int CChefe::Pegax(void)
{
	return this->iPosx;
}

/**********************/
/* OBTEM O VALOR DE Y */
/**********************/
int CChefe::Pegay(void)
{
	return this->iPosy;
}
void CChefe::Setax(int x)
{
	this->iPosx = x;
}
void CChefe::Setay(int y)
{
	this->iPosy = y;
}
void CChefe::Setaxy(int x,int y)
{
	this->iPosx += x;
	this->iPosy += y;
}


void CChefe::Atualiza(BITMAP *buffer)
{
	Setaxy(0,1);
	draw_sprite(buffer,this->imgchefe,this->iPosx,this->iPosy);
}

int CChefe::Colisao(int obj2x,int obj2y, int obj2a, int obj2l) 
{
if (this->iPosx+this->largura > obj2x && this->iPosx < obj2x+obj2l && this->iPosy+this->altura > obj2y && this->iPosy < obj2y+obj2a)
 	{
		return 1; // colidiu
	} else return 0; // não colidiu
}
