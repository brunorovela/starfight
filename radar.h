#include <allegro.h>

void radar_atualiza(BITMAP *,int,int);

void radar_atualiza(BITMAP *buffer_radar,int x, int y)
{
	_putpixel32(buffer_radar, x/7, (y+33)/7, makecol(255,255,0)); // precisão
}
