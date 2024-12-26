#ifndef FASE2_H
#define FASE2_H

#include <allegro5/allegro.h>
#include "projeteis.h"
#include "nave_jogador.h"
#include "nave_fase2.h"

#define MAX_INIMIGOS_FASE2 3
#define VELOCIDADE_INIMIGO_FASE2 2
#define VELOCIDADE_PROJETIL_INIMIGO_FASE2 4
#define PROJETIL_LENTO 2


typedef struct
{
    float x, y;
    int largura, altura;
    int hitbox_largura, hitbox_altura;    
    int hitbox_offset_x, hitbox_offset_y; 
    int ativo;
    int direcao_y;
    int tipo;               
    double tempo_ativacao; 
    ALLEGRO_BITMAP *sprite; 
} InimigoFase2;


void inicializar_inimigos_fase2(InimigoFase2 inimigos_fase2[]);
void atualizar_inimigos_fase2(InimigoFase2 inimigos_fase2[], ProjetilInimigo projeteis_fase2[], int especial3_ativo);
void gerar_novos_inimigos_fase2(InimigoFase2 inimigos_fase2[], NaveJogador *nave, ALLEGRO_BITMAP *sprite_inimigo1_fase2, ALLEGRO_BITMAP *sprite_inimigo2_fase2, int chefe_ativo);
void desenhar_inimigos_fase2(InimigoFase2 inimigos_fase2[], ALLEGRO_BITMAP *sprite_inimigo1_fase2, ALLEGRO_BITMAP *sprite_inimigo2_fase2);

#endif // FASE2_H
