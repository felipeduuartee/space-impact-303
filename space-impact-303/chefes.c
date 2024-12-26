#include "chefes.h"
#include "projeteis.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <math.h>

#define VELOCIDADE_CHEFE_INICIAL 2.0
#define MAX_LASER_BOSS 1 // Máximo de lasers ativos do chefe
#define LARGURA_TELA 800 // Ajuste para a largura da sua tela
#define ALTURA_TELA 600  // Ajuste para a altura da sua tela

#define VELOCIDADE_PROJETIL_LASER 7.0    // Velocidade do laser
#define VELOCIDADE_PROJETIL_RICOCHETE 5.0 // Velocidade do projétil ricochete

int VELOCIDADE_CHEFE = 2;



void inicializar_chefe(Chefe *chefe)
{
    chefe->x = LARGURA_TELA; // Começa fora da tela à direita
    chefe->y = 100;          // Posição vertical inicial
    chefe->largura = 128;    // Largura da sprite do chefe (de acordo com a imagem)
    chefe->altura = 128;     // Altura da sprite do chefe (de acordo com a imagem)
    chefe->vidas = 15;       // Define a vida do chefe
    chefe->ativo = 1;        // Chefe está ativo
    chefe->velocidade_y = 1;
    chefe->sprite = al_load_bitmap("./imagens/boss1.png");

    chefe->entrando = 1;      // Novo estado para controlar a entrada do chefe
    chefe->velocidade_x = -3; // Velocidade de entrada para a esquerda


    chefe->hitbox_offset_x = 20;                 // Ajuste a posição da hitbox em relação à largura da sprite
    chefe->hitbox_offset_y = 20;                 // Ajuste a posição da hitbox em relação à altura da sprite
    chefe->hitbox_largura = chefe->largura - 40; // Hitbox menor que a sprite para ficar mais justa
    chefe->hitbox_altura = chefe->altura - 40;   // Hitbox menor que a sprite para ficar mais justa

    chefe->tempo_invulneravel = 0;
    chefe->invulneravel = 0;


    chefe->tempo_laser = al_get_time() - PAUSA_LASER;
}


void atualizar_chefe(Chefe *chefe, ProjetilBoss projeteis_chefe[], ALLEGRO_BITMAP *sprite_laser)
{
    if (!chefe->ativo)
        return;


    if (chefe->entrando)
    {
        chefe->x += chefe->velocidade_x;


        if (chefe->x <= LARGURA_TELA - chefe->largura - 50)
        {
            chefe->x = LARGURA_TELA - chefe->largura - 50;
            chefe->entrando = 0;
        }
    }
    else
    {

        chefe->y += chefe->velocidade_y;

        if (chefe->y >= ALTURA_TELA - chefe->altura)
        {
            chefe->y = ALTURA_TELA - chefe->altura;
            chefe->velocidade_y = -chefe->velocidade_y;
        }
        else if (chefe->y <= 0)
        {
            chefe->y = 0;
            chefe->velocidade_y = -chefe->velocidade_y;
        }


        double tempo_atual = al_get_time();


        if (tempo_atual - chefe->tempo_laser >= PAUSA_LASER)
        {

            disparar_laser_boss1(projeteis_chefe, chefe->x, chefe->y + chefe->altura / 2, sprite_laser);
            chefe->tempo_laser = tempo_atual; // Atualiza o tempo do último disparo
        }
    }
}


void desenhar_chefe(Chefe *chefe)
{
    if (chefe->ativo)
    {
        if (chefe->invulneravel)
        {

            if ((int)(al_get_time() * 10) % 2 == 0)
            {
                al_draw_bitmap(chefe->sprite, chefe->x, chefe->y, 0);
            }

            if (al_get_time() - chefe->tempo_invulneravel > 1.0)
            {
                chefe->invulneravel = 0; // Termina a invulnerabilidade
            }
        }
        else
        {
            al_draw_bitmap(chefe->sprite, chefe->x, chefe->y, 0);
        }


        // al_draw_rectangle(
        //     chefe->x + chefe->hitbox_offset_x,                         // Posição X da hitbox
        //     chefe->y + chefe->hitbox_offset_y,                         // Posição Y da hitbox
        //     chefe->x + chefe->hitbox_offset_x + chefe->hitbox_largura, // Largura da hitbox
        //     chefe->y + chefe->hitbox_offset_y + chefe->hitbox_altura,  // Altura da hitbox
        //     al_map_rgb(255, 0, 0), 2                                   // Cor vermelha com espessura da linha 2
        // );
    }
}

