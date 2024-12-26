#include <stdlib.h>
#include "Joystick.h"

#define LARGURA_TELA 800
#define ALTURA_TELA 600
double ultimo_disparo_inimigo_fase2[MAX_INIMIGOS_FASE2];

joystick *joystick_create()
{
    joystick *element = (joystick *)malloc(sizeof(joystick));
    element->right = 0;
    element->left = 0;
    element->up = 0;
    element->down = 0;
    element->shot = 0;
    return element;
}

void joystick_destroy(joystick *element)
{
    free(element);
}

void joystick_right(joystick *element)
{
    element->right ^= 1;
}

void joystick_left(joystick *element)
{
    element->left ^= 1;
}

void joystick_up(joystick *element)
{
    element->up ^= 1;
}

void joystick_down(joystick *element)
{
    element->down ^= 1;
}

void resetar_controle(joystick *element)
{
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);
    element->left = al_key_down(&state, ALLEGRO_KEY_A);
    element->right = al_key_down(&state, ALLEGRO_KEY_D);
    element->up = al_key_down(&state, ALLEGRO_KEY_W);
    element->down = al_key_down(&state, ALLEGRO_KEY_S);
    element->shot = al_key_down(&state, ALLEGRO_KEY_SPACE);
}

void limpar_fila_eventos(ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    ALLEGRO_EVENT ev;
    while (al_get_next_event(fila_eventos, &ev))
    {
    }
}

int exibir_tela_pausa(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background_pausa, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    int opcao_selecionada = 0;
    float background_x = 0;
    float background_speed = 1.0;

    ALLEGRO_TIMER *timer_pausa = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE *fila_pausa = al_create_event_queue();

    al_register_event_source(fila_pausa, al_get_keyboard_event_source());
    al_register_event_source(fila_pausa, al_get_timer_event_source(timer_pausa));
    al_register_event_source(fila_pausa, al_get_display_event_source(al_get_current_display()));
    al_start_timer(timer_pausa);

    bool atualizar_tela = true;

    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_pausa, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit(0);
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            background_x -= background_speed;
            if (background_x <= -al_get_bitmap_width(background_pausa))
            {
                background_x = 0;
            }
            atualizar_tela = true;
        }

        if (atualizar_tela)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background_pausa, background_x, 0, 0);
            al_draw_bitmap(background_pausa, background_x + al_get_bitmap_width(background_pausa), 0, 0);

            for (int i = 0; i < 2; i++)
            {
                ALLEGRO_COLOR cor;
                if (i == opcao_selecionada)
                {
                    cor = al_map_rgb(255, 255, 255);
                }
                else
                {
                    cor = al_map_rgb(128, 128, 128);
                }
                const char *texto;
                float pos_y = 300 + i * 50;
                if (i == 0)
                    texto = "Voltar ao Jogo";
                else
                    texto = "Sair do Jogo";
                al_draw_textf(fonte, cor, 400, pos_y, ALLEGRO_ALIGN_CENTER, "%s", texto);
            }

            al_flip_display();
            atualizar_tela = false;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                opcao_selecionada = (opcao_selecionada + 1) % 2;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                opcao_selecionada = (opcao_selecionada + 1) % 2;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                al_stop_timer(timer_pausa);
                al_destroy_timer(timer_pausa);
                al_destroy_event_queue(fila_pausa);

                al_flush_event_queue(fila_eventos);

                if (opcao_selecionada == 0)
                {
                    return 0;
                }
                else if (opcao_selecionada == 1)
                {
                    exit(1);
                }
            }
        }
    }
}

