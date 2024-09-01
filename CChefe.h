#ifndef CChefe_H
#define CChefe_H

#include <allegro.h>
/*
	Definição do Status:
	0-Parado
	1-Monimento
	2-Morto
*/
class CChefe
{
private:
	BITMAP *imgchefe;
	int iPosx;
	int iPosy;

public:	
	int status;	
	int largura;
	int altura;

 	CChefe();
	~CChefe();

	void Atualiza(BITMAP *);
	int Pegax();
	int Pegay();
	void Setax(int);
	void Setay(int);
	void Setaxy(int,int);
	int Colisao(int,int,int,int);
};

#endif
