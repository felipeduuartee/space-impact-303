// itens.h
#ifndef ITENS_H
#define ITENS_H

#include <allegro5/allegro.h>

typedef struct {
    float x, y;               
    int ativo;                
    float tempo_ativacao;     
    float largura, altura;    
    int hitbox_offset_x;      
    ALLEGRO_BITMAP *sprite;   
} ItemDrop;

typedef struct {
    float x, y;               
    int ativo;                
    float tempo_ativacao;     
    float largura, altura;    
    int hitbox_offset_x;      
    ALLEGRO_BITMAP *sprite;   
} ItemDrop2;

typedef struct {
    float x, y;               
    int ativo;                
    float tempo_ativacao;     
    float largura, altura;    
    int hitbox_offset_x;      
    ALLEGRO_BITMAP *sprite;   
} ItemDrop3;


#define MAX_ITEMS 1 

void inicializar_item(ItemDrop *item);
void atualizar_item(ItemDrop *item);
void desenhar_item(ItemDrop *item);

void inicializar_item_fase2(ItemDrop2 *item);
void atualizar_item_fase2(ItemDrop2 *item);
void desenhar_item_fase2(ItemDrop2 *item);


void inicializar_item_fase3(ItemDrop3 *item);
void atualizar_item_fase3(ItemDrop3 *item);
void desenhar_item_fase3(ItemDrop3 *item);

#endif // ITENS_H