void disparar_laser_boss1(ProjetilBoss projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite)
{
    for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
    {
        if (!projeteis_chefe[i].ativo)
        {
            projeteis_chefe[i].x = x - 20;
            projeteis_chefe[i].y = y;
            projeteis_chefe[i].largura = al_get_bitmap_width(sprite);
            projeteis_chefe[i].altura = al_get_bitmap_height(sprite);
            projeteis_chefe[i].ativo = 1;
            projeteis_chefe[i].dx = -VELOCIDADE_PROJETIL_LASER; 
            projeteis_chefe[i].sprite = sprite;


            projeteis_chefe[i].hitbox_offset_x = 0;
            projeteis_chefe[i].hitbox_offset_y = 0;
            projeteis_chefe[i].hitbox_largura = 34;
            projeteis_chefe[i].hitbox_altura = 9;

            break;
        }
    }
}

void disparar_projetil_ricochete(Chefe *chefe, ProjetilBoss projeteis_ricochete[], ALLEGRO_BITMAP *sprite)
{

    if (!chefe->ativo) return;

    if (!sprite)
    {
        printf("Erro: sprite de ricochete não foi carregada corretamente.\n");
        return;
    }

    int projeteis_disparados = 0;


    for (int i = 0; i < MAX_PROJETEIS_RICOCHETE && projeteis_disparados < 2; i++)
    {
        if (!projeteis_ricochete[i].ativo)
        {
            projeteis_ricochete[i].sprite = sprite;


            projeteis_ricochete[i].x = chefe->x;
            projeteis_ricochete[i].y = chefe->y + chefe->altura / 2;
            projeteis_ricochete[i].largura = al_get_bitmap_width(sprite);
            projeteis_ricochete[i].altura = al_get_bitmap_height(sprite);
            projeteis_ricochete[i].ativo = 1;
            projeteis_ricochete[i].dx = -VELOCIDADE_PROJETIL_RICOCHETE; //esquerda


            if (projeteis_disparados == 0)
                projeteis_ricochete[i].dy = -VELOCIDADE_PROJETIL_RICOCHETE / 2; //cima
            else
                projeteis_ricochete[i].dy = VELOCIDADE_PROJETIL_RICOCHETE / 2; //  baixo


            projeteis_ricochete[i].hitbox_offset_x = projeteis_ricochete[i].largura / 4;
            projeteis_ricochete[i].hitbox_offset_y = projeteis_ricochete[i].altura / 4;
            projeteis_ricochete[i].hitbox_largura = projeteis_ricochete[i].largura / 2;
            projeteis_ricochete[i].hitbox_altura = projeteis_ricochete[i].altura / 2;


            projeteis_disparados++;
        }
    }
}


void inicializar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[])
{
    for (int i = 0; i < MAX_PROJETEIS_RICOCHETE; i++)
    {
        projeteis_ricochete[i].ativo = 0;
        projeteis_ricochete[i].sprite = NULL;


        projeteis_ricochete[i].hitbox_offset_x = 0;
        projeteis_ricochete[i].hitbox_offset_y = 0;
        projeteis_ricochete[i].hitbox_largura = 10;
        projeteis_ricochete[i].hitbox_altura = 10;
    }
}

void atualizar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[])
{
    for (int i = 0; i < MAX_PROJETEIS_RICOCHETE; i++)
    {
        if (projeteis_ricochete[i].ativo)
        {

            projeteis_ricochete[i].x += projeteis_ricochete[i].dx;
            projeteis_ricochete[i].y += projeteis_ricochete[i].dy;


            if (projeteis_ricochete[i].y <= 0 ||
                projeteis_ricochete[i].y + projeteis_ricochete[i].altura >= ALTURA_TELA)
            {

                projeteis_ricochete[i].dy = -projeteis_ricochete[i].dy;
            }


            if (projeteis_ricochete[i].x + projeteis_ricochete[i].largura < 0)
            {
                projeteis_ricochete[i].ativo = 0; // Desativa o projétil quando sair da tela
            }
        }
    }
}

