#include "colisoes.h"
#include <allegro5/allegro.h>

static int colisao_retangular(float x1, float y1, int hitbox_offset_x1, int hitbox_offset_y1, int hitbox_largura1, int hitbox_altura1,
                              float x2, float y2, int hitbox_offset_x2, int hitbox_offset_y2, int hitbox_largura2, int hitbox_altura2)
{
    return (x1 + hitbox_offset_x1 < x2 + hitbox_offset_x2 + hitbox_largura2 &&
            x1 + hitbox_offset_x1 + hitbox_largura1 > x2 + hitbox_offset_x2 &&
            y1 + hitbox_offset_y1 < y2 + hitbox_offset_y2 + hitbox_altura2 &&
            y1 + hitbox_offset_y1 + hitbox_altura1 > y2 + hitbox_offset_y2);
}

static int colisao_retangular_item(float x1, float y1, float largura1, float altura1,
                                   float x2, float y2, float largura2, float altura2,
                                   int offset_x, int offset_y)
{
    return (x1 < x2 + largura2 + offset_x && x1 + largura1 > x2 + offset_x &&
            y1 < y2 + altura2 + offset_y && y1 + altura1 > y2 + offset_y);
}

static int colisao_circulo_retangulo(float cx, float cy, float cr,
                                     float rx, float ry, float rw, float rh)
{
    float closestX = fmaxf(rx, fminf(cx, rx + rw));
    float closestY = fmaxf(ry, fminf(cy, ry + rh));

    float distanceX = cx - closestX;
    float distanceY = cy - closestY;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (cr * cr);
}

void detectar_colisao_projeteis_inimigos(Projetil projeteis[], Inimigo inimigos[], int *pontuacao, ItemDrop *item, int *inimigos_derrotados)
{
    static int item_foi_dropado = 0;

    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo)
        {
            for (int j = 0; j < MAX_INIMIGOS; j++)
            {
                if (inimigos[j].ativo && colisao_retangular(
                                             projeteis[i].x, projeteis[i].y,
                                             0, 0, projeteis[i].largura, projeteis[i].altura, // Hitbox do projétil sem offset
                                             inimigos[j].x, inimigos[j].y,
                                             inimigos[j].hitbox_offset_x, inimigos[j].hitbox_offset_y, // Offset da hitbox do inimigo
                                             inimigos[j].hitbox_largura, inimigos[j].hitbox_altura))   // Hitbox ajustada do inimigo
                {

                    projeteis[i].ativo = 0;
                    inimigos[j].ativo = 0;

                    (*pontuacao) += 10;

                    (*inimigos_derrotados)++;

                    if (*inimigos_derrotados >= 18 && !item_foi_dropado)
                    {
                        item->x = inimigos[j].x;
                        item->y = inimigos[j].y;
                        item->ativo = 1;
                        item->tempo_ativacao = al_get_time();
                        item_foi_dropado = 1;
                    }
                }
            }
        }
    }
}

void detectar_colisao_nave_inimigos(NaveJogador *nave, Inimigo inimigos[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados)
{

    if (nave->invulneravel)
        return;

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        if (inimigos[i].ativo && colisao_retangular(
                                     nave->x, nave->y,
                                     nave->hitbox_offset_x, nave->hitbox_offset_y, // Offset da hitbox da nave
                                     nave->hitbox_largura, nave->hitbox_altura,    // Hitbox ajustada da nave
                                     inimigos[i].x, inimigos[i].y,
                                     inimigos[i].hitbox_offset_x, inimigos[i].hitbox_offset_y, // Offset da hitbox do inimigo
                                     inimigos[i].hitbox_largura, inimigos[i].hitbox_altura))   // Hitbox ajustada do inimigo
        {

            nave->vidas--;
            inimigos[i].ativo = 0;

            if (nave->vidas > 0)
            {
                nave->invulneravel = 1;
                nave->tempo_invulneravel = al_get_time();
            }

            if (nave->vidas <= 0)
            {
                nave->vidas = 0;
                tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                exit(0);
            }
        }
    }
}

void detectar_colisao_nave_item(NaveJogador *nave, ItemDrop *item)
{
    if (item->ativo && colisao_retangular_item(
                           nave->x, nave->y, nave->hitbox_largura, nave->hitbox_altura,
                           item->x + item->hitbox_offset_x, item->y, item->largura, item->altura, 0, 0))
    {

        item->ativo = 0;
        nave->especial_coletado = 1;
    }
}