int tela_game_over(int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background_game_over)
{
    int opcao_selecionada = 0;
    float background_x = 0;
    float background_speed = 1.0;

    while (1)
    {

        background_x -= background_speed;
        if (background_x <= -al_get_bitmap_width(background_game_over))
        {
            background_x = 0;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(background_game_over, background_x, 0, 0);
        al_draw_bitmap(background_game_over, background_x + al_get_bitmap_width(background_game_over), 0, 0);

        al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 150,
                     ALLEGRO_ALIGN_CENTER, "Voce perdeu!");

        char pontuacao_texto[50];
        snprintf(pontuacao_texto, sizeof(pontuacao_texto), "Pontuacao: %d", pontuacao);
        al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2 - 100,
                     ALLEGRO_ALIGN_CENTER, pontuacao_texto);

        char inimigos_texto[50];
        snprintf(inimigos_texto, sizeof(inimigos_texto), "Inimigos derrotados: %d", inimigos_derrotados_total);
        al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2 - 50,
                     ALLEGRO_ALIGN_CENTER, inimigos_texto);

        ALLEGRO_COLOR cor_opcao = opcao_selecionada == 0 ? al_map_rgb(255, 255, 255) : al_map_rgb(128, 128, 128);
        al_draw_text(fonte, cor_opcao, LARGURA_TELA / 2, ALTURA_TELA / 2 + 50, ALLEGRO_ALIGN_CENTER, "Enter para sair do jogo");

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {

                return opcao_selecionada;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {

            exit(0);
        }
    }
}

int exibir_menu(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_FONT *font_felipe, ALLEGRO_BITMAP *background_jogo)
{
    int opcao_selecionada = 0;
    float background_x = 0;
    float background_speed = 1.0;

    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit(0);
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            background_x -= background_speed;
            if (background_x <= -al_get_bitmap_width(background))
            {
                background_x = 0;
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Space Impact 303");

            for (int i = 0; i < 3; i++)
            {
                ALLEGRO_COLOR cor = (i == opcao_selecionada) ? al_map_rgb(255, 255, 255) : al_map_rgb(128, 128, 128);
                const char *texto;
                float pos_y = 300 + i * 50;
                if (i == 0)
                    texto = "Começar";
                else if (i == 1)
                    texto = "Controles";
                else
                    texto = "Sair";
                al_draw_textf(fonte, cor, 400, pos_y, ALLEGRO_ALIGN_CENTER, "%s", texto);
            }

            al_draw_text(font_felipe, al_map_rgb(255, 255, 255), 400, 570, ALLEGRO_ALIGN_CENTER, "Feito por: Felipe Duarte");

            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                opcao_selecionada = (opcao_selecionada + 1) % 3;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                opcao_selecionada = (opcao_selecionada + 2) % 3;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if (opcao_selecionada == 0)
                {
                    exibir_dialogo(fila_eventos, background_jogo);
                    return 1;
                }
                else if (opcao_selecionada == 1)
                {
                    exibir_tela_controles(fonte, background, fila_eventos);
                }
                else if (opcao_selecionada == 2)
                {
                    exit(0);
                }
            }
        }
    }
}

void exibir_dialogo(ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background)
{
    // Carrega a imagem do diálogo
    ALLEGRO_BITMAP *imagem_dialogo = al_load_bitmap("./imagens/dialogo.png");
    if (!imagem_dialogo)
    {
        fprintf(stderr, "Falha ao carregar a imagem dialogo.png\n");
        exit(1);
    }

    // Obtém a largura e altura da tela
    int largura_tela = al_get_display_width(al_get_current_display());
    int altura_tela = al_get_display_height(al_get_current_display());

    // Calcula a posição para centralizar a imagem no rodapé
    int pos_x = (largura_tela - al_get_bitmap_width(imagem_dialogo)) / 2;
    int pos_y = altura_tela - al_get_bitmap_height(imagem_dialogo); // Posiciona no rodapé

    bool sair = false;
    ALLEGRO_EVENT ev;
    float background_x = 0;
    float background_speed = 1.0; // Ajuste a velocidade conforme necessário

    while (!sair)
    {
        // Aguarda por eventos
        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit(0);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                sair = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            // Atualiza a posição do background
            background_x -= background_speed;
            if (background_x <= -al_get_bitmap_width(background))
            {
                background_x = 0;
            }

            // Limpa a tela e desenha o fundo do jogo
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

            // Desenha a imagem do diálogo no rodapé
            al_draw_bitmap(imagem_dialogo, pos_x, pos_y, 0);

            // Atualiza a tela
            al_flip_display();
        }
    }

    // Destrói a imagem do diálogo após o uso
    al_destroy_bitmap(imagem_dialogo);
}



