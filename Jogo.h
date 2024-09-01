#include "CMeteoro.h"
#include "CMunicao.h"
#include "objetos.h"
#include "nave.h"
#include "radar.h"
#include "CChefe.h"

int Inicia_Jogo();
void Finaliza_Jogo();

int Inicia_Jogo()
{
 	
	MIDI *somfase1 = load_midi("fase1.mid"); 
 	SAMPLE *somexplosao = load_wav("explosao.wav");
 	SAMPLE *somtiro = load_wav("tiro.wav");
 	SAMPLE *somalarme = load_wav("alarme.wav");

	BITMAP *buffer;
	BITMAP *cenario;
	BITMAP *painel;
	BITMAP *bmpnuclear;
	BITMAP *tiro;
	BITMAP *radar;
	BITMAP *buffer_radar;
	BITMAP *buffer_painel;
	BITMAP *explosao;
	BITMAP *vermelho;
	BITMAP *amarelo;
	BITMAP *verde;

	int ytela=11400;
	int total_meteoros=0;
	int i=0;
	int j=0;
	int buffer_municao = 0;
	const int total_municao = 5;
	bool tocou = false;
	int Resultado=0;
 	
	total_meteoros = conta_objetos();
	CMeteoro *meteoro = new CMeteoro[total_meteoros]();
	CMunicao *municao = new CMunicao[total_municao]();
	CChefe *chefe = new CChefe();
	chefe->Setax(0);
	chefe->Setay(600);

	CNave *nave = new CNave();
 
	posiciona_objetos(meteoro);
	      
	cenario = create_bitmap(640,12000);
	cenario = load_bitmap("cenario.bmp",NULL);
	buffer = create_bitmap(800,600);
	explosao = load_bitmap("explosao.bmp",NULL);
	buffer_radar = create_bitmap(92,92);
	clear(buffer);
	
 	painel = create_bitmap(150,600);
	painel = load_bitmap("painel.bmp",NULL);
	vermelho = load_bitmap("vermelho.bmp",NULL);
	amarelo = load_bitmap("amarelo.bmp",NULL);
	verde = load_bitmap("verde.bmp",NULL);
	buffer_painel = create_bitmap(150,600);
	radar = load_bitmap("radar.bmp",NULL);
	
 	play_midi(somfase1,1);

 	while(!key[KEY_ESC])
	{
		// cortei o cenário
		blit(cenario,buffer,0,ytela,0,0,650,600);

		// abaixo segue rotina para o painel
		draw_sprite(buffer_painel,painel,0,0);
		textprintf_ex(buffer_painel,font,30,173,makecol(255,0,0),-1, "Nave");
		textprintf_ex(buffer_painel,font,30,183,makecol(255,255,0),-1, "X:%d-Y:%d", nave->pegax(),nave->pegay());
		
		textprintf_ex(buffer_painel,font,30,194,makecol(255,0,0),-1, "Distancia");
 		textprintf_ex(buffer_painel,font,30,204,makecol(255,255,0),-1, "%d", ytela);
 		
 		textprintf_ex(buffer_painel,font,30,215,makecol(255,0,0),-1, "Energia");
 		textprintf_ex(buffer_painel,font,30,225,makecol(255,255,0),-1, "%d", nave->pegaenergia());
 		
 		textprintf_ex(buffer_painel,font,30,236,makecol(255,0,0),-1, "Pontos");
 		textprintf_ex(buffer_painel,font,30,246,makecol(255,255,0),-1, "%d", nave->pontos);
		
		if (nave->energia > 6)
  		{
			draw_sprite(buffer_painel,vermelho,86,303);
			draw_sprite(buffer_painel,amarelo,85,341);
			draw_sprite(buffer_painel,verde,85,377);
  		} else if (nave->energia > 3)
  		{
	  		draw_sprite(buffer_painel,vermelho,86,303);
			draw_sprite(buffer_painel,amarelo,85,341);
  		} else if (nave->energia > 0)
  		{
  			draw_sprite(buffer_painel,vermelho,86,303);
  			if (tocou == false)
     		{
  				play_sample (somalarme, 255, 128, 1000, 0);
  				tocou = true;
     		}
  		} else 
    	  {
    		Resultado = 1;
    		break;
    	  }
		
		draw_sprite(buffer,buffer_painel,650,0); // mostra o painel para o buffer
		//Fim da construção do painel

		draw_sprite(buffer_radar,radar,0,0);

/* 
****************************************************************************************
Caida dos meteoros na tela:
1 - Varre todos os meteoros instanciados conforme a quantidade da matriz.
2 - O primeiro if verifica se o meteoro está morto.
3 - Se a tela estiver no campo próximo ao meteoro ativa o meteoro para
que o mesmo possa ser desenhado no buffer.
4 - Após o meteoro estiver ativado o 3º if verifica se o mesmo realmente
está tivado. Se estiver ativado desenha ele no buffer.
5 - O 4º if verifica se o meteoro já passou pela tela, se passou seta ele como morto
e para de desenha-lo na tela.
****************************************************************************************
*/

		for (i=0;i<total_meteoros;i++)
		{  
			if (meteoro[i].status != 2) // if (1)
			{
				if (meteoro[i].Pegay() > ytela && meteoro[i].Pegay() < ytela+600 && meteoro[i].status==0) // if (2)
    			{
                	meteoro[i].status=1;
                	meteoro[i].Setay(-32);
        		} 
        		
        		if (meteoro[i].status == 1) // if (3)
          		{
                	meteoro[i].Atualiza(buffer);
                	radar_atualiza(buffer_radar,meteoro[i].Pegax(),meteoro[i].Pegay());
					// Colisão                	
					if (meteoro[i].Colisao(nave->pegax(),nave->pegay(),nave->altura, nave->largura) == 1)
					{
						meteoro[i].status = 3; // morto
						draw_sprite(buffer,explosao,meteoro[i].Pegax(),meteoro[i].Pegay());
						draw_sprite(buffer,explosao,nave->pegax(),nave->pegay());
						if (nave->pontos >1)
						{
		 					nave->pontos -=2;
						}
						nave->energia--;
						play_sample (somexplosao, 255, 128, 1000, 0);
					}
                	// fim da colisão
				}

        		if (meteoro[i].status==1 && meteoro[i].Pegay() > 600) // if (4)
          		{ 
                	meteoro[i].status=3;
        		}
			}
		}
		_putpixel32(buffer_radar, nave->pegax()/7, (nave->pegay()+33)/7, makecol(0,0,0)); //precisão
		draw_sprite(painel,buffer_radar,20,35);

//Colisão com o tiro
	for (i=0;i<total_municao;i++)
	{
		for (j=0;j<total_meteoros;j++)
		{
			if (meteoro[j].status == 1)
			{
				if (municao[i].status == 1)
				{
					if (meteoro[j].Colisao(municao[i].pegax(),municao[i].pegay(),municao[i].altura, municao[i].largura) == 1)
					{
						draw_sprite(buffer,explosao,meteoro[j].Pegax(),meteoro[j].Pegay());
						municao[i].status = 0; // tiro destruído
     					meteoro[j].vida--;
     					nave->pontos++;
     					play_sample (somexplosao, 255, 128, 1000, 0);
					}
				}
			}
		}
		
		//colisão do tiro no chefe
		if (chefe->status == 1) 
  		{
  			if (municao[i].status == 1)
  			{
				if (chefe->Colisao(municao[i].pegax(),municao[i].pegay(),municao[i].altura, municao[i].largura) == 1)
				{
					draw_sprite(buffer,explosao,municao[i].pegax(),municao[i].pegay());
					municao[i].status = 0; // tiro destruído
     				nave->pontos += 5;
     				play_sample (somexplosao, 255, 128, 1000, 0);
				}
			}
		}
		//fim da colisão
	}
//fim da colisão com o tiro

//************* fim dos meteoros


// CHEFE
	if (chefe->status != 2)
	{
		if (chefe->Pegay() > ytela && chefe->Pegay() < ytela+600 && chefe->status==0)
    	{
    		chefe->status=1;
        	chefe->Setay(-430);
    	} 
	}
    
    if (chefe->status == 1)
    {
		chefe->Atualiza(buffer);
        
        //colisão com a nave
		if (chefe->Colisao(nave->pegax(),nave->pegay(),nave->altura, nave->largura) == 1)
		{
			draw_sprite(buffer,explosao,nave->pegax(),nave->pegay());
			play_sample (somexplosao, 255, 128, 1000, 0);
			Resultado = 2;
			break;
		}
  		// fim da colisão
    }
    
// FIM CHEFE


//************* Inicio dos tiros
	if (buffer_municao == 0)
	{
		if (key[KEY_SPACE])
		{
			for (i=0;i<total_municao;i++)
 			{
 				if (municao[i].status == 0)
 				{
					municao[i].status = 1;
					municao[i].setax(nave->pegax()+12);
 					municao[i].setay(nave->pegay()-10);
 					buffer_municao = 10;
 					play_sample (somtiro, 50, 128, 1000, 0);
					break;
				}
 			}
		}
	} else buffer_municao--;

	for (i=0;i<total_municao;i++)
 	{
		if (municao[i].status == 1)	
 		{
 			municao[i].atualiza(buffer);
		}
	}
//	textprintf(buffer,font,10,10,makecol(255,0,0), "municao[%d]: %d",j, municao[0].pegay());
//	textprintf(buffer,font,10,20,makecol(255,0,0), "municao[%d]: %d",j, municao[1].pegay());
//	textprintf(buffer,font,10,30,makecol(255,0,0), "municao[%d]: %d",j, municao[2].pegay());

//************* fim dos tiros  
  		/*textprintf(buffer,font,10,0,makecol(255,0,0), "meteoros: %d", total_meteoros);	
  		for	(j=0;j<total_meteoros;j++)
    	{
			textprintf(buffer,font,10,(j+10)*10,makecol(255,0,0), "meteoroy[%d]: %d",j, meteoro[j].Pegay());
		}
		for	(j=0;j<total_meteoros;j++)
    	{
			textprintf(buffer,font,200,(j+10)*10,makecol(255,0,0), "meteorox[%d]: %d",j, meteoro[j].Pegax());
		}
		textprintf(buffer,font,500,0,makecol(255,0,0), "ytela: %d", ytela);
*/
//************* 
		
  		if (key[KEY_UP])
		{
			nave->setaxy(0,-2);
		}
		if (key[KEY_DOWN])
		{
			nave->setaxy(0,2);
		}
		if (key[KEY_LEFT])
		{
			nave->setaxy(-2,0);
		}
		if (key[KEY_RIGHT])
		{
			nave->setaxy(2,0);
		}
		nave->atualiza(buffer);
		draw_sprite(screen,buffer,0,0);
		if (ytela>0) ytela--;
		
		if (buffer_municao == 0)
		{
			if (key[KEY_P])
			{
				Pausar_Jogo(buffer);
			}
		} else buffer_municao--;
		   
		vsync();
	}
	stop_midi();
 	delete buffer;
	delete cenario;
	delete meteoro;
	delete painel;
	delete bmpnuclear;
	delete tiro;
	delete radar;
	delete buffer_radar;
	delete buffer_painel;
	delete municao;
	delete somfase1;
 	delete somexplosao;
 	delete somtiro;
	delete vermelho;
	delete amarelo;
	delete verde;
	delete somalarme;
	delete chefe;
	return Resultado;
}

void Finaliza_Jogo()
{
	
}