void detectar_colisao_projeteis_nave(NaveJogador *nave, ProjetilInimigo projeteis_inimigos[], ProjetilBoss projeteis_boss[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados)
{

    if (nave->invulneravel)
        return;

    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        if (nave->invulneravel)
        {
            break;
        }

        if (projeteis_inimigos[i].ativo && colisao_retangular(
                                               nave->x, nave->y,
                                               nave->hitbox_offset_x, nave->hitbox_offset_y, // Offset da nave
                                               nave->hitbox_largura, nave->hitbox_altura,    // Largura e altura da hitbox ajustada da nave
                                               projeteis_inimigos[i].x, projeteis_inimigos[i].y,
                                               projeteis_inimigos[i].hitbox_offset_x, projeteis_inimigos[i].hitbox_offset_y, // Offset do projétil inimigo
                                               projeteis_inimigos[i].largura, projeteis_inimigos[i].altura))                 // Largura e altura da hitbox ajustada do projétil inimigo
        {
            projeteis_inimigos[i].ativo = 0;
            nave->vidas--;

            if (nave->vidas <= 0)
            {
                nave->vidas = 0;
                tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                exit(0);
            }

            nave->invulneravel = 1;
            nave->tempo_invulneravel = al_get_time();
            break;
        }
    }

    if (projeteis_boss != NULL)
    {
        for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
        {
            if (nave->invulneravel)
            {
                break;
            }

            if (projeteis_boss[i].ativo && colisao_retangular(
                                               nave->x, nave->y,
                                               nave->hitbox_offset_x, nave->hitbox_offset_y, // Offset da nave
                                               nave->hitbox_largura, nave->hitbox_altura,    // Largura e altura da hitbox ajustada da nave
                                               projeteis_boss[i].x, projeteis_boss[i].y,
                                               projeteis_boss[i].hitbox_offset_x, projeteis_boss[i].hitbox_offset_y, // Offset do projétil do chefe
                                               projeteis_boss[i].largura, projeteis_boss[i].altura))                 // Largura e altura da hitbox ajustada do projétil do chefe
            {
                projeteis_boss[i].ativo = 0;
                nave->vidas--;

                if (nave->vidas <= 0)
                {
                    nave->vidas = 0;
                    tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                    exit(0);
                }

                nave->invulneravel = 1;
                nave->tempo_invulneravel = al_get_time();
                break;
            }
        }
    }
}

void detectar_colisao_projeteis_chefe(Chefe *chefe, Projetil projeteis[], int *pontuacao, int *chefe_derrotado, double *tempo_chefe_derrotado)
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo && chefe->ativo)
        {
            if (colisao_retangular(
                    projeteis[i].x, projeteis[i].y,
                    0, 0,
                    projeteis[i].largura, projeteis[i].altura,

                    chefe->x, chefe->y,
                    chefe->hitbox_offset_x, chefe->hitbox_offset_y,
                    chefe->hitbox_largura, chefe->hitbox_altura))
            {
                projeteis[i].ativo = 0;
                chefe->vidas--;
                (*pontuacao) += 100;

                if (chefe->vidas <= 0)
                {
                    chefe->vidas = 0;
                    chefe->ativo = 0;
                    (*pontuacao) += 1000;

                    *chefe_derrotado = 1;
                    *tempo_chefe_derrotado = al_get_time();
                }
                else
                {
                    chefe->invulneravel = 1;
                    chefe->tempo_invulneravel = al_get_time();
                }
            }
        }
    }
}

void detectar_colisao_nave_chefe(NaveJogador *nave, Chefe *chefe, int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    if (chefe->ativo && colisao_retangular(
                            nave->x, nave->y,
                            nave->hitbox_offset_x, nave->hitbox_offset_y,
                            nave->hitbox_largura, nave->hitbox_altura,

                            chefe->x, chefe->y,
                            chefe->hitbox_offset_x, chefe->hitbox_offset_y,
                            chefe->hitbox_largura, chefe->hitbox_altura))
    {
        nave->vidas--;

        if (nave->vidas <= 0)
        {
            nave->vidas = 0;
            tela_game_over(pontuacao, inimigos_derrotados_total, fonte, fila_eventos, background);
            exit(0);
        }

        nave->invulneravel = 1;
        nave->tempo_invulneravel = al_get_time();
    }
}

