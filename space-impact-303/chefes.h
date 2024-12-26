#ifndef CHEFES_H
#define CHEFES_H

#include <allegro5/allegro.h>
#include "projeteis.h"
#include "config.h"
#define INTERVALO_DISPARO_CHEFE 0.3 
#define VELOCIDADE_PROJETIL_CHEFE 2.0 


typedef struct
{
    float x, y;
    int largura, altura;
    int vidas;
    int ativo;
    float velocidade_y;
    float velocidade_x; 
    int entrando;       
    ALLEGRO_BITMAP *sprite;
    int invulneravel;          
    double tempo_invulneravel; 
    int hitbox_offset_x; 
    int hitbox_offset_y; 
    int hitbox_largura;  
    int hitbox_altura;   
    double tempo_laser; 
} Chefe;

typedef struct
{
    float x, y;
    int largura, altura;
    int vidas;
    int ativo;
    float velocidade_y;
    float velocidade_x; 
    int entrando;       
    ALLEGRO_BITMAP *sprite;
    int invulneravel;          
    double tempo_invulneravel; 
    int hitbox_offset_x; 
    int hitbox_offset_y; 
    int hitbox_largura;  
    int hitbox_altura;   
    int laser_ativo;    
    double tempo_laser; 
    double tempo_projetil_circular; 

} ChefeFase2;

extern int VELOCIDADE_CHEFE;


void inicializar_chefe(Chefe *chefe);
void atualizar_chefe(Chefe *chefe, ProjetilBoss projeteis_chefe[], ALLEGRO_BITMAP *sprite_laser);
void desenhar_chefe(Chefe *chefe);
void disparar_projetil_chefe(ProjetilBoss projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite);
void disparar_laser_boss1(ProjetilBoss projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite);
void reduzir_hp_chefe(Chefe *chefe, int dano);
void inicializar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[]);
void disparar_projetil_chefe_comum(ProjetilBoss projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite);
void disparar_projetil_ricochete(Chefe *chefe, ProjetilBoss projeteis_ricochete[], ALLEGRO_BITMAP *sprite);
void atualizar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[]);
void desenhar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[]);



void inicializar_chefe_fase2(ChefeFase2 *chefe);
void atualizar_chefe_fase2(ChefeFase2 *chefe, ProjetilBossFase2 projeteis_chefe[], ALLEGRO_BITMAP *sprite_laser, ALLEGRO_BITMAP *sprite_projetil_circular);;
void desenhar_chefe_fase2(ChefeFase2 *chefe);
void disparar_laser_fase2(ProjetilBossFase2 projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite);

#endif // CHEFES_H