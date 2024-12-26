#include "inimigos_fase2.h"
#include "projeteis.h"
#include "nave_fase2.h"
#include <allegro5/allegro.h>
#include <stdlib.h> // Para função rand()
#include <math.h>   // Para função sqrt()

#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define DISTANCIA_SEGURA 150 // Distância mínima entre a nave e os inimigos ao iniciar

static double ultimo_disparo_inimigo_fase2[MAX_INIMIGOS_FASE2]; // Armazena o tempo do último disparo de cada inimigo da fase 2
static double intervalo_disparo_inimigo_fase2 = 1.7;            // Tempo entre disparos dos inimigos da fase 2

void inicializar_inimigos_fase2(InimigoFase2 inimigos_fase2[])
{
    int posicao_inicial_x = LARGURA_TELA + 100;
    int margem_superior = 50;

    for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
    {
        inimigos_fase2[i].ativo = 1;
        inimigos_fase2[i].x = posicao_inicial_x + (rand() % 200);
        inimigos_fase2[i].y = margem_superior + (rand() % (ALTURA_TELA - 2 * margem_superior));
        inimigos_fase2[i].largura = 128; // Largura da sprite do inimigo da fase 2
        inimigos_fase2[i].altura = 128;  // Altura da sprite do inimigo da fase 2

        inimigos_fase2[i].hitbox_largura = inimigos_fase2[i].largura * 0.7; // 70% da largura da sprite
        inimigos_fase2[i].hitbox_altura = inimigos_fase2[i].altura * 0.6;   // 70% da altura da sprite

        inimigos_fase2[i].hitbox_offset_x = (inimigos_fase2[i].largura - inimigos_fase2[i].hitbox_largura) / 2;
        inimigos_fase2[i].hitbox_offset_y = (inimigos_fase2[i].altura - inimigos_fase2[i].hitbox_altura) / 2;

        inimigos_fase2[i].direcao_y = (rand() % 2) ? 1 : -1;
        inimigos_fase2[i].tipo = i % 2;

        inimigos_fase2[i].sprite = (inimigos_fase2[i].tipo == 0) ? al_load_bitmap("enemy_fase2_1.png") : al_load_bitmap("enemy_fase2_2.png");
    }
}

void atualizar_inimigos_fase2(InimigoFase2 inimigos_fase2[], ProjetilInimigo projeteis_fase2[], int especial3_ativo)
{
    double tempo_atual = al_get_time();

    for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
    {
        if (inimigos_fase2[i].ativo)
        {

            inimigos_fase2[i].x -= VELOCIDADE_INIMIGO_FASE2;

            inimigos_fase2[i].y += inimigos_fase2[i].direcao_y * 2;

            int hitbox_top = inimigos_fase2[i].y + inimigos_fase2[i].hitbox_offset_y;
            int hitbox_bottom = hitbox_top + inimigos_fase2[i].hitbox_altura;

            if (hitbox_top < 0)
            {
                inimigos_fase2[i].y = -inimigos_fase2[i].hitbox_offset_y;
                inimigos_fase2[i].direcao_y = 1;
            }

            if (hitbox_bottom > ALTURA_TELA)
            {
                inimigos_fase2[i].y = ALTURA_TELA - inimigos_fase2[i].hitbox_altura - inimigos_fase2[i].hitbox_offset_y;
                inimigos_fase2[i].direcao_y = -1;
            }

            if (inimigos_fase2[i].x < -inimigos_fase2[i].largura)
            {
                inimigos_fase2[i].ativo = 0;
            }

            if (tempo_atual - ultimo_disparo_inimigo_fase2[i] > intervalo_disparo_inimigo_fase2)
            {
                for (int j = 0; j < MAX_PROJETEIS_INIMIGOS_FASE2; j++)
                {
                    if (!projeteis_fase2[j].ativo)
                    {
                        projeteis_fase2[j].x = inimigos_fase2[i].x;
                        projeteis_fase2[j].y = inimigos_fase2[i].y + inimigos_fase2[i].altura / 2;
                        projeteis_fase2[j].ativo = 1;
                        projeteis_fase2[j].largura = 10;
                        projeteis_fase2[j].altura = 10;
                        projeteis_fase2[j].dx = especial3_ativo ? -PROJETIL_LENTO : -VELOCIDADE_PROJETIL_INIMIGO_FASE2;
                        projeteis_fase2[j].tipo = inimigos_fase2[i].tipo;
                        break;
                    }
                }
                ultimo_disparo_inimigo_fase2[i] = tempo_atual;
            }
        }
    }
}

void desenhar_inimigos_fase2(InimigoFase2 inimigos_fase2[], ALLEGRO_BITMAP *sprite_inimigo_fase2_1, ALLEGRO_BITMAP *sprite_inimigo_fase2_2)
{
    for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
    {
        if (inimigos_fase2[i].ativo)
        {

            ALLEGRO_BITMAP *sprite = (inimigos_fase2[i].tipo == 0) ? sprite_inimigo_fase2_1 : sprite_inimigo_fase2_2;

            al_draw_bitmap(sprite, inimigos_fase2[i].x, inimigos_fase2[i].y, 0);

            // al_draw_rectangle(
            //     inimigos_fase2[i].x + inimigos_fase2[i].hitbox_offset_x,                    
            //     inimigos_fase2[i].y + inimigos_fase2[i].hitbox_offset_y,                    
            //     inimigos_fase2[i].x + inimigos_fase2[i].hitbox_offset_x + inimigos_fase2[i].hitbox_largura, 
            //     inimigos_fase2[i].y + inimigos_fase2[i].hitbox_offset_y + inimigos_fase2[i].hitbox_altura,  
            //     al_map_rgb(255, 0, 0), 2 
            // );
        }
    }
}

void gerar_novos_inimigos_fase2(InimigoFase2 inimigos_fase2[], NaveJogador *nave, ALLEGRO_BITMAP *sprite_inimigo1_fase2, ALLEGRO_BITMAP *sprite_inimigo2_fase2, int chefe_ativo)
{
    if (!chefe_ativo && rand() % 57 == 0)
    {
        for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
        {
            if (!inimigos_fase2[i].ativo)
            {
                int seguro = 0;

                while (!seguro)
                {
                    inimigos_fase2[i].x = LARGURA_TELA;
                    inimigos_fase2[i].y = rand() % (ALTURA_TELA - 40);

                    float distancia_x = inimigos_fase2[i].x - nave->x;
                    float distancia_y = inimigos_fase2[i].y - nave->y;
                    float distancia = sqrt(distancia_x * distancia_x + distancia_y * distancia_y);

                    if (distancia >= DISTANCIA_SEGURA)
                    {
                        seguro = 1;
                    }
                }

                inimigos_fase2[i].largura = 40;
                inimigos_fase2[i].altura = 40;
                inimigos_fase2[i].direcao_y = (rand() % 2) ? 1 : -1;
                inimigos_fase2[i].tipo = rand() % 2;
                inimigos_fase2[i].sprite = (inimigos_fase2[i].tipo == 0) ? sprite_inimigo1_fase2 : sprite_inimigo2_fase2;
                inimigos_fase2[i].ativo = 1;
                ultimo_disparo_inimigo_fase2[i] = al_get_time();
                break;
            }
        }
    }
}
