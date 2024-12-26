#include "projeteis.h"
#include <allegro5/allegro.h>
#include <math.h>

#define VELOCIDADE_PROJETIL 5
#define VELOCIDADE_PROJETIL_INIMIGO 4
#define PROJETIL_LENTO 2
#define VELOCIDADE_PROJETIL_ESPECIAL 20

void inicializar_projeteis(Projetil projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        projeteis[i].ativo = 0;
        projeteis[i].sprite = NULL;
    }
}

void disparar_projetil(Projetil projeteis[], float x, float y, int especial_ativo,
                       ALLEGRO_BITMAP *sprite_bala_normal, ALLEGRO_BITMAP *sprite_bala_especial)
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (!projeteis[i].ativo)
        {
            ALLEGRO_BITMAP *sprite_atual = especial_ativo ? sprite_bala_especial : sprite_bala_normal;

            projeteis[i].x = x;
            projeteis[i].y = y;
            projeteis[i].largura = al_get_bitmap_width(sprite_atual);
            projeteis[i].altura = al_get_bitmap_height(sprite_atual);
            projeteis[i].ativo = 1;
            projeteis[i].velocidade = especial_ativo ? VELOCIDADE_PROJETIL_ESPECIAL : VELOCIDADE_PROJETIL;
            projeteis[i].sprite = sprite_atual;

            projeteis[i].hitbox_offset_x = projeteis[i].largura / 4;
            projeteis[i].hitbox_offset_y = projeteis[i].altura / 4;
            projeteis[i].hitbox_largura = projeteis[i].largura / 2;
            projeteis[i].hitbox_altura = projeteis[i].altura / 2;

            break;
        }
    }
}

void atualizar_projeteis(Projetil projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo)
        {
            projeteis[i].x += projeteis[i].velocidade;
            if (projeteis[i].x > LARGURA_TELA)
            {
                projeteis[i].ativo = 0;
            }
        }
    }
}

void desenhar_projeteis(Projetil projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo && projeteis[i].sprite)
        {

            al_draw_bitmap(projeteis[i].sprite, projeteis[i].x, projeteis[i].y, 0);

            // al_draw_rectangle(
            //     projeteis[i].x + projeteis[i].hitbox_offset_x,
            //     projeteis[i].y + projeteis[i].hitbox_offset_y,
            //     projeteis[i].x + projeteis[i].hitbox_offset_x + projeteis[i].hitbox_largura,
            //     projeteis[i].y + projeteis[i].hitbox_offset_y + projeteis[i].hitbox_altura,
            //     al_map_rgb(255, 0, 0),
            //     1.5
            // );
        }
    }
}

void inicializar_projeteis_inimigos(ProjetilInimigo projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        projeteis[i].ativo = 0;
        projeteis[i].sprite = NULL;

        projeteis[i].hitbox_offset_x = 0;
        projeteis[i].hitbox_offset_y = 0;
        projeteis[i].hitbox_largura = 0;
        projeteis[i].hitbox_altura = 0;
    }
}

void disparar_projetil_inimigo(ProjetilInimigo projeteis[], float x, float y, ALLEGRO_BITMAP *sprite)
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        if (!projeteis[i].ativo)
        {
            projeteis[i].x = x;
            projeteis[i].y = y;
            projeteis[i].largura = al_get_bitmap_width(sprite);
            projeteis[i].altura = al_get_bitmap_height(sprite);
            projeteis[i].ativo = 1;
            projeteis[i].dx = -VELOCIDADE_PROJETIL_INIMIGO;
            projeteis[i].sprite = sprite;
            projeteis[i].hitbox_offset_x = 0; 
            projeteis[i].hitbox_offset_y = 0; 
            projeteis[i].hitbox_largura = 34; 
            projeteis[i].hitbox_altura = 9;   

            break;
        }
    }
}

void atualizar_projeteis_inimigos(ProjetilInimigo projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        if (projeteis[i].ativo)
        {
            projeteis[i].x += projeteis[i].dx;
            if (projeteis[i].x < 0 || projeteis[i].x > LARGURA_TELA)
            {
                projeteis[i].ativo = 0;
            }
        }
    }
}

void desenhar_projeteis_inimigos(ProjetilInimigo projeteis[],
                                 ALLEGRO_BITMAP *sprite_projeteis1, ALLEGRO_BITMAP *sprite_projeteis2)
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        if (projeteis[i].ativo)
        {

            ALLEGRO_BITMAP *sprite = (projeteis[i].tipo == 0) ? sprite_projeteis1 : sprite_projeteis2;
            if (sprite)
            {

                al_draw_bitmap(sprite, projeteis[i].x, projeteis[i].y, 0);

                // al_draw_rectangle(
                //     projeteis[i].x + projeteis[i].hitbox_offset_x,
                //     projeteis[i].y + projeteis[i].hitbox_offset_y,
                //     projeteis[i].x + projeteis[i].hitbox_offset_x + projeteis[i].hitbox_largura,
                //     projeteis[i].y + projeteis[i].hitbox_offset_y + projeteis[i].hitbox_altura,
                //     al_map_rgb(255, 0, 0), // Cor vermelha
                //     1.5                    // Espessura da linha
                // );
            }
        }
    }
}

void inicializar_projeteis_chefe(ProjetilBoss projeteis_chefe[])
{
    for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
    {
        projeteis_chefe[i].ativo = 0;
        projeteis_chefe[i].sprite = NULL;

        projeteis_chefe[i].hitbox_offset_x = 0;
        projeteis_chefe[i].hitbox_offset_y = 0;
        projeteis_chefe[i].hitbox_largura = 10;
        projeteis_chefe[i].hitbox_altura = 10;
    }
}

void desenhar_projeteis_chefe(ProjetilBoss projeteis_chefe[], ALLEGRO_BITMAP *sprite_tiro_comum, ALLEGRO_BITMAP *sprite_laser)
{
    for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
    {
        if (projeteis_chefe[i].ativo && projeteis_chefe[i].sprite)
        {

            ALLEGRO_BITMAP *sprite_atual = projeteis_chefe[i].sprite == sprite_laser ? sprite_laser : sprite_tiro_comum;

            al_draw_bitmap(sprite_atual, projeteis_chefe[i].x, projeteis_chefe[i].y, 0);

            // al_draw_rectangle(
            //     projeteis_chefe[i].x + projeteis_chefe[i].hitbox_offset_x,
            //     projeteis_chefe[i].y + projeteis_chefe[i].hitbox_offset_y,
            //     projeteis_chefe[i].x + projeteis_chefe[i].hitbox_offset_x + projeteis_chefe[i].hitbox_largura,
            //     projeteis_chefe[i].y + projeteis_chefe[i].hitbox_offset_y + projeteis_chefe[i].hitbox_altura,
            //     al_map_rgb(255, 0, 0), // Cor vermelha
            //     1.5                    // Espessura da linha
            // );
        }
    }
}

void atualizar_projeteis_chefe(ProjetilBoss projeteis_chefe[])
{
    for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
    {
        if (projeteis_chefe[i].ativo)
        {

            projeteis_chefe[i].x += projeteis_chefe[i].dx;
            projeteis_chefe[i].y += projeteis_chefe[i].dy;

            if (projeteis_chefe[i].x + projeteis_chefe[i].largura < 0 ||
                projeteis_chefe[i].y + projeteis_chefe[i].altura < 0 ||
                projeteis_chefe[i].y > ALTURA_TELA)
            {
                projeteis_chefe[i].ativo = 0; 
            }
        }
    }
}

void inicializar_projeteis_inimigos_fase2(ProjetilInimigo projeteis[])
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        projeteis[i].ativo = 0;
        projeteis[i].sprite = NULL;
    }
}

void disparar_projetil_inimigo_fase2(ProjetilInimigo projeteis_fase2[], float x, float y, int especial3_ativo, ALLEGRO_BITMAP *sprite)
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        if (!projeteis_fase2[i].ativo)
        {
            projeteis_fase2[i].x = x;
            projeteis_fase2[i].y = y;
            projeteis_fase2[i].largura = al_get_bitmap_width(sprite);
            projeteis_fase2[i].altura = al_get_bitmap_height(sprite);
            projeteis_fase2[i].ativo = 1;
            projeteis_fase2[i].dx = especial3_ativo ? -PROJETIL_LENTO : -VELOCIDADE_PROJETIL_INIMIGO;
            projeteis_fase2[i].sprite = sprite;
            break;
        }
    }
}

void atualizar_projeteis_inimigos_fase2(ProjetilInimigo projeteis_fase2[])
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        if (projeteis_fase2[i].ativo)
        {
            projeteis_fase2[i].x += projeteis_fase2[i].dx;
            if (projeteis_fase2[i].x < 0 || projeteis_fase2[i].x > LARGURA_TELA)
            {
                projeteis_fase2[i].ativo = 0;
            }
        }
    }
}

