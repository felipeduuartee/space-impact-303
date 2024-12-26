#ifndef INIMIGOS_H
#define INIMIGOS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "projeteis.h"
#include "nave_jogador.h"

#define VELOCIDADE_INIMIGO 2
#define VELOCIDADE_PROJETIL_INIMIGO 3
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define MAX_INIMIGOS 3
#define DISTANCIA_SEGURA 150  

typedef struct {
    float x, y;                
    int largura, altura;       
    int hitbox_largura, hitbox_altura; 
    int hitbox_offset_x, hitbox_offset_y; 
    int ativo;                 
    int direcao_y;             
    int tipo;                  
    ALLEGRO_BITMAP *sprite;    
} Inimigo;


// Funções para inicializar, atualizar e desenhar os inimigos
void inicializar_inimigos(Inimigo inimigos[]);
void atualizar_inimigos(Inimigo inimigos[], ProjetilInimigo projeteis[]);
void gerar_novos_inimigos(Inimigo inimigos[], NaveJogador *nave,
                          ALLEGRO_BITMAP *sprite_inimigo1, ALLEGRO_BITMAP *sprite_inimigo2, int chefe_ativo);
void desenhar_inimigos(Inimigo inimigos[], ALLEGRO_BITMAP *sprite_inimigo1, ALLEGRO_BITMAP *sprite_inimigo2);

#endif // INIMIGOS_H
