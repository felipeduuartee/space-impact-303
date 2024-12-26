#ifndef NAVE_FASE2_H
#define NAVE_FASE2_H

#include <allegro5/allegro.h>

// Estrutura para a nave do jogador na Fase 2
typedef struct {
    float x, y;
    int largura, altura;
    int hitbox_largura, hitbox_altura; // Dimensões da hitbox
    int hitbox_offset_x, hitbox_offset_y; // Deslocamento da hitbox
    int vidas;
    int invulneravel;
    double tempo_invulneravel;
    int especial_ativo; // Ativa se o ataque especial for coletado
    int especial_coletado;   // Indica se o especial foi coletado
    double tempo_especial;
    ALLEGRO_BITMAP *sprite;
} NaveJogadorFase2;

// Funções para inicializar, atualizar e desenhar a nave da Fase 2
void inicializar_nave_fase2(NaveJogadorFase2 *nave);
void atualizar_nave_fase2(NaveJogadorFase2 *nave, int direcao_x, int direcao_y);
void desenhar_nave_fase2(NaveJogadorFase2 *nave, ALLEGRO_BITMAP *sprite_nave);

#endif // NAVE_FASE2_H