void desenhar_projeteis_inimigos_fase2(ProjetilInimigo projeteis_fase2[],
                                       ALLEGRO_BITMAP *sprite_projeteis3, ALLEGRO_BITMAP *sprite_projeteis4)
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        if (projeteis_fase2[i].ativo)
        {

            ALLEGRO_BITMAP *sprite = (projeteis_fase2[i].tipo == 0) ? sprite_projeteis3 : sprite_projeteis4;
            if (sprite)
            {

                al_draw_bitmap(sprite, projeteis_fase2[i].x, projeteis_fase2[i].y, 0);

                // al_draw_rectangle(
                //     projeteis_fase2[i].x + projeteis_fase2[i].hitbox_offset_x,
                //     projeteis_fase2[i].y + projeteis_fase2[i].hitbox_offset_y,
                //     projeteis_fase2[i].x + projeteis_fase2[i].hitbox_offset_x + projeteis_fase2[i].hitbox_largura,
                //     projeteis_fase2[i].y + projeteis_fase2[i].hitbox_offset_y + projeteis_fase2[i].hitbox_altura,
                //     al_map_rgb(255, 0, 0), // Cor vermelha
                //     1.5                    // Espessura da linha
                // );
            }
        }
    }
}

void inicializar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis)
{
    for (int i = 0; i < max_projeteis; i++)
    {
        projeteis[i].ativo = 0;
        projeteis[i].sprite = NULL;

        projeteis[i].hitbox_offset_x = 0;
        projeteis[i].hitbox_offset_y = 0;
        projeteis[i].hitbox_largura = 10;
        projeteis[i].hitbox_altura = 10;
    }
}

void disparar_projetil_circular(ProjetilBossFase2 projeteis[], int max_projeteis, float x, float y, float velocidade, ALLEGRO_BITMAP *sprite)
{
    if (!sprite)
    {
        fprintf(stderr, "Erro: sprite do projétil circular é NULL.\n");
        return;
    }

    int num_projeteis = 12;
    float angulo_inicial = 0.0;

    for (int i = 0; i < max_projeteis; i++)
    {
        if (!projeteis[i].ativo)
        {
            for (int j = 0; j < num_projeteis; j++)
            {
                if (i + j >= max_projeteis)
                {
                    break;
                }

                float angulo = angulo_inicial + (j * (2 * M_PI / num_projeteis));

                projeteis[i + j].x = x;
                projeteis[i + j].y = y;
                projeteis[i + j].largura = al_get_bitmap_width(sprite);
                projeteis[i + j].altura = al_get_bitmap_height(sprite);
                projeteis[i + j].dx = cos(angulo) * velocidade;
                projeteis[i + j].dy = sin(angulo) * velocidade;
                projeteis[i + j].ativo = 1;
                projeteis[i + j].sprite = sprite;
                projeteis[i + j].tipo = TIPO_PROJETIL_CIRCULAR;

                projeteis[i + j].hitbox_offset_x = 2;
                projeteis[i + j].hitbox_offset_y = 2;
                projeteis[i + j].hitbox_largura = projeteis[i + j].largura - 4;
                projeteis[i + j].hitbox_altura = projeteis[i + j].altura - 4;
            }
            break;
        }
    }
}

void atualizar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis)
{
    for (int i = 0; i < max_projeteis; i++)
    {
        if (projeteis[i].ativo)
        {
            projeteis[i].x += projeteis[i].dx;
            projeteis[i].y += projeteis[i].dy;

            if (projeteis[i].x + projeteis[i].largura < 0 || projeteis[i].x > LARGURA_TELA ||
                projeteis[i].y + projeteis[i].altura < 0 || projeteis[i].y > ALTURA_TELA)
            {
                projeteis[i].ativo = 0;
            }
        }
    }
}

void desenhar_projeteis_chefe_fase2(ProjetilBossFase2 projeteis[], int max_projeteis)
{
    for (int i = 0; i < max_projeteis; i++)
    {
        if (projeteis[i].ativo)
        {
            if (projeteis[i].sprite != NULL)
            {

                al_draw_bitmap(projeteis[i].sprite, projeteis[i].x, projeteis[i].y, 0);

                // al_draw_rectangle(
                //     projeteis[i].x + projeteis[i].hitbox_offset_x,
                //     projeteis[i].y + projeteis[i].hitbox_offset_y,
                //     projeteis[i].x + projeteis[i].hitbox_offset_x + projeteis[i].hitbox_largura,
                //     projeteis[i].y + projeteis[i].hitbox_offset_y + projeteis[i].hitbox_altura,
                //     al_map_rgb(255, 0, 0), // Cor vermelha
                //     1.5                    // Espessura da linha
                // );
            }
            else
            {

                fprintf(stderr, "Erro: projeteis_chefe[%d].sprite é NULL.\n", i);
            }
        }
    }
}
