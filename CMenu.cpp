#include "CMenu.h"

BITMAP *mnuBuffer = NULL;

CMenu::CMenu()
{
	mnuBuffer = create_bitmap(800,600);
	this->imgBotao = NULL;
	this->imgMenu = NULL;
	
	this->imgBotao = load_bitmap("Botao.bmp",NULL);
	this->imgMenu = load_bitmap("Menu.bmp",NULL);
	iOpcao = 2;
	BufferTeclado = 0;
}

CMenu::~CMenu()
{
	this->imgBotao = NULL;
	this->imgMenu = NULL;
	mnuBuffer = NULL;

	delete this->imgBotao;
	delete this->imgMenu;
	delete mnuBuffer;
}

int CMenu::Atualizar()
{
		
	while (!key[KEY_ENTER])
	{
		blit(imgMenu,mnuBuffer,0,0,0,0,800,600);
		
   		if (BufferTeclado==0)
		{
			if (key[KEY_UP])
			{
				if (iOpcao != 2)
				{
					iOpcao++;
					BufferTeclado=30;
				}
			}
			else if (key[KEY_DOWN])
			{
			if (iOpcao != 0)
				{
					iOpcao--;
					BufferTeclado=30;
				}
			}
		}
		else
			BufferTeclado--;
					
		if (iOpcao == 2)
			draw_sprite(mnuBuffer,imgBotao,262,325); // Inicia Jogo
		else if (iOpcao == 1)
			draw_sprite(mnuBuffer,imgBotao,262,365); // Créditos
		else if (iOpcao == 0)
   			draw_sprite(mnuBuffer,imgBotao,262,405); // Sair

		draw_sprite(screen, mnuBuffer, 0, 0);
	}

	return iOpcao;
}
