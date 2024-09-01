#ifndef nave_h
#define nave_h

#include <allegro.h>

class CNave
{
private:
	BITMAP *bmpnave;
	int posx;
	int posy;

public:	
	int energia;
	int pontos;
	int altura;
	int largura;

	CNave();
	~CNave();

	int pegax(void);
	int pegay(void);
	int pegaenergia(void);

	void setax(int);
	void setay(int);
	void setaxy(int,int);
	void atualiza(BITMAP *);
};

#endif
