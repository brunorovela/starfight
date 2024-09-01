#include <allegro.h>

void Instala_Drivers();

void Instala_Drivers()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT,800,600,0,0);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);	
}
