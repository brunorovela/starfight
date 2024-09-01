#ifndef municao_h
#define municao_h

#include <allegro.h>

/*
Status Munição:
0 - Carregado
1 - Movimento
*/
class CMunicao
{
private:
	BITMAP *imgmunicao;
	int posx;
	int posy;

public:	
	bool status;
	int largura;
	int altura;

	CMunicao();
	~CMunicao();

	int pegax(void);
	int pegay(void);

	void setax(int);
	void setay(int);
	void setaxy(int,int);
	void atualiza(BITMAP *);
};

#endif
