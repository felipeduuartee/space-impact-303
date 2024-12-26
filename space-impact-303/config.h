#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#define INTERVALO_DISPARO 0.2
#define INTERVALO_DISPARO_ESPECIAL 0.1
#define LARGURA_TELA 800
#define ALTURA_TELA 600

#define DURACAO_ESPECIAL 5.0
#define TAMANHO_FONTE 32
#define MAX_PROJETEIS_RICOCHETE 20         
#define DURACAO_LASER 2.0
#define PAUSA_LASER 1.5

#define VELOCIDADE_PROJETIL_CHEFE2 4.0  
#define DURACAO_LASER_FASE2 1.0        
#define PAUSA_LASER_FASE2 0.2          
#define VELOCIDADE_LASER_CHEFE2 10.0    
#define INTERVALO_DISPARO_CIRCULAR 5.0 
#define VELOCIDADE_PROJETIL_CIRCULAR 10.0
#define MAX_PROJETEIS_BOSS_FASE2 50    
#define TIPO_PROJETIL_LASER     1
#define TIPO_PROJETIL_CIRCULAR  2
#define DURACAO_INVULNERAVEL 1

