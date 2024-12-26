#ifndef PROJETEIS_H
#define PROJETEIS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "config.h"

// Definições de constantes
#define MAX_PROJETEIS 50
#define MAX_PROJETEIS_INIMIGOS 50
#define MAX_PROJETEIS_BOSS 50
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define MAX_PROJETEIS_INIMIGOS_FASE2 10
#define M_PI 3.14159265358979323846
#define TIPO_LASER_BOSS 1 // Defina um tipo para identificar o laser do chefe


// Estrutura para projéteis do jogador
typedef struct
{
    float x, y;
    int largura, altura;
    int ativo;
    float velocidade;
    int hitbox_offset_x, hitbox_offset_y;
    int hitbox_largura, hitbox_altura;
    ALLEGRO_BITMAP *sprite;

} Projetil;

// Estrutura para projéteis dos inimigos
typedef struct
{
    float x, y;
    int largura, altura;
    int ativo;
    float dx, dy;
    int tipo;
    int hitbox_offset_x, hitbox_offset_y;
    int hitbox_largura, hitbox_altura;
    ALLEGRO_BITMAP *sprite;
} ProjetilInimigo;

typedef struct
{
    float x, y;
    int largura, altura;
    int ativo;
    float dx, dy; // Adicionando dy para definir movimento vertical
    ALLEGRO_BITMAP *sprite;

    // Hitbox
    int hitbox_offset_x, hitbox_offset_y;
    int hitbox_largura, hitbox_altura;
    int tipo; // Novo campo para identificar o tipo de projétil
} ProjetilBoss;

typedef struct
{
    float x, y;             // Posições do projétil
    int largura, altura;    // Tamanho do projétil
    int ativo;              // Indica se o projétil está ativo
    float dx, dy;           // Velocidade nos eixos x e y
    float velocidade;       // Velocidade do projétil
    ALLEGRO_BITMAP *sprite; // Sprite do projétil

    // Hitbox
    int hitbox_offset_x, hitbox_offset_y;
    int hitbox_largura, hitbox_altura;

        int tipo; // Novo campo para identificar o tipo do projétil
} ProjetilBossFase2;

// Funções para projéteis do jogador
void inicializar_projeteis(Projetil projeteis[]);
void disparar_projetil(Projetil projeteis[], float x, float y, int especial_ativo,
                       ALLEGRO_BITMAP *sprite_bala_normal, ALLEGRO_BITMAP *sprite_bala_especial);
void atualizar_projeteis(Projetil projeteis[]);
void desenhar_projeteis(Projetil projeteis[]);

// Funções para projéteis dos inimigos da Fase 1
void inicializar_projeteis_inimigos(ProjetilInimigo projeteis[]);
void disparar_projetil_inimigo(ProjetilInimigo projeteis[], float x, float y, ALLEGRO_BITMAP *sprite);
void atualizar_projeteis_inimigos(ProjetilInimigo projeteis[]);
void desenhar_projeteis_inimigos(ProjetilInimigo projeteis[],
                                 ALLEGRO_BITMAP *sprite_projeteis1, ALLEGRO_BITMAP *sprite_projeteis2);

// Funções para projéteis dos inimigos da Fase 2
void inicializar_projeteis_inimigos_fase2(ProjetilInimigo projeteis_fase2[]);
void disparar_projetil_inimigo_fase2(ProjetilInimigo projeteis_fase2[], float x, float y, int especial3_ativo, ALLEGRO_BITMAP *sprite);
void atualizar_projeteis_inimigos_fase2(ProjetilInimigo projeteis_fase2[]);
void desenhar_projeteis_inimigos_fase2(ProjetilInimigo projeteis_fase2[],
                                       ALLEGRO_BITMAP *sprite_projeteis3, ALLEGRO_BITMAP *sprite_projeteis4);

// Funções para projéteis do chefe
void inicializar_projeteis_chefe(ProjetilBoss projeteis_chefe[]);
void atualizar_projeteis_chefe(ProjetilBoss projeteis_chefe[]);
void desenhar_projeteis_chefe(ProjetilBoss projeteis_chefe[], ALLEGRO_BITMAP *sprite_tiro_comum, ALLEGRO_BITMAP *sprite_laser);

void inicializar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis);
void atualizar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis);
void disparar_projetil_circular(ProjetilBossFase2 projeteis[], int max_projeteis, float x, float y, float velocidade, ALLEGRO_BITMAP *sprite);
void desenhar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis);








#endif // PROJETEIS_H