void desenhar_projeteis_ricochete(ProjetilBoss projeteis_ricochete[])
{
    for (int i = 0; i < MAX_PROJETEIS_RICOCHETE; i++)
    {
        if (projeteis_ricochete[i].ativo)
        {
            if (projeteis_ricochete[i].sprite)
            {
                al_draw_bitmap(projeteis_ricochete[i].sprite, projeteis_ricochete[i].x, projeteis_ricochete[i].y, 0);


                // al_draw_rectangle(
                //     projeteis_ricochete[i].x + projeteis_ricochete[i].hitbox_offset_x,
                //     projeteis_ricochete[i].y + projeteis_ricochete[i].hitbox_offset_y,
                //     projeteis_ricochete[i].x + projeteis_ricochete[i].hitbox_offset_x + projeteis_ricochete[i].hitbox_largura,
                //     projeteis_ricochete[i].y + projeteis_ricochete[i].hitbox_offset_y + projeteis_ricochete[i].hitbox_altura,
                //     al_map_rgb(255, 0, 0), 2);
            }
        }
    }
}

void reduzir_hp_chefe(Chefe *chefe, int dano)
{
    chefe->vidas -= dano;
    if (chefe->vidas <= 0)
    {
        chefe->ativo = 0;
    }
}



void inicializar_chefe_fase2(ChefeFase2 *chefe)
{
    chefe->x = LARGURA_TELA; // Começa fora da tela à direita
    chefe->y = 100;          // Posição vertical inicial
    chefe->largura = 128;    // Largura do sprite do chefe (de acordo com a imagem)
    chefe->altura = 128;     // Altura do sprite do chefe (de acordo com a imagem)
    chefe->vidas = 20;       // Define a vida do chefe
    chefe->ativo = 1;        // Chefe está ativo
    chefe->velocidade_y = 1;
    chefe->sprite = al_load_bitmap("./imagens/boss2.png");

    chefe->entrando = 1;      // Estado para controlar a entrada do chefe
    chefe->velocidade_x = -3; // Velocidade de entrada para a esquerda


    chefe->hitbox_offset_x = 20;
    chefe->hitbox_offset_y = 20;
    chefe->hitbox_largura = chefe->largura - 40;
    chefe->hitbox_altura = chefe->altura - 40;

    chefe->tempo_invulneravel = 0;
    chefe->invulneravel = 0;


    chefe->tempo_laser = al_get_time() - PAUSA_LASER_FASE2;
    chefe->tempo_projetil_circular = al_get_time() - INTERVALO_DISPARO_CIRCULAR;
}

