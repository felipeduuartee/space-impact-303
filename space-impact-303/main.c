#include "config.h"
#include "chefes.h"
#include "colisoes.h"
#include "hud.h"
#include "inimigos.h"
#include "inimigos_fase2.h"
#include "itens.h"
#include "Joystick.h"
#include "nave_fase2.h"
#include "nave_jogador.h"
#include "projeteis.h"

int main()
{

    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    ALLEGRO_BITMAP *background = al_load_bitmap("./imagens/background1.png");
    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    ALLEGRO_FONT *fonte = al_load_ttf_font("./imagens/space-font.ttf", TAMANHO_FONTE, 0);
    ALLEGRO_FONT *fonte_hud = al_load_ttf_font("./imagens/space-font.ttf", 12, 0);

    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    joystick *controle = joystick_create();

    NaveJogador nave;
    Projetil projeteis[MAX_PROJETEIS];
    ProjetilInimigo projeteis_inimigos[MAX_PROJETEIS_INIMIGOS];
    ProjetilBoss projeteis_chefe[MAX_PROJETEIS_BOSS];
    ProjetilBoss projeteis_ricochete[MAX_PROJETEIS_RICOCHETE];
    Inimigo inimigos[MAX_INIMIGOS];
    Chefe chefe;
    ChefeFase2 chefe_fase2;
    ItemDrop item;
    InimigoFase2 inimigos_fase2[MAX_INIMIGOS_FASE2];
    ProjetilInimigo projeteis_inimigos_fase2[MAX_PROJETEIS_INIMIGOS];
    ProjetilBossFase2 projeteis_chefe_fase2[MAX_PROJETEIS_BOSS_FASE2];
    ItemDrop2 item2;
    ItemDrop3 item3;

    inicializar_nave(&nave);
    inicializar_projeteis(projeteis);
    inicializar_projeteis_inimigos(projeteis_inimigos);
    inicializar_projeteis_chefe(projeteis_chefe);
    inicializar_inimigos(inimigos);
    inicializar_chefe(&chefe);
    inicializar_item(&item);
    inicializar_inimigos_fase2(inimigos_fase2);
    inicializar_projeteis_inimigos(projeteis_inimigos_fase2);
    inicializar_chefe_fase2(&chefe_fase2);
    inicializar_projeteis_chefe_fase2(projeteis_chefe_fase2, MAX_PROJETEIS_BOSS_FASE2);
    inicializar_item_fase2(&item2);
    inicializar_item_fase3(&item3);

    ALLEGRO_BITMAP *background_tela_inicial = al_load_bitmap("./imagens/background_inicial.png");
    ALLEGRO_BITMAP *background_fase2 = al_load_bitmap("./imagens/background2.png");
    ALLEGRO_BITMAP *background_tela_pause = al_load_bitmap("./imagens/background_pause.png");
    ALLEGRO_BITMAP *background_tela_go = al_load_bitmap("./imagens/background-game-over.png");
    ALLEGRO_BITMAP *background_vitoria = al_load_bitmap("./imagens/tela-win.png");
    ALLEGRO_BITMAP *sprite_nave = al_load_bitmap("./imagens/nave.png");
    ALLEGRO_BITMAP *sprite_projetil_normal = al_load_bitmap("./imagens/bullet.png");
    ALLEGRO_BITMAP *sprite_projetil_especial = al_load_bitmap("./imagens/bullet-especial.png");
    ALLEGRO_BITMAP *sprite_inimigo1 = al_load_bitmap("./imagens/enemy.png");
    ALLEGRO_BITMAP *sprite_inimigo2 = al_load_bitmap("./imagens/enemy2.png");
    ALLEGRO_BITMAP *sprite_projeteis1 = al_load_bitmap("./imagens/bullet_enemy.png");
    ALLEGRO_BITMAP *sprite_projeteis2 = al_load_bitmap("./imagens/bullet_enemy2.png");
    ALLEGRO_BITMAP *sprite_chefe = al_load_bitmap("./imagens/boss1.png");
    ALLEGRO_BITMAP *sprite_tiro_comum = al_load_bitmap("./imagens/tiro-boss-1.png");
    ALLEGRO_BITMAP *sprite_laser_boss1 = al_load_bitmap("./imagens/laser-boss1.png");
    ALLEGRO_BITMAP *sprite_tiro_ricochete = al_load_bitmap("./imagens/tiro-boss-1a.png");
    ALLEGRO_BITMAP *sprite_inimigo3 = al_load_bitmap("./imagens/enemy3.png");
    ALLEGRO_BITMAP *sprite_inimigo4 = al_load_bitmap("./imagens/enemy4.png");
    ALLEGRO_BITMAP *sprite_projeteis3 = al_load_bitmap("./imagens/bullet_enemy3.png");
    ALLEGRO_BITMAP *sprite_projeteis4 = al_load_bitmap("./imagens/bullet_enemy4.png");
    ALLEGRO_BITMAP *sprite_projetil_circular = al_load_bitmap("./imagens/tiro-boss-2.png");
    ALLEGRO_BITMAP *sprite_laser_chefe2 = al_load_bitmap("./imagens/laser-chefe2.png");

    double ultimo_disparo = 0;
    int pontuacao = 0;
    int game_over = 0;
    double tempo_inicio = al_get_time();
    double tempo_fase = 0;
    int chefe_ativo = 0;
    int direcao_x = 0, direcao_y = 0;
    float background_x = 0;
    // int reiniciar = 0;
    int chefe_derrotado = 0;
    int chefe2_derrotado = 0;
    double tempo_chefe_derrotado = 0;
    int fase2_iniciada = 0;
    int fase_atual = 1;
    int inimigos_derrotados = 0;
    int inimigos_derrotados_fase2 = 0;
    double tempo_ultimo_disparo_fase2 = 0.0;
    double tempo_ultimo_disparo_fase1 = 0.0;
    bool transicao_em_andamento = false;

    al_start_timer(timer);
    exibir_texto_corrido(fonte, background_tela_inicial, fila_eventos);

    al_flush_event_queue(fila_eventos);
    exibir_menu(fonte, background_tela_inicial, fila_eventos, fonte_hud, background);

    al_flush_event_queue(fila_eventos);


    
    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        // if (reiniciar)
        // {
        //     reiniciar_jogo(&nave, &chefe, projeteis, projeteis_inimigos, projeteis_chefe, inimigos, &item, &pontuacao, &chefe_ativo, &tempo_inicio, &game_over, fila_eventos);
        //     reiniciar = 0;
        //     fase_atual = 1;
        //     fase2_iniciada = 0;
        //     al_flush_event_queue(fila_eventos);
        //     continue;
        // }


        //clicar no 'x' da janela
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }


        //pausar o jogo
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_P)
        {
            al_stop_timer(timer);
            al_flush_event_queue(fila_eventos);

            int retorno_pausa = exibir_tela_pausa(fonte, background_tela_pause, fila_eventos);

            al_flush_event_queue(fila_eventos);
            al_start_timer(timer);

            if (retorno_pausa == 0)
            {
                resetar_controle(controle);
            }
            else if (retorno_pausa == 1)
            {
                exit(1);
            }
            continue;
        }

        //começa o timer do jogo

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (!transicao_em_andamento)
            {
                direcao_x = (controle->right ? 1 : 0) - (controle->left ? 1 : 0);
                direcao_y = (controle->down ? 1 : 0) - (controle->up ? 1 : 0);
                tempo_fase = al_get_time() - tempo_inicio;

                atualizar_nave(&nave, direcao_x, direcao_y);

                if (nave.especial2_ativo)
                {

                    if (al_get_time() - nave.tempo_especial2 >= 5.0)
                    {
                        nave.especial2_ativo = 0;
                    }

                    al_draw_circle(nave.x + nave.largura / 2, nave.y + nave.altura / 2, 40, al_map_rgb(0, 0, 255), 3);
                }

                if (nave.especial3_ativo)
                {

                    if (al_get_time() - nave.tempo_especial3 >= 5.0)
                    {
                        nave.especial3_ativo = 0;
                    }
                }


                else if (nave.invulneravel)
                {

                    if (al_get_time() - nave.tempo_invulneravel > DURACAO_INVULNERAVEL)
                    {
                        nave.invulneravel = 0;
                    }
                }

                if (fase_atual == 1 && inimigos_derrotados >= 20 && !chefe_ativo)
                {
                    chefe_ativo = 1;
                    inicializar_chefe(&chefe);
                }

                if (fase_atual == 2 && inimigos_derrotados_fase2 >= 20 && !chefe_ativo)
                {
                    chefe_ativo = 1;
                    inicializar_chefe_fase2(&chefe_fase2);
                }

                if (chefe_derrotado)
                {
                    if (fase_atual == 1 && !fase2_iniciada)
                    {
                        if (al_get_time() - tempo_chefe_derrotado >= 2.0)
                        {

                            transicao_em_andamento = true;

                            al_stop_timer(timer);
                            al_flush_event_queue(fila_eventos);

                            al_clear_to_color(al_map_rgb(0, 0, 0));
                            al_flip_display();

                            exibir_texto_gradualmente("FASE 2", fonte, LARGURA_TELA / 2, ALTURA_TELA / 2, al_map_rgb(255, 255, 255), 0.2);

                            background = background_fase2;

                            chefe_ativo = 0;
                            fase2_iniciada = 1;
                            fase_atual = 2;

                            reinicializar_todos_projeteis(projeteis_inimigos, projeteis_inimigos_fase2, projeteis_chefe, projeteis);
                            resetar_controle(controle);

                            al_flush_event_queue(fila_eventos);
                            al_start_timer(timer);

                            while (transicao_em_andamento)
                            {
                                ALLEGRO_EVENT ev;
                                al_flush_event_queue(fila_eventos);
                                al_wait_for_event(fila_eventos, &ev);

                                if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
                                {
                                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE || ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_W || ev.keyboard.keycode == ALLEGRO_KEY_S)
                                    {
                                        continue;
                                    }
                                }
                                al_flush_event_queue(fila_eventos);

                                if (al_get_time() - tempo_chefe_derrotado >= 2.5)
                                {
                                    transicao_em_andamento = false;
                                    break;
                                }
                            }
                            al_flush_event_queue(fila_eventos);

                            transicao_em_andamento = false;

                            continue;
                            al_flush_event_queue(fila_eventos);
                        }
                        al_flush_event_queue(fila_eventos);
                    }

                    else if (fase_atual == 2)
                    {
                        if (chefe2_derrotado)
                        {
                            if (al_get_time() - tempo_chefe_derrotado >= 2.0)
                            {
                                tela_vitoria(pontuacao, inimigos_derrotados + inimigos_derrotados_fase2, fonte, fila_eventos, background_vitoria);
                                exit(0);
                            }
                        }
                    }
                }
                // al_flush_event_queue(fila_eventos);

                if (chefe_ativo)
                {
                    if (fase_atual == 1)
                    {
                        double intervalo_disparo_fase1 = 2.0;
                        double tempo_atual = al_get_time();

                        if (tempo_atual - tempo_ultimo_disparo_fase1 >= intervalo_disparo_fase1)
                        {
                            disparar_projetil_ricochete(&chefe, projeteis_ricochete, sprite_tiro_ricochete);
                            tempo_ultimo_disparo_fase1 = tempo_atual;
                        }

                        atualizar_chefe(&chefe, projeteis_chefe, sprite_laser_boss1);
                        atualizar_projeteis_chefe(projeteis_chefe);
                        atualizar_projeteis_ricochete(projeteis_ricochete);
                    }
                    else if (fase_atual == 2)
                    {

                        double intervalo_disparo_fase2 = 3.0;
                        double tempo_atual = al_get_time();

                        if (tempo_atual - tempo_ultimo_disparo_fase2 >= intervalo_disparo_fase2)
                        {
                            disparar_projetil_circular(projeteis_chefe_fase2, MAX_PROJETEIS_BOSS_FASE2, chefe_fase2.x, chefe_fase2.y, 4.0, sprite_projetil_circular);
                            tempo_ultimo_disparo_fase2 = tempo_atual;
                        }

                        atualizar_chefe_fase2(&chefe_fase2, projeteis_chefe_fase2, sprite_laser_chefe2, sprite_projetil_circular);
                        atualizar_projeteis_chefe_fase2(projeteis_chefe_fase2, MAX_PROJETEIS_BOSS_FASE2);
                    }
                }

                if (fase_atual == 1)
                {
                    if (!chefe_ativo)
                    {
                        gerar_novos_inimigos(inimigos, &nave, sprite_inimigo1, sprite_inimigo2, chefe_ativo);
                    }
                    atualizar_inimigos(inimigos, projeteis_inimigos);
                    atualizar_projeteis_inimigos(projeteis_inimigos);
                }
                else if (fase_atual == 2)
                {
                    if (!chefe_ativo)
                    {
                        gerar_novos_inimigos_fase2(inimigos_fase2, &nave, sprite_inimigo3, sprite_inimigo4, chefe_ativo);
                    }
                    atualizar_inimigos_fase2(inimigos_fase2, projeteis_inimigos_fase2, nave.especial3_ativo);
                    atualizar_projeteis_inimigos_fase2(projeteis_inimigos_fase2);
                }

                atualizar_projeteis(projeteis);
                atualizar_item(&item);
                atualizar_item_fase2(&item2);
                atualizar_item_fase3(&item3);

                if (fase_atual == 1)
                {
                    detectar_colisao_projeteis_nave(&nave, projeteis_inimigos, projeteis_chefe, fonte, background_tela_go, fila_eventos, pontuacao, inimigos_derrotados);
                    detectar_colisao_projeteis_inimigos(projeteis, inimigos, &pontuacao, &item, &inimigos_derrotados);
                    detectar_colisao_nave_inimigos(&nave, inimigos, fonte, background, fila_eventos, pontuacao, inimigos_derrotados);

                    if (chefe_ativo)
                    {
                        detectar_colisao_projeteis_chefe(&chefe, projeteis, &pontuacao, &chefe_derrotado, &tempo_chefe_derrotado);
                        detectar_colisao_nave_chefe(&nave, &chefe, pontuacao, inimigos_derrotados + inimigos_derrotados_fase2, fonte, background, fila_eventos);
                        detectar_colisao_projeteis_ricochete_nave(&nave, projeteis_ricochete, fonte, background_tela_go, fila_eventos, pontuacao, inimigos_derrotados + inimigos_derrotados_fase2);
                    }
                }
                else if (fase_atual == 2)
                {
                    if (nave.especial2_ativo)
                    {
                        detectar_colisao_escudo(&nave, projeteis_inimigos_fase2, inimigos_fase2);
                    }
                    detectar_colisao_projeteis_nave(&nave, projeteis_inimigos_fase2, NULL, fonte, background_tela_go, fila_eventos, pontuacao, inimigos_derrotados + inimigos_derrotados_fase2);
                    detectar_colisao_projeteis_inimigos_fase2(projeteis, inimigos_fase2, &pontuacao, &item2, &item3, &inimigos_derrotados_fase2);

                    detectar_colisao_nave_inimigos_fase2(&nave, inimigos_fase2, pontuacao, (inimigos_derrotados + inimigos_derrotados_fase2), fonte, background_tela_go, fila_eventos);

                    detectar_colisao_projeteis_inimigos_fase2_nave(&nave, projeteis_inimigos_fase2, pontuacao, (inimigos_derrotados + inimigos_derrotados_fase2), fonte, background_tela_go, fila_eventos);

                    if (chefe_ativo)
                    {
                        detectar_colisao_projeteis_chefe_fase2(&chefe_fase2, projeteis, &pontuacao, &chefe2_derrotado, &tempo_chefe_derrotado);
                        detectar_colisao_nave_chefe_fase2(&nave, &chefe_fase2, pontuacao, (inimigos_derrotados + inimigos_derrotados_fase2), fonte, background_tela_go, fila_eventos);
                        detectar_colisao_projeteis_chefe_fase2_nave(
                            &nave,
                            projeteis_chefe_fase2,
                            fonte,
                            background_tela_go,
                            fila_eventos,
                            pontuacao,
                            inimigos_derrotados + inimigos_derrotados_fase2);
                    }
                }

                if (item.ativo)
                {
                    detectar_colisao_nave_item(&nave, &item);
                }

                if (item2.ativo)
                {
                    detectar_colisao_nave_item_fase2(&nave, &item2);
                }

                if (item3.ativo)
                {
                    detectar_colisao_nave_item3_fase2(&nave, &item3);
                }

                float intervalo_disparo_atual = nave.especial_ativo ? INTERVALO_DISPARO_ESPECIAL : INTERVALO_DISPARO;

                if (controle->shot && (al_get_time() - ultimo_disparo >= intervalo_disparo_atual))
                {
                    disparar_projetil(projeteis, nave.x + nave.largura, nave.y + nave.altura / 2,
                                      nave.especial_ativo, sprite_projetil_normal, sprite_projetil_especial);
                    ultimo_disparo = al_get_time();
                }

                if (nave.especial_ativo && al_get_time() - nave.tempo_especial > DURACAO_ESPECIAL)
                {
                    nave.especial_ativo = 0;
                }

                background_x -= 2;
                if (background_x <= -al_get_bitmap_width(background))
                    background_x = 0;

                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(background, background_x, 0, 0);
                al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

                desenhar_nave(&nave, sprite_nave, direcao_y);
                desenhar_projeteis(projeteis);

                if (fase_atual == 1)
                {
                    desenhar_projeteis_inimigos(projeteis_inimigos, sprite_projeteis1, sprite_projeteis2);
                    desenhar_inimigos(inimigos, sprite_inimigo1, sprite_inimigo2);
                }
                else if (fase_atual == 2)
                {
                    desenhar_projeteis_inimigos_fase2(projeteis_inimigos_fase2, sprite_projeteis3, sprite_projeteis4);
                    desenhar_inimigos_fase2(inimigos_fase2, sprite_inimigo3, sprite_inimigo4);
                }

                if (chefe_ativo)
                {
                    if (fase_atual == 1)
                    {
                        desenhar_chefe(&chefe);
                        desenhar_projeteis_chefe(projeteis_chefe, sprite_tiro_comum, sprite_laser_boss1);
                        desenhar_projeteis_ricochete(projeteis_ricochete);
                    }
                    else if (fase_atual == 2)
                    {
                        desenhar_chefe_fase2(&chefe_fase2);
                        desenhar_projeteis_chefe_fase2(projeteis_chefe_fase2, MAX_PROJETEIS_BOSS_FASE2);
                    }
                }

                if (item.ativo)
                {
                    desenhar_item(&item);
                }

                if (item2.ativo)
                {
                    desenhar_item_fase2(&item2);
                }

                if (item3.ativo)
                {
                    desenhar_item_fase3(&item3);
                }

                desenhar_hud(fonte_hud, nave.vidas, pontuacao, tempo_fase, &nave);
                al_flip_display();

                if (nave.vidas <= 0 && !game_over)
                {
                    game_over = 1;
                    int retorno_game_over = tela_game_over(pontuacao, inimigos_derrotados + inimigos_derrotados_fase2, fonte, fila_eventos, background_tela_go);

                    if (retorno_game_over == 1)
                    {
                        exit(0);
                    }
                }
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                joystick_up(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                joystick_down(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                joystick_left(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                joystick_right(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                controle->shot = 1;

            if (ev.keyboard.keycode == ALLEGRO_KEY_E)
            {
                if (nave.especial_coletado)
                {
                    nave.especial_ativo = 1;
                    nave.tempo_especial = al_get_time();
                    nave.especial_coletado = 0;
                }
                else if (nave.especial2_coletado)
                {
                    nave.especial2_ativo = 1;
                    nave.tempo_especial2 = al_get_time();
                    nave.invulneravel = 1;
                    nave.especial2_coletado = 0;
                }
                else if (nave.especial3_coletado)
                {
                    nave.especial3_ativo = 1;
                    nave.tempo_especial3 = al_get_time();
                    nave.especial3_coletado = 0;
                }
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
                joystick_up(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_S)
                joystick_down(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_A)
                joystick_left(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_D)
                joystick_right(controle);
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                controle->shot = 0;
        }
    }

    al_destroy_bitmap(sprite_nave);
    al_destroy_bitmap(sprite_projetil_normal);
    al_destroy_bitmap(sprite_projetil_especial);
    al_destroy_bitmap(sprite_inimigo1);
    al_destroy_bitmap(sprite_inimigo2);
    al_destroy_bitmap(sprite_projeteis1);
    al_destroy_bitmap(sprite_projeteis2);
    al_destroy_bitmap(sprite_chefe);
    al_destroy_bitmap(sprite_projetil_circular);
    al_destroy_bitmap(sprite_tiro_comum);
    al_destroy_bitmap(background);
    al_destroy_font(fonte);
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
    al_destroy_timer(timer);
    joystick_destroy(controle);
    al_destroy_font(fonte_hud);

    return 0;
}
