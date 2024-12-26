#include "nave_jogador.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define VELOCIDADE_NAVE 4

void inicializar_nave(NaveJogador *nave)
{
    nave->x = 50;
    nave->y = 300;
    nave->largura = 58;
    nave->altura = 48;
    nave->vidas = 5;
    nave->invulneravel = 1;
    nave->tempo_invulneravel = al_get_time();
    nave->especial_ativo = 0;
    nave->especial_coletado = 0;
    nave->especial2_coletado = 0;
    nave->especial3_ativo = 0;
    nave->especial3_coletado = 0;
    nave->sprite = al_load_bitmap("./imagens/nave.png");

    nave->hitbox_largura = 40;
    nave->hitbox_altura = 35;
    nave->hitbox_offset_x = 9;
    nave->hitbox_offset_y = 7;

    nave->sprite_up[0] = al_load_bitmap("./imagens/nave_up1.png");
    nave->sprite_up[1] = al_load_bitmap("./imagens/nave_up2.png");
    nave->sprite_up[2] = al_load_bitmap("./imagens/nave_up3.png");

    nave->sprite_down[0] = al_load_bitmap("./imagens/nave_down1.png");
    nave->sprite_down[1] = al_load_bitmap("./imagens/nave_down2.png");
    nave->sprite_down[2] = al_load_bitmap("./imagens/nave_down3.png");

    nave->frame_atual = 0;
    nave->ultimo_frame_troca = al_get_time();
}

void atualizar_nave(NaveJogador *nave, int direcao_x, int direcao_y)
{
    nave->x += direcao_x * VELOCIDADE_NAVE;
    nave->y += direcao_y * VELOCIDADE_NAVE;

    if (nave->x < 0)
        nave->x = 0;
    if (nave->x > 800 - nave->largura)
        nave->x = 800 - nave->largura;
    if (nave->y < 0)
        nave->y = 0;
    if (nave->y > 600 - nave->altura)
        nave->y = 600 - nave->altura;
}

void desenhar_nave(NaveJogador *nave, ALLEGRO_BITMAP *sprite_nave, int direcao_y)
{
    ALLEGRO_BITMAP *sprite_atual = sprite_nave;

    // Se o especial2 estiver ativo, desenha o escudo ao redor da nave
    if (nave->especial2_ativo)
    {
        al_draw_circle(nave->x + nave->largura / 2, nave->y + nave->altura / 2, 40, al_map_rgb(0, 0, 255), 3); // Círculo azul com espessura 3
    }

    // Se a nave estiver invulnerável, aplica o efeito de invulnerabilidade
    if (nave->invulneravel)
    {
        // Intermitência visual (piscar) quando a nave está invulnerável
        if ((int)(al_get_time() * 10) % 2 == 0)
        {
            al_draw_bitmap(sprite_atual, nave->x, nave->y, 0);
        }

        // Verifica se o tempo de invulnerabilidade já passou (nave fica vulnerável novamente após 0.4 segundos)
        if (al_get_time() - nave->tempo_invulneravel > 0.4)
        {
            nave->invulneravel = 0; // Desativa a invulnerabilidade
        }
    }
    else
    {
        // Se a nave não estiver invulnerável, decide qual sprite desenhar com base na direção
        if (direcao_y < 0)
        {
            sprite_atual = nave->sprite_up[nave->frame_atual];
        }
        else if (direcao_y > 0)
        {
            sprite_atual = nave->sprite_down[nave->frame_atual];
        }
        else
        {
            sprite_atual = sprite_nave;
        }

        // Atualiza o frame da animação da nave com base no tempo
        if (direcao_y != 0)
        {
            double tempo_atual = al_get_time();
            if (tempo_atual - nave->ultimo_frame_troca >= 0.1)
            {
                nave->frame_atual = (nave->frame_atual + 1) % 3; // Ciclando entre os frames da animação
                nave->ultimo_frame_troca = tempo_atual;
            }
        }
        else
        {
            nave->frame_atual = 0; // Reseta para o frame padrão quando não está subindo/descendo
        }

        // Desenha a nave normalmente (sem invulnerabilidade)
        al_draw_bitmap(sprite_atual, nave->x, nave->y, 0);
    }

    // Aqui está um código comentado que pode ser usado para desenhar a hitbox (caso precise debugar ou verificação da colisão)
    // al_draw_rectangle(
    //     nave->x + nave->hitbox_offset_x,
    //     nave->y + nave->hitbox_offset_y,
    //     nave->x + nave->hitbox_offset_x + nave->hitbox_largura,
    //     nave->y + nave->hitbox_offset_y + nave->hitbox_altura,
    //     al_map_rgb(255, 0, 0),  // Cor vermelha
    //     2                       // Espessura da linha do retângulo
    // );
}