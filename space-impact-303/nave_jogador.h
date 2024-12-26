#ifndef NAVE_JOGADOR_H
#define NAVE_JOGADOR_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// Estrutura para a nave do jogador
typedef struct
{
    float x, y;
    int largura, altura;
    int hitbox_largura, hitbox_altura;    // Dimensões da hitbox
    int hitbox_offset_x, hitbox_offset_y; // Deslocamento da hitbox
    int vidas;
    int invulneravel;
    double tempo_invulneravel;
    int especial_ativo;    // Indica se o ataque especial está ativo
    int especial_coletado; // Indica se o especial foi coletado
    int especial2_coletado;
    int especial3_coletado;
    int especial3_ativo;
    int especial2_ativo;
    double tempo_especial2;
    double tempo_especial3;
    double tempo_especial;
    ALLEGRO_BITMAP *sprite;

    // Adicionamos as novas variáveis:
    ALLEGRO_BITMAP *sprite_up[3];   // Sprites para quando a nave sobe
    ALLEGRO_BITMAP *sprite_down[3]; // Sprites para quando a nave desce
    int frame_atual;                // Controle do frame atual da animação
    double ultimo_frame_troca;      // Tempo da última troca de frame
} NaveJogador;

// Funções para inicializar, atualizar e desenhar a nave
void inicializar_nave(NaveJogador *nave);
void atualizar_nave(NaveJogador *nave, int direcao_x, int direcao_y);
void desenhar_nave(NaveJogador *nave, ALLEGRO_BITMAP *sprite_nave, int direcao_y);
#endif // NAVE_JOGADOR_H