void detectar_colisao_escudo(NaveJogador *nave,
                             ProjetilInimigo projeteis_inimigos_fase2[],
                             InimigoFase2 inimigos_fase2[])
{
    float centro_escudo_x = nave->x + nave->largura / 2;
    float centro_escudo_y = nave->y + nave->altura / 2;
    float raio_escudo = 40.0; 

    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        if (projeteis_inimigos_fase2[i].ativo)
        {
            float distancia_x = projeteis_inimigos_fase2[i].x - centro_escudo_x;
            float distancia_y = projeteis_inimigos_fase2[i].y - centro_escudo_y;
            float distancia = sqrt(distancia_x * distancia_x + distancia_y * distancia_y);

            if (distancia <= raio_escudo)
            {
                projeteis_inimigos_fase2[i].ativo = 0; 
            }
        }
    }

    for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
    {
        if (inimigos_fase2[i].ativo)
        {
            float distancias[8];                                                                                                                                                            
            distancias[0] = sqrt(pow(inimigos_fase2[i].x - centro_escudo_x, 2) + pow(inimigos_fase2[i].y - centro_escudo_y, 2));                                                            
            distancias[1] = sqrt(pow((inimigos_fase2[i].x + inimigos_fase2[i].largura) - centro_escudo_x, 2) + pow(inimigos_fase2[i].y - centro_escudo_y, 2));                              
            distancias[2] = sqrt(pow(inimigos_fase2[i].x - centro_escudo_x, 2) + pow((inimigos_fase2[i].y + inimigos_fase2[i].altura) - centro_escudo_y, 2));                               
            distancias[3] = sqrt(pow((inimigos_fase2[i].x + inimigos_fase2[i].largura) - centro_escudo_x, 2) + pow((inimigos_fase2[i].y + inimigos_fase2[i].altura) - centro_escudo_y, 2)); 

            distancias[4] = sqrt(pow((inimigos_fase2[i].x + inimigos_fase2[i].largura / 2) - centro_escudo_x, 2) + pow(inimigos_fase2[i].y - centro_escudo_y, 2));                              
            distancias[5] = sqrt(pow((inimigos_fase2[i].x + inimigos_fase2[i].largura / 2) - centro_escudo_x, 2) + pow((inimigos_fase2[i].y + inimigos_fase2[i].altura) - centro_escudo_y, 2)); 
            distancias[6] = sqrt(pow(inimigos_fase2[i].x - centro_escudo_x, 2) + pow((inimigos_fase2[i].y + inimigos_fase2[i].altura / 2) - centro_escudo_y, 2));                               
            distancias[7] = sqrt(pow((inimigos_fase2[i].x + inimigos_fase2[i].largura) - centro_escudo_x, 2) + pow((inimigos_fase2[i].y + inimigos_fase2[i].altura / 2) - centro_escudo_y, 2)); 
            for (int j = 0; j < 8; j++)
            {
                if (distancias[j] <= raio_escudo)
                {
                    inimigos_fase2[i].ativo = 0; 
                    break;                       
                }
            }
        }
    }
}

void detectar_colisao_projeteis_ricochete_nave(NaveJogador *nave, ProjetilBoss projeteis_ricochete[], ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, int pontuacao, int inimigos_derrotados)
{
    for (int i = 0; i < MAX_PROJETEIS_RICOCHETE; i++)
    {
        if (nave->invulneravel)
        {
            break;
        }

        if (projeteis_ricochete[i].ativo && colisao_retangular(
                                                nave->x, nave->y,
                                                nave->hitbox_offset_x, nave->hitbox_offset_y, // Offset da nave
                                                nave->hitbox_largura, nave->hitbox_altura,    // Largura e altura da hitbox ajustada da nave
                                                projeteis_ricochete[i].x, projeteis_ricochete[i].y,
                                                projeteis_ricochete[i].hitbox_offset_x, projeteis_ricochete[i].hitbox_offset_y, // Offset do projétil ricochete
                                                projeteis_ricochete[i].hitbox_largura, projeteis_ricochete[i].hitbox_altura))   // Largura e altura da hitbox ajustada do projétil ricochete
        {
            projeteis_ricochete[i].ativo = 0;
            nave->vidas--;

            if (nave->vidas <= 0)
            {
                nave->vidas = 0;
                tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                exit(0);
            }

            nave->invulneravel = 1;
            nave->tempo_invulneravel = al_get_time();
            break;
        }
    }
}

