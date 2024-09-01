#include "drv.h"
#include <allegro.h>
#include "Jogo.h"
#include "CMenu.h"
#include "CAbertura.h"
/*
	Opção:
 	0 - Sair
 	1 - Créditos
 	2 - Iniciar Jogo
 	
 	Resultado:
 	0 - Retorna para o Menu
 	1 - Game over
 	2 - Final
*/
int main(int argc, char *argv[])
{
	Instala_Drivers(); 
 	Inicia_Abertura();

	int Resultado=0;
	int iOpcao = 3;

	CMenu *Menu = new CMenu();

	while(iOpcao != 0)
	{  
		iOpcao = Menu->Atualizar();
		if (iOpcao == 2) // Iniciar jogo
		{
			Resultado = Inicia_Jogo();
			
			if (Resultado == 1)
			{
				Resultado = 3;
				Mostra_GameOver();
			}

			if (Resultado == 2)
			{
				Resultado = 3;
				Mostra_Final();
			}
		}
		if (iOpcao == 1) // Iniciar Créditos
		{
			Mostra_Creditos();
		}
	}

	Menu = NULL;
	delete Menu;

	allegro_exit();
	return 0;     
}

END_OF_MAIN();
