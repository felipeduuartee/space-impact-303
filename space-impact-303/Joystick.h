#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <math.h>
#include <stdio.h>

// Adicionando as inclusões dos headers necessários
#include "nave_jogador.h"
#include "projeteis.h"
#include "inimigos.h"
#include "itens.h"
#include "inimigos_fase2.h"
#include "chefes.h"

// Declaração da estrutura `joystick`
typedef struct {
    unsigned char right; // Botão de movimentação à direita
    unsigned char left;  // Botão de movimentação à esquerda
    unsigned char up;    // Botão de movimentação para cima
    unsigned char down;  // Botão de movimentação para baixo
    unsigned char shot; // tiro
} joystick;

// Declaração das funções do joystick
joystick* joystick_create();                   // Criação de um controle de joystick
void joystick_destroy(joystick *element);      // Destruição do controle de joystick
void joystick_right(joystick *element);        // Ativa/desativa o botão direito
void joystick_left(joystick *element);         // Ativa/desativa o botão esquerdo
void joystick_up(joystick *element);           // Ativa/desativa o botão para cima
void joystick_down(joystick *element);         // Ativa/desativa o botão para baixo



void limpar_fila_eventos(ALLEGRO_EVENT_QUEUE *fila_eventos);
int exibir_tela_pausa(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background_pausa, ALLEGRO_EVENT_QUEUE *fila_eventos);
int exibir_menu(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_FONT *font_felipe, ALLEGRO_BITMAP *background_jogo);
void exibir_tela_controles(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
int tela_game_over(int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background_game_over);
void exibir_texto_gradualmente(const char* texto, ALLEGRO_FONT* fonte, float x, float y, ALLEGRO_COLOR cor, float intervalo_entre_letras);
void reiniciar_jogo(NaveJogador *nave, Chefe *chefe, Projetil projeteis[], ProjetilInimigo projeteis_inimigos[], ProjetilBoss projeteis_chefe[], Inimigo inimigos[], ItemDrop *item, int *pontuacao, int *chefe_ativo, double *tempo_inicio, int *game_over, ALLEGRO_EVENT_QUEUE *fila_eventos);
void reinicializar_todos_projeteis(ProjetilInimigo projeteis_fase1[], ProjetilInimigo projeteis_fase2[], ProjetilBoss projeteis_chefe[], Projetil projeteis_jogador[]);
int tela_vitoria(int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background_vitoria);
void exibir_texto_corrido(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
void resetar_controle(joystick *element);
void exibir_dialogo(ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background);

#endif // JOYSTICK_H