void detectar_colisao_projeteis_inimigos_fase2(Projetil projeteis[], InimigoFase2 inimigos_fase2[], int *pontuacao, ItemDrop2 *item, ItemDrop3 *item3, int *inimigos_derrotados_fase2)
{
    static int item_foi_dropado_fase2 = 0;
    static int item3_foi_dropado_fase2 = 0;

    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo)
        {
            for (int j = 0; j < MAX_INIMIGOS_FASE2; j++)
            {
                if (inimigos_fase2[j].ativo && colisao_retangular(
                                                   projeteis[i].x, projeteis[i].y,
                                                   projeteis[i].hitbox_offset_x, projeteis[i].hitbox_offset_y,
                                                   projeteis[i].largura, projeteis[i].altura,
                                                   inimigos_fase2[j].x, inimigos_fase2[j].y,
                                                   inimigos_fase2[j].hitbox_offset_x, inimigos_fase2[j].hitbox_offset_y,
                                                   inimigos_fase2[j].hitbox_largura, inimigos_fase2[j].hitbox_altura))
                {

                    projeteis[i].ativo = 0;
                    inimigos_fase2[j].ativo = 0;

                    (*pontuacao) += 20;

                    (*inimigos_derrotados_fase2)++;

                    if (*inimigos_derrotados_fase2 >= 12 && !item3_foi_dropado_fase2)
                    {
                        item3->x = inimigos_fase2[j].x;
                        item3->y = inimigos_fase2[j].y;
                        item3->ativo = 1;
                        item3->tempo_ativacao = al_get_time();
                        item3_foi_dropado_fase2 = 1;
                    }

                    if (*inimigos_derrotados_fase2 >= 18 && !item_foi_dropado_fase2)
                    {
                        item->x = inimigos_fase2[j].x;
                        item->y = inimigos_fase2[j].y;
                        item->ativo = 1;
                        item->tempo_ativacao = al_get_time();
                        item_foi_dropado_fase2 = 1;
                    }
                }
            }
        }
    }
}

void detectar_colisao_nave_inimigos_fase2(NaveJogador *nave,
                                          InimigoFase2 inimigos_fase2[],
                                          int pontuacao, int inimigos_derrotados,
                                          ALLEGRO_FONT *fonte,
                                          ALLEGRO_BITMAP *background,
                                          ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    for (int i = 0; i < MAX_INIMIGOS_FASE2; i++)
    {
        if (inimigos_fase2[i].ativo)
        {
            int inimigo_destruido = 0;

            // Verifica colisão com o escudo
            if (nave->especial2_ativo)
            {
                float shield_cx = nave->x + nave->largura / 2;
                float shield_cy = nave->y + nave->altura / 2;
                float shield_radius = 40;

                float inimigo_x = inimigos_fase2[i].x + inimigos_fase2[i].hitbox_offset_x;
                float inimigo_y = inimigos_fase2[i].y + inimigos_fase2[i].hitbox_offset_y;
                float inimigo_w = inimigos_fase2[i].hitbox_largura;
                float inimigo_h = inimigos_fase2[i].hitbox_altura;

                if (colisao_circulo_retangulo(shield_cx, shield_cy, shield_radius,
                                              inimigo_x, inimigo_y, inimigo_w, inimigo_h))
                {
                    inimigos_fase2[i].ativo = 0;
                    inimigo_destruido = 1;
                    // Opcional: incrementar pontuação
                    continue; // Passa para o próximo inimigo
                }
            }

            // Verifica colisão com a nave se não estiver invulnerável
            if (!nave->invulneravel && !inimigo_destruido)
            {
                if (colisao_retangular(
                        nave->x, nave->y,
                        nave->hitbox_offset_x, nave->hitbox_offset_y,
                        nave->hitbox_largura, nave->hitbox_altura,
                        inimigos_fase2[i].x, inimigos_fase2[i].y,
                        inimigos_fase2[i].hitbox_offset_x, inimigos_fase2[i].hitbox_offset_y,
                        inimigos_fase2[i].hitbox_largura, inimigos_fase2[i].hitbox_altura))
                {
                    inimigos_fase2[i].ativo = 0;
                    nave->vidas--;

                    if (nave->vidas <= 0)
                    {
                        nave->vidas = 0;
                        tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                        exit(0);
                    }

                    nave->invulneravel = 1;
                    nave->tempo_invulneravel = al_get_time();
                    break;
                }
            }
        }
    }
}

