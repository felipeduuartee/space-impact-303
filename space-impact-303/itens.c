
#include "itens.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

void inicializar_item(ItemDrop *item)
{
    item->ativo = 0; 
    item->sprite = al_load_bitmap("./imagens/especial1.png");
    if (item->sprite)
    {
        item->largura = al_get_bitmap_width(item->sprite) - 10; 
        item->altura = al_get_bitmap_height(item->sprite) - 30; 
        item->hitbox_offset_x = -40;                            
    }
    else
    {
        item->largura = 5; 
        item->altura = 5;
        item->hitbox_offset_x = 0;
    }
}


void atualizar_item(ItemDrop *item)
{
    if (item->ativo)
    {

        if (al_get_time() - item->tempo_ativacao > 8.0)
        {
            item->ativo = 0; 
        }
    }
}


void desenhar_item(ItemDrop *item)
{
    if (item->ativo)
    {
        al_draw_bitmap(item->sprite, item->x, item->y, 0);
    }
}



void inicializar_item_fase2(ItemDrop2 *item)
{
    item->ativo = 0; // Inativo por padrão
    item->sprite = al_load_bitmap("./imagens/especial2.png");
    if (item->sprite)
    {
        item->largura = al_get_bitmap_width(item->sprite) - 10; 
        item->altura = al_get_bitmap_height(item->sprite) - 10; 
        item->hitbox_offset_x = -40;                            
    }
    else
    {
        item->largura = 5; 
        item->altura = 5;
        item->hitbox_offset_x = 0;
    }
}


void atualizar_item_fase2(ItemDrop2 *item)
{
    if (item->ativo)
    {

        if (al_get_time() - item->tempo_ativacao > 8.0)
        {
            item->ativo = 0;
        }
    }
}


void desenhar_item_fase2(ItemDrop2 *item)
{
    if (item->ativo)
    {
        al_draw_bitmap(item->sprite, item->x, item->y, 0);
    }
}



void inicializar_item_fase3(ItemDrop3 *item)
{
    item->ativo = 0; 
    item->sprite = al_load_bitmap("./imagens/especial3.png");
    if (item->sprite)
    {
        item->largura = al_get_bitmap_width(item->sprite) - 10; 
        item->altura = al_get_bitmap_height(item->sprite) - 30; 
        item->hitbox_offset_x = -40;                            
    }
    else
    {
        item->largura = 5; 
        item->altura = 5;
        item->hitbox_offset_x = 0;
    }
}


void atualizar_item_fase3(ItemDrop3 *item)
{
    if (item->ativo)
    {

        if (al_get_time() - item->tempo_ativacao > 8.0)
        {
            item->ativo = 0;
        }
    }
}


void desenhar_item_fase3(ItemDrop3 *item)
{
    if (item->ativo)
    {
        al_draw_bitmap(item->sprite, item->x, item->y, 0);
    }
}