void atualizar_chefe_fase2(ChefeFase2 *chefe, ProjetilBossFase2 projeteis_chefe[], ALLEGRO_BITMAP *sprite_laser, ALLEGRO_BITMAP *sprite_projetil_circular)
{
    if (!chefe->ativo)
        return;


    if (chefe->entrando)
    {
        chefe->x += chefe->velocidade_x;


        if (chefe->x <= LARGURA_TELA - chefe->largura - 50)
        {
            chefe->x = LARGURA_TELA - chefe->largura - 50;
            chefe->entrando = 0;
        }
    }
    else
    {

        chefe->y += chefe->velocidade_y;

        if (chefe->y >= ALTURA_TELA - chefe->altura)
        {
            chefe->y = ALTURA_TELA - chefe->altura;
            chefe->velocidade_y = -chefe->velocidade_y;
        }
        else if (chefe->y <= 0)
        {
            chefe->y = 0;
            chefe->velocidade_y = -chefe->velocidade_y;
        }

        double tempo_atual = al_get_time();


        if (tempo_atual - chefe->tempo_laser >= PAUSA_LASER_FASE2)
        {

            int laser_ativo = 0;
            for (int i = 0; i < MAX_PROJETEIS_BOSS_FASE2; i++)
            {
                if (projeteis_chefe[i].ativo && projeteis_chefe[i].tipo == TIPO_PROJETIL_LASER)
                {
                    laser_ativo = 1;
                    break;
                }
            }


            if (!laser_ativo)
            {

                disparar_laser_fase2(projeteis_chefe, chefe->x, chefe->y + chefe->altura / 2, sprite_laser);
                chefe->tempo_laser = tempo_atual; // Atualiza o tempo do último disparo do laser
            }
        }


        if (tempo_atual - chefe->tempo_projetil_circular >= INTERVALO_DISPARO_CIRCULAR)
        {

            int projeteis_circulares_ativos = 0;
            for (int i = 0; i < MAX_PROJETEIS_BOSS_FASE2; i++)
            {
                if (projeteis_chefe[i].ativo && projeteis_chefe[i].tipo == TIPO_PROJETIL_CIRCULAR)
                {
                    projeteis_circulares_ativos = 1;
                    break;
                }
            }


            if (!projeteis_circulares_ativos)
            {

                disparar_projetil_circular(projeteis_chefe, MAX_PROJETEIS_BOSS_FASE2, chefe->x + chefe->largura / 2, chefe->y + chefe->altura / 2, VELOCIDADE_PROJETIL_CIRCULAR, sprite_projetil_circular);
                chefe->tempo_projetil_circular = tempo_atual; // Atualiza o tempo do último disparo circular
            }
        }
    }
}


void desenhar_chefe_fase2(ChefeFase2 *chefe)
{
    if (chefe->ativo)
    {
        if (chefe->invulneravel)
        {

            if ((int)(al_get_time() * 10) % 2 == 0)
            {
                al_draw_bitmap(chefe->sprite, chefe->x, chefe->y, 0);
            }

            if (al_get_time() - chefe->tempo_invulneravel > 1.0)
            {
                chefe->invulneravel = 0; // Termina a invulnerabilidade
            }
        }
        else
        {
            al_draw_bitmap(chefe->sprite, chefe->x, chefe->y, 0);
        }


        // al_draw_rectangle(
        //     chefe->x + chefe->hitbox_offset_x,                         // Posição X da hitbox
        //     chefe->y + chefe->hitbox_offset_y,                         // Posição Y da hitbox
        //     chefe->x + chefe->hitbox_offset_x + chefe->hitbox_largura, // Posição final X da hitbox
        //     chefe->y + chefe->hitbox_offset_y + chefe->hitbox_altura,  // Posição final Y da hitbox
        //     al_map_rgb(255, 0, 0), 2                                   // Cor vermelha com espessura da linha 2
        // );
    }
}

void disparar_laser_fase2(ProjetilBossFase2 projeteis_chefe[], float x, float y, ALLEGRO_BITMAP *sprite)
{
    if (!sprite)
    {
        fprintf(stderr, "Erro: sprite do laser é NULL.\n");
        return;
    }

    for (int i = 0; i < MAX_PROJETEIS_BOSS_FASE2; i++)
    {
        if (!projeteis_chefe[i].ativo)
        {

            projeteis_chefe[i].x = x - 20;
            projeteis_chefe[i].y = y - al_get_bitmap_height(sprite) / 2;
            projeteis_chefe[i].largura = al_get_bitmap_width(sprite);
            projeteis_chefe[i].altura = al_get_bitmap_height(sprite);
            projeteis_chefe[i].ativo = 1;
            projeteis_chefe[i].dx = -VELOCIDADE_LASER_CHEFE2;
            projeteis_chefe[i].dy = 0;
            projeteis_chefe[i].sprite = sprite;
            projeteis_chefe[i].tipo = TIPO_PROJETIL_LASER;


            projeteis_chefe[i].hitbox_offset_x = 0;
            projeteis_chefe[i].hitbox_offset_y = 0;
            projeteis_chefe[i].hitbox_largura = projeteis_chefe[i].largura;
            projeteis_chefe[i].hitbox_altura = projeteis_chefe[i].altura;

            break;
        }
    }
}