void detectar_colisao_projeteis_inimigos_fase2_nave(NaveJogador *nave,
                                                    ProjetilInimigo projeteis_inimigos_fase2[],
                                                    int pontuacao, int inimigos_derrotados,
                                                    ALLEGRO_FONT *fonte,
                                                    ALLEGRO_BITMAP *background,
                                                    ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        if (projeteis_inimigos_fase2[i].ativo)
        {
            int projetil_destruido = 0;

            // Verifica colisão com o escudo
            if (nave->especial2_ativo)
            {
                float shield_cx = nave->x + nave->largura / 2;
                float shield_cy = nave->y + nave->altura / 2;
                float shield_radius = 40;

                float proj_x = projeteis_inimigos_fase2[i].x + projeteis_inimigos_fase2[i].hitbox_offset_x;
                float proj_y = projeteis_inimigos_fase2[i].y + projeteis_inimigos_fase2[i].hitbox_offset_y;
                float proj_w = projeteis_inimigos_fase2[i].hitbox_largura;
                float proj_h = projeteis_inimigos_fase2[i].hitbox_altura;

                if (colisao_circulo_retangulo(shield_cx, shield_cy, shield_radius,
                                              proj_x, proj_y, proj_w, proj_h))
                {
                    projeteis_inimigos_fase2[i].ativo = 0;
                    projetil_destruido = 1;
                    continue; // Passa para o próximo projetil
                }
            }

            // Verifica colisão com a nave se não estiver invulnerável
            if (!nave->invulneravel && !projetil_destruido)
            {
                if (colisao_retangular(
                        nave->x, nave->y,
                        nave->hitbox_offset_x, nave->hitbox_offset_y,
                        nave->hitbox_largura, nave->hitbox_altura,
                        projeteis_inimigos_fase2[i].x, projeteis_inimigos_fase2[i].y,
                        projeteis_inimigos_fase2[i].hitbox_offset_x, projeteis_inimigos_fase2[i].hitbox_offset_y,
                        projeteis_inimigos_fase2[i].hitbox_largura, projeteis_inimigos_fase2[i].hitbox_altura))
                {
                    projeteis_inimigos_fase2[i].ativo = 0;
                    nave->vidas--;

                    if (nave->vidas <= 0)
                    {
                        nave->vidas = 0;
                        tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                        exit(0);
                    }

                    nave->invulneravel = 1;
                    nave->tempo_invulneravel = al_get_time();
                    break;
                }
            }
        }
    }
}

void detectar_colisao_projeteis_chefe_fase2(ChefeFase2 *chefe_fase2, Projetil projeteis[], int *pontuacao, int *chefe_derrotado_fase2, double *tempo_chefe_derrotado_fase2)
{
    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        if (projeteis[i].ativo && chefe_fase2->ativo) // Verifica se o projétil e o chefe estão ativos
        {
            if (colisao_retangular(projeteis[i].x, projeteis[i].y,
                                   projeteis[i].hitbox_offset_x, projeteis[i].hitbox_offset_y,
                                   projeteis[i].largura, projeteis[i].altura,
                                   chefe_fase2->x, chefe_fase2->y,
                                   chefe_fase2->hitbox_offset_x, chefe_fase2->hitbox_offset_y,
                                   chefe_fase2->largura, chefe_fase2->altura))
            {
                projeteis[i].ativo = 0;
                chefe_fase2->vidas--;
                (*pontuacao) += 150;

                if (chefe_fase2->vidas <= 0)
                {
                    chefe_fase2->vidas = 0;
                    chefe_fase2->ativo = 0;
                    (*pontuacao) += 1500;

                    *chefe_derrotado_fase2 = 1;
                    *tempo_chefe_derrotado_fase2 = al_get_time();
                }
                else
                {
                    chefe_fase2->invulneravel = 1;
                    chefe_fase2->tempo_invulneravel = al_get_time();
                }
            }
        }
    }
}

