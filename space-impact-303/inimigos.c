#include "inimigos.h"
#include "projeteis.h"
#include <allegro5/allegro.h>
#include <stdlib.h>
#include <stdlib.h> 
#include <math.h>   

static double ultimo_disparo_inimigo[MAX_INIMIGOS]; 
static double intervalo_disparo_inimigo = 2.0;      


void inicializar_inimigos(Inimigo inimigos[])
{
    int posicao_inicial_x = LARGURA_TELA + 100;
    int margem_superior = 50;

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigos[i].ativo = 1;
        inimigos[i].x = posicao_inicial_x + (rand() % 200);
        inimigos[i].y = margem_superior + (rand() % (ALTURA_TELA - 2 * margem_superior));
        inimigos[i].largura = 64;  
        inimigos[i].altura = 64;   


        inimigos[i].hitbox_largura = inimigos[i].largura - 16; 
        inimigos[i].hitbox_altura = inimigos[i].altura - 16;   

        inimigos[i].hitbox_offset_x = 8;  
        inimigos[i].hitbox_offset_y = 8;  

        inimigos[i].direcao_y = (rand() % 2) ? 1 : -1;
        inimigos[i].tipo = i % 2;
        inimigos[i].sprite = (inimigos[i].tipo == 0) ? al_load_bitmap("enemy.png") : al_load_bitmap("enemy2.png");
    }
}


void atualizar_inimigos(Inimigo inimigos[], ProjetilInimigo projeteis[])
{
    double tempo_atual = al_get_time();

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        if (inimigos[i].ativo)
        {

            inimigos[i].x -= VELOCIDADE_INIMIGO;


            inimigos[i].y += inimigos[i].direcao_y * 2;


            int hitbox_top = inimigos[i].y + inimigos[i].hitbox_offset_y;
            int hitbox_bottom = hitbox_top + inimigos[i].hitbox_altura;

            if (hitbox_top < 0)
            {
                inimigos[i].y = -inimigos[i].hitbox_offset_y;
                inimigos[i].direcao_y = 1;
            }

            if (hitbox_bottom > ALTURA_TELA)
            {
                inimigos[i].y = ALTURA_TELA - inimigos[i].hitbox_altura - inimigos[i].hitbox_offset_y;
                inimigos[i].direcao_y = -1;
            }


            if (inimigos[i].x < -inimigos[i].largura)
            {
                inimigos[i].ativo = 0;
            }


            if (tempo_atual - ultimo_disparo_inimigo[i] > intervalo_disparo_inimigo)
            {
                for (int j = 0; j < MAX_PROJETEIS_INIMIGOS; j++)
                {
                    if (!projeteis[j].ativo)
                    {
                        projeteis[j].x = inimigos[i].x;
                        projeteis[j].y = inimigos[i].y + inimigos[i].altura / 2;
                        projeteis[j].ativo = 1;
                        projeteis[j].largura = 10;
                        projeteis[j].altura = 10;
                        projeteis[j].dx = -VELOCIDADE_PROJETIL_INIMIGO; 
                        projeteis[j].tipo = inimigos[i].tipo;
                        break;
                    }
                }
                ultimo_disparo_inimigo[i] = tempo_atual;
            }
        }
    }
}


void desenhar_inimigos(Inimigo inimigos[], ALLEGRO_BITMAP *sprite_inimigo1, ALLEGRO_BITMAP *sprite_inimigo2)
{
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        if (inimigos[i].ativo)
        {

            ALLEGRO_BITMAP *sprite = (inimigos[i].tipo == 0) ? sprite_inimigo1 : sprite_inimigo2;


            al_draw_bitmap(sprite, inimigos[i].x, inimigos[i].y, 0);


            // al_draw_rectangle(
            //     inimigos[i].x + inimigos[i].hitbox_offset_x,                        
            //     inimigos[i].y + inimigos[i].hitbox_offset_y,                        
            //     inimigos[i].x + inimigos[i].hitbox_offset_x + inimigos[i].hitbox_largura, 
            //     inimigos[i].y + inimigos[i].hitbox_offset_y + inimigos[i].hitbox_altura,  
            //     al_map_rgb(255, 0, 0), 2
            // );
        }
    }
}


void gerar_novos_inimigos(Inimigo inimigos[], NaveJogador *nave, ALLEGRO_BITMAP *sprite_inimigo1, ALLEGRO_BITMAP *sprite_inimigo2, int chefe_ativo)
{
    if (!chefe_ativo && rand() % 60 == 0) 
    {
        for (int i = 0; i < MAX_INIMIGOS; i++)
        {
            if (!inimigos[i].ativo)
            {
                int seguro = 0;


                while (!seguro)
                {
                    inimigos[i].x = LARGURA_TELA; 
                    inimigos[i].y = rand() % (ALTURA_TELA - 40);


                    float distancia_x = inimigos[i].x - nave->x;
                    float distancia_y = inimigos[i].y - nave->y;
                    float distancia = sqrt(distancia_x * distancia_x + distancia_y * distancia_y);


                    if (distancia >= DISTANCIA_SEGURA)
                    {
                        seguro = 1;
                    }
                }


                inimigos[i].largura = 40;
                inimigos[i].altura = 40;
                inimigos[i].direcao_y = (rand() % 2) ? 1 : -1;
                inimigos[i].tipo = rand() % 2;
                inimigos[i].sprite = (inimigos[i].tipo == 0) ? sprite_inimigo1 : sprite_inimigo2;
                inimigos[i].ativo = 1;
                ultimo_disparo_inimigo[i] = al_get_time();
                break;
            }
        }
    }
}
