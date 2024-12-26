#ifndef COLISOES_H
#define COLISOES_H

#include "itens.h"
#include "nave_jogador.h"
#include "projeteis.h"
#include "inimigos.h"
#include "inimigos_fase2.h"
#include "chefes.h"
#include "Joystick.h"

// Funções para detectar colisões
void detectar_colisao_projeteis_inimigos(Projetil projeteis[], Inimigo inimigos[], int *pontuacao, ItemDrop *item, int *inimigos_derrotados);
void detectar_colisao_nave_inimigos(NaveJogador *nave, Inimigo inimigos[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados);
void detectar_colisao_nave_chefe(NaveJogador *nave, Chefe *chefe, int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
void detectar_colisao_projeteis_nave(NaveJogador *nave, ProjetilInimigo projeteis_inimigos[], ProjetilBoss projeteis_boss[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados);
void detectar_colisao_projeteis_chefe(Chefe *chefe, Projetil projeteis[], int *pontuacao, int *chefe_derrotado, double *tempo_chefe_derrotado);
void detectar_colisao_nave_item(NaveJogador *nave, ItemDrop *item);
void detectar_colisao_projeteis_ricochete_nave(NaveJogador *nave, ProjetilBoss projeteis_ricochete[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados);

// Funções para detectar colisões na fase 2
void detectar_colisao_projeteis_inimigos_fase2(Projetil projeteis[], InimigoFase2 inimigos_fase2[], int *pontuacao, ItemDrop2 *item, ItemDrop3 *item3, int *inimigos_derrotados_fase2);
void detectar_colisao_nave_inimigos_fase2(NaveJogador *nave, InimigoFase2 inimigos_fase2[], int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
void detectar_colisao_projeteis_inimigos_fase2_nave(NaveJogador *nave, ProjetilInimigo projeteis_inimigos[], int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
void detectar_colisao_nave_chefe_fase2(NaveJogador *nave, ChefeFase2 *chefe_fase2, int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos);
void detectar_colisao_projeteis_chefe_fase2(ChefeFase2 *chefe_fase2, Projetil projeteis[], int *pontuacao, int *chefe_derrotado_fase2, double *tempo_chefe_derrotado_fase2);
void detectar_colisao_projeteis_chefe_fase2_nave(NaveJogador *nave, ProjetilBossFase2 projeteis_chefe[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados);
void detectar_colisao_nave_item_fase2(NaveJogador *nave, ItemDrop2 *item);
void detectar_colisao_nave_item3_fase2(NaveJogador *nave, ItemDrop3 *item);
void detectar_colisao_escudo(NaveJogador *nave, 
                             ProjetilInimigo projeteis_inimigos_fase2[], 
                             InimigoFase2 inimigos_fase2[]);


#endif // COLISOES_H
