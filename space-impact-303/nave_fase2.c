#include "nave_fase2.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> // Para desenhar formas primitivas

#define VELOCIDADE_NAVE 5

void inicializar_nave_fase2(NaveJogadorFase2 *nave) {
    nave->x = 50;
    nave->y = 250; // Posição inicial mais alta
    nave->vidas = 3;
    nave->invulneravel = 0;
    nave->tempo_invulneravel = 0;
    nave->especial_coletado = 0; 
    nave->especial_ativo = 0; // Inicializa como não coletado
    nave->sprite = al_load_bitmap("nave2.png"); // Sprite específico para a nave da Fase 2

    if (nave->sprite) {
        nave->largura = al_get_bitmap_width(nave->sprite);
        nave->altura = al_get_bitmap_height(nave->sprite);


        nave->hitbox_largura = nave->largura - 50; // Hitbox menor
        nave->hitbox_altura = nave->largura - 30;  // Hitbox mais quadrada


        nave->hitbox_offset_x = -10;
        nave->hitbox_offset_y = -35; // Aumenta o deslocamento para cima
    } else {

        nave->largura = 50;
        nave->altura = 30;
        nave->hitbox_largura = 20;
        nave->hitbox_altura = 20;
        nave->hitbox_offset_x = 10;
        nave->hitbox_offset_y = -35; // Sobe mais a hitbox
    }
}

void atualizar_nave_fase2(NaveJogadorFase2 *nave, int direcao_x, int direcao_y) {
    nave->x += direcao_x * VELOCIDADE_NAVE;
    nave->y += direcao_y * VELOCIDADE_NAVE;


    if (nave->x < 0) nave->x = 0;
    if (nave->x > 800 - nave->largura) nave->x = 800 - nave->largura;
    if (nave->y < 0) nave->y = 0;
    if (nave->y > 600 - nave->altura) nave->y = 600 - nave->altura;


    if (nave->invulneravel && al_get_time() - nave->tempo_invulneravel > 0.4) {
        nave->invulneravel = 0; // Invulnerabilidade dura 0.4 segundos
    }
}

void desenhar_nave_fase2(NaveJogadorFase2 *nave, ALLEGRO_BITMAP *sprite_nave) {

    if (nave->invulneravel) {

        if ((int)(al_get_time() * 10) % 2 == 0) {
            al_draw_bitmap(sprite_nave, nave->x, nave->y, 0);
        }
    } else {

        al_draw_bitmap(sprite_nave, nave->x, nave->y, 0);
    }


    al_draw_rectangle(
        nave->x + nave->hitbox_offset_x,              // Posição X da hitbox
        nave->y + nave->hitbox_offset_y,              // Posição Y da hitbox
        nave->x + nave->hitbox_offset_x + nave->hitbox_largura,  // Largura da hitbox
        nave->y + nave->hitbox_offset_y + nave->hitbox_altura,   // Altura da hitbox
        al_map_rgb(255, 0, 0), 2                      // Cor vermelha com espessura da linha 2
    );
}
