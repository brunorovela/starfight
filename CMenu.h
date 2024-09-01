#ifndef CMenu_H
#define CMenu_H

#include <allegro.h>

class CMenu
{
private:
	BITMAP *imgMenu;
	BITMAP *imgBotao;
	int iOpcao;
	int BufferTeclado;
public:	
	CMenu();
	~CMenu();

	int Atualizar();
};

#endif