void exibir_texto_corrido(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    // Texto que será exibido
    const char *texto[] = {
        "Ano 2921.",
        "A humanidade expandiu-se pelo universo.",
        "Colônias e estações espaciais floresceram.",
        "A imagem do Cruzeiro resplandece por toda a galáxia.",
        "Mas uma nova ameaça surgiu das sombras.",
        "Relatórios de ataques alarmaram o Alto Comando.",
        "Você é nossa última linha de defesa.",
        "Proteja a estação e salve a galáxia."};

    int num_linhas = sizeof(texto) / sizeof(texto[0]);

    float posicao_y = ALTURA_TELA; 
    float velocidade = 70.0;       

    float background_x = 0;
    float background_speed = 50.0; 

    bool sair = false;
    ALLEGRO_EVENT ev;
    double ultimo_tempo = al_get_time();

    while (!sair)
    {
        while (al_get_next_event(fila_eventos, &ev))
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                exit(0);
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    sair = true;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_TIMER)
            {
                double tempo_atual = al_get_time();
                double delta_tempo = tempo_atual - ultimo_tempo;
                ultimo_tempo = tempo_atual;

                posicao_y -= velocidade * delta_tempo;

                background_x -= background_speed * delta_tempo;
                if (background_x <= -al_get_bitmap_width(background))
                {
                    background_x = 0;
                }

                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(background, background_x, 0, 0);
                al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);

                for (int i = 0; i < num_linhas; i++)
                {
                    float y = posicao_y + i * 70; 
                    if (y < -50 || y > ALTURA_TELA + 50)
                        continue; 

                    float x = LARGURA_TELA / 2;

                    float largura_maxima = LARGURA_TELA * 0.8; 

                    al_draw_multiline_text(fonte, al_map_rgb(255, 255, 0),
                                           x, y, largura_maxima, 30,
                                           ALLEGRO_ALIGN_CENTER, texto[i]);
                }

                if (posicao_y + num_linhas * 50 < 0)
                {
                    al_draw_text(fonte, al_map_rgb(255, 255, 255),
                                 LARGURA_TELA / 2, ALTURA_TELA / 2,
                                 ALLEGRO_ALIGN_CENTER, "Pressione ENTER para continuar.");
                }

                al_flip_display();
            }
        }
    }
}

void exibir_tela_controles(ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *background, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    float background_x = 0;
    bool sair = false;

    while (!sair)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            background_x -= 1;
            if (background_x <= -al_get_bitmap_width(background))
            {
                background_x = 0;
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + al_get_bitmap_width(background), 0, 0);
            al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, al_map_rgba(0, 0, 0, 150));
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 150, ALLEGRO_ALIGN_CENTER, "CONTROLES");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 220, ALLEGRO_ALIGN_CENTER, "MOVER: W, A, S, D");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 270, ALLEGRO_ALIGN_CENTER, "ATIRAR: ESPACO");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 320, ALLEGRO_ALIGN_CENTER, "HABILIDADE ESPECIAL: E");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 370, ALLEGRO_ALIGN_CENTER, "PAUSAR: P");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 420, ALLEGRO_ALIGN_CENTER, "VOLTAR: ENTER");

            al_flip_display(); // Atualiza a tela
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            sair = true; // Encerra o loop e retorna ao menu
        }

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit(0); // Sai do programa completamente
        }
    }
}

