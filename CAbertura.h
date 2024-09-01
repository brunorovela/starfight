#include <allegro.h>

void Inicia_Abertura();
void Escurecer(int);
void Clarear(BITMAP *, int);

void Inicia_Abertura()
{
	BITMAP *bmpLogo = NULL;
	BITMAP *bmpNome = NULL;
	BITMAP *bmpHestoria = NULL;

	SAMPLE *somlogo = NULL;
	somlogo = load_wav("brainscore.wav");

	bmpLogo = load_bitmap("brain_score.bmp",NULL);
	bmpNome = load_bitmap("starfight.bmp",NULL);
	bmpHestoria = load_bitmap("hestoria.bmp",NULL);

	play_sample (somlogo, 255, 128, 1000, 0);

	Clarear(bmpLogo,3);
	Escurecer(3);
	Clarear(bmpNome,3);
	Escurecer(3);
 	Clarear(bmpHestoria,1);
	Escurecer(1);		

	bmpLogo = NULL;
	bmpNome = NULL;
	bmpHestoria = NULL;
	somlogo = NULL;
	delete bmpLogo;
	delete bmpNome;
	delete somlogo;
	delete bmpHestoria;
}

void Escurecer(int vel)
{
	BITMAP *bmpOriginal = NULL; 
	BITMAP *bmpArmazenador = NULL;

	int var = 0;
	
	if((bmpOriginal = create_bitmap(SCREEN_W, SCREEN_H))) 
 	{
		if((bmpArmazenador = create_bitmap(SCREEN_W, SCREEN_H))) 
		{	
			blit(screen, bmpOriginal, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			if(vel <= 0) 
   				vel = 16;
			for(var = 255 - vel; var > 0; var -= vel) 
   			{
				clear(bmpArmazenador);
				set_trans_blender(0, 0, 0, var);
				draw_trans_sprite(bmpArmazenador, bmpOriginal, 0, 0);
				vsync();
				blit(bmpArmazenador, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			}
			destroy_bitmap(bmpArmazenador);
		}
		destroy_bitmap(bmpOriginal);
	}
	rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
}

void Clarear(BITMAP *bmpOriginal, int vel)
{

	BITMAP *bmpArmazenador = NULL;
	int var = 0;
 	
	if((bmpArmazenador = create_bitmap(SCREEN_W, SCREEN_H)))
	{
		if(vel <= 0) 
  			vel = 16;
		for(var = 0; var < 256; var += vel) 
  		{
			clear(bmpArmazenador);
			set_trans_blender(0, 0, 0, var);
			draw_trans_sprite(bmpArmazenador, bmpOriginal, 0, 0);
			vsync();
			blit(bmpArmazenador, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		}
		destroy_bitmap(bmpArmazenador);
	}
	blit(bmpOriginal, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void Mostra_Creditos()
{
	BITMAP *buffer = NULL;
	BITMAP *imgCreditos = NULL;

	MIDI *creditos = NULL;
	creditos = load_midi("creditos.mid");

	imgCreditos = load_bitmap("creditos.bmp",NULL);
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	
 	play_midi(creditos,1);

	while(!key[KEY_ESC])
	{
		draw_sprite(buffer,imgCreditos,0,0);
		draw_sprite(screen,buffer,0,0);
		vsync();
	}
	stop_midi();
	
	buffer = NULL;
	imgCreditos = NULL;

	delete buffer;
	delete imgCreditos;
}

void Mostra_GameOver()
{
	BITMAP *buffer = NULL;
	BITMAP *imgGameover = NULL;

	imgGameover = load_bitmap("gameover.bmp",NULL);
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	
	while(!key[KEY_ESC])
	{
		draw_sprite(buffer,imgGameover,0,0);
		draw_sprite(screen,buffer,0,0);
		vsync();
	}

	buffer = NULL;
	imgGameover = NULL;
	delete buffer;
	delete imgGameover;
}

void Mostra_Final()
{
	BITMAP *buffer = NULL;
	BITMAP *imgFinal1 = NULL;
	BITMAP *imgFinal2 = NULL;
	BITMAP *imgceu = NULL;
	
	int bombas = ( 50 + (rand() % 100) );

	SAMPLE *somexplosao = NULL;
	somexplosao = load_wav("explosao.wav");
	
	SAMPLE *somfinal = NULL;
	somfinal = load_wav("final.wav");
	
	imgFinal1 = load_bitmap("final1.bmp", NULL);
	imgFinal2 = load_bitmap("final2.bmp", NULL);
	imgceu = load_bitmap("ceu.bmp", NULL);

	buffer = create_bitmap(SCREEN_W, SCREEN_H);

	draw_sprite(buffer, imgFinal1, 0, 0);
	draw_sprite(screen, buffer, 0, 0);

	int i = 0;
	int j = 0;
	
	for (i=0; i<50; i++)
	{
		rest(50 + (rand() % 50));
		play_sample (somexplosao, 255, 128, 1000, 0);
	}

	Clarear(imgceu,2);
	Escurecer(2);
	clear(buffer);

	play_sample (somfinal, 255, 128, 1000, 0);

	while(!key[KEY_ESC])
	{
		draw_sprite(buffer,imgFinal2,0,0);
		draw_sprite(screen,buffer,0,0);
		vsync();
	}
	stop_sample(somfinal);
	
	buffer = NULL;
	imgFinal1 = NULL;
	imgFinal2 = NULL;
	somexplosao = NULL;
	somfinal = NULL;
	imgceu = NULL;
	
	delete buffer;
	delete imgFinal1;
	delete imgFinal2;
	delete somexplosao;
	delete somfinal;
	delete imgceu;
}
