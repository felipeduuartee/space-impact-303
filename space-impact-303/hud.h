#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "nave_jogador.h"
#include "projeteis.h"
#include "inimigos.h"
#include "chefes.h"
#include "colisoes.h"
#include "itens.h"
#include "Joystick.h"
#include "inimigos_fase2.h"
#include "nave_fase2.h"

// Funções para inicializar e desenhar o HUD
void desenhar_hud(ALLEGRO_FONT *fonte, int vidas, int pontuacao, double tempo_fase, NaveJogador *nave);
#endif // HUD_H