int tela_vitoria(int pontuacao, int inimigos_derrotados_total, ALLEGRO_FONT *fonte, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_BITMAP *background_vitoria)
{
    int opcao_selecionada = 0;    // 0 = Sair do Jogo
    float background_x = 0;       // Posição inicial do background
    float background_speed = 1.0; // Velocidade de movimento do fundo

    while (1)
    {

        background_x -= background_speed;
        if (background_x <= -al_get_bitmap_width(background_vitoria))
        {
            background_x = 0;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(background_vitoria, background_x, 0, 0);
        al_draw_bitmap(background_vitoria, background_x + al_get_bitmap_width(background_vitoria), 0, 0);

        al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 2, ALTURA_TELA / 2 - 150,
                     ALLEGRO_ALIGN_CENTER, "Voce venceu!");

        char pontuacao_texto[50];
        snprintf(pontuacao_texto, sizeof(pontuacao_texto), "Pontuacao: %d", pontuacao);
        al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2 - 100,
                     ALLEGRO_ALIGN_CENTER, pontuacao_texto);

        char inimigos_texto[50];
        snprintf(inimigos_texto, sizeof(inimigos_texto), "Inimigos derrotados: %d", inimigos_derrotados_total);
        al_draw_text(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, ALTURA_TELA / 2 - 50,
                     ALLEGRO_ALIGN_CENTER, inimigos_texto);

        ALLEGRO_COLOR cor_opcao = opcao_selecionada == 0 ? al_map_rgb(255, 255, 255) : al_map_rgb(128, 128, 128);
        al_draw_text(fonte, cor_opcao, LARGURA_TELA / 2, ALTURA_TELA / 2 + 50, ALLEGRO_ALIGN_CENTER, "Enter para sair do jogo");

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {

                return opcao_selecionada;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {

            exit(0);
        }
    }
}

void reiniciar_jogo(NaveJogador *nave, Chefe *chefe, Projetil projeteis[], ProjetilInimigo projeteis_inimigos[],
                    ProjetilBoss projeteis_chefe[], Inimigo inimigos[], ItemDrop *item, int *pontuacao,
                    int *chefe_ativo, double *tempo_inicio, int *game_over, ALLEGRO_EVENT_QUEUE *fila_eventos)
{
    *pontuacao = 0;
    *chefe_ativo = 0;
    *tempo_inicio = al_get_time();
    *game_over = 0;

    inicializar_nave(nave);
    inicializar_projeteis(projeteis);
    inicializar_projeteis_inimigos(projeteis_inimigos);
    inicializar_projeteis_chefe(projeteis_chefe);
    inicializar_inimigos(inimigos);
    inicializar_chefe(chefe);
    inicializar_item(item);

    al_flush_event_queue(fila_eventos);
}

void exibir_texto_gradualmente(const char *texto, ALLEGRO_FONT *fonte, float x, float y, ALLEGRO_COLOR cor, float intervalo_entre_letras)
{

    al_clear_to_color(al_map_rgb(0, 0, 0));

    char buffer[128] = ""; // texto construindo
    int tamanho_texto = strlen(texto);

    for (int i = 0; i < tamanho_texto; i++)
    {

        buffer[i] = texto[i];
        buffer[i + 1] = '\0';

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(fonte, cor, x, y, ALLEGRO_ALIGN_CENTRE, buffer);
        al_flip_display();

        al_rest(intervalo_entre_letras);
    }

    al_rest(1.0);
}

void reinicializar_todos_projeteis(ProjetilInimigo projeteis_fase1[], ProjetilInimigo projeteis_fase2[], ProjetilBoss projeteis_chefe[], Projetil projeteis_jogador[])
{
    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS; i++)
    {
        projeteis_fase1[i].ativo = 0;
        projeteis_fase1[i].x = 0;
        projeteis_fase1[i].y = 0;
    }

    for (int i = 0; i < MAX_PROJETEIS_INIMIGOS_FASE2; i++)
    {
        projeteis_fase2[i].ativo = 0;
        projeteis_fase2[i].x = 0;
        projeteis_fase2[i].y = 0;
        ultimo_disparo_inimigo_fase2[i] = al_get_time();
    }

    for (int i = 0; i < MAX_PROJETEIS_BOSS; i++)
    {
        projeteis_chefe[i].ativo = 0;
        projeteis_chefe[i].x = 0;
        projeteis_chefe[i].y = 0;
    }

    for (int i = 0; i < MAX_PROJETEIS; i++)
    {
        projeteis_jogador[i].ativo = 0;
        projeteis_jogador[i].x = 0;
        projeteis_jogador[i].y = 0;
    }
}
