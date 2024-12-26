#include "hud.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

void desenhar_hud(ALLEGRO_FONT *fonte, int vidas, int pontuacao, double tempo_fase, NaveJogador *nave)
{
    char texto[50];

    sprintf(texto, "Vidas: %d", vidas);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 10, 10, 0, texto);

    sprintf(texto, "Pontuação: %d", pontuacao);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 10, 30, 0, texto);

    sprintf(texto, "Tempo: %.1f", tempo_fase);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 10, 50, 0, texto);

    if (nave->especial_coletado)
    {
        ALLEGRO_BITMAP *especial_sprite = al_load_bitmap("./imagens/especial-hud.jpeg");
        if (especial_sprite)
        {
            al_draw_bitmap(especial_sprite, 5, 70, 0);
            al_destroy_bitmap(especial_sprite);
        }
    }

    if (nave->especial3_coletado)
    {
        ALLEGRO_BITMAP *especial3_sprite = al_load_bitmap("./imagens/especial3-hud.jpeg");
        if (especial3_sprite)
        {
            al_draw_bitmap(especial3_sprite, 5, 70, 0);
            al_destroy_bitmap(especial3_sprite);
        }
    }

    if (nave->especial2_coletado)
    {
        ALLEGRO_BITMAP *especial2_sprite = al_load_bitmap("./imagens/especial2-hud.png");
        if (especial2_sprite)
        {
            al_draw_bitmap(especial2_sprite, 45, 70, 0);
            al_destroy_bitmap(especial2_sprite);
        }
    }
}