void detectar_colisao_nave_chefe_fase2(NaveJogador *nave, ChefeFase2 *chefe_fase2, int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    if (chefe_fase2->ativo && colisao_retangular(
                                  nave->x, nave->y,
                                  nave->hitbox_offset_x, nave->hitbox_offset_y,
                                  nave->hitbox_largura, nave->hitbox_altura,
                                  chefe_fase2->x, chefe_fase2->y,
                                  chefe_fase2->hitbox_offset_x, chefe_fase2->hitbox_offset_y,
                                  chefe_fase2->hitbox_largura, chefe_fase2->hitbox_altura))
    {
        nave->vidas--;

        if (nave->vidas <= 0)
        {
            nave->vidas = 0;
            tela_game_over(pontuacao, inimigos_derrotados_total, fonte, fila_eventos, background);
            exit(0);
        }

        nave->invulneravel = 1;
        nave->tempo_invulneravel = al_get_time();
    }
}

void detectar_colisao_projeteis_chefe_fase2_nave(NaveJogador *nave,
                                                 ProjetilBossFase2 projeteis_chefe_fase2[],
                                                 ALLEGRO_FONT *fonte,
                                                 ALLEGRO_BITMAP *background,
                                                 ALLEGRO_EVENT_QUEUE *fila_eventos,
                                                 int pontuacao,
                                                 int inimigos_derrotados)
{
    for (int i = 0; i < MAX_PROJETEIS_BOSS_FASE2; i++)
    {
        if (projeteis_chefe_fase2[i].ativo)
        {
            int projetil_destruido = 0;

            // Verifica colisão com o escudo
            if (nave->especial2_ativo)
            {
                float shield_cx = nave->x + nave->largura / 2;
                float shield_cy = nave->y + nave->altura / 2;
                float shield_radius = 40;

                float proj_x = projeteis_chefe_fase2[i].x + projeteis_chefe_fase2[i].hitbox_offset_x;
                float proj_y = projeteis_chefe_fase2[i].y + projeteis_chefe_fase2[i].hitbox_offset_y;
                float proj_w = projeteis_chefe_fase2[i].hitbox_largura;
                float proj_h = projeteis_chefe_fase2[i].hitbox_altura;

                if (colisao_circulo_retangulo(shield_cx, shield_cy, shield_radius,
                                              proj_x, proj_y, proj_w, proj_h))
                {
                    projeteis_chefe_fase2[i].ativo = 0;
                    projetil_destruido = 1;
                    continue;
                }
            }

            // Verifica colisão com a nave se não estiver invulnerável
            if (!nave->invulneravel && !projetil_destruido)
            {
                if (colisao_retangular(
                        nave->x, nave->y,
                        nave->hitbox_offset_x, nave->hitbox_offset_y,
                        nave->hitbox_largura, nave->hitbox_altura,
                        projeteis_chefe_fase2[i].x, projeteis_chefe_fase2[i].y,
                        projeteis_chefe_fase2[i].hitbox_offset_x, projeteis_chefe_fase2[i].hitbox_offset_y,
                        projeteis_chefe_fase2[i].hitbox_largura, projeteis_chefe_fase2[i].hitbox_altura))
                {
                    projeteis_chefe_fase2[i].ativo = 0;
                    nave->vidas--;

                    if (nave->vidas <= 0)
                    {
                        nave->vidas = 0;
                        tela_game_over(pontuacao, inimigos_derrotados, fonte, fila_eventos, background);
                        exit(0);
                    }

                    nave->invulneravel = 1;
                    nave->tempo_invulneravel = al_get_time();
                    break;
                }
            }
        }
    }
}

void detectar_colisao_nave_item_fase2(NaveJogador *nave, ItemDrop2 *item)
{
    if (item->ativo && colisao_retangular_item(
                           nave->x, nave->y, nave->hitbox_largura, nave->hitbox_altura,
                           item->x + item->hitbox_offset_x, item->y, item->largura, item->altura, 0, 0))
    {
        item->ativo = 0;
        nave->especial2_coletado = 1;

        if (nave->especial3_coletado && !nave->especial2_ativo)
        {
            nave->especial3_coletado = 0;
        }
    }
}

void detectar_colisao_nave_item3_fase2(NaveJogador *nave, ItemDrop3 *item)
{
    if (item->ativo && colisao_retangular_item(
                           nave->x, nave->y, nave->hitbox_largura, nave->hitbox_altura,
                           item->x + item->hitbox_offset_x, item->y, item->largura, item->altura, 0, 0))
    {
        item->ativo = 0;
        nave->especial3_coletado = 1;
    }
}