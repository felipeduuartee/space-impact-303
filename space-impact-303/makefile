# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c99 -g

# Diretórios de inclusão
INCLUDES = -I. -I/usr/include/x86_64-linux-gnu

# Bibliotecas Allegro
LIBS = -L/usr/lib/x86_64-linux-gnu -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives

# Arquivos objeto
OBJECTS = main.o nave_jogador.o projeteis.o inimigos.o chefes.o hud.o colisoes.o itens.o Joystick.o inimigos_fase2.o

# Nome do executável
TARGET = jogo

# Regra padrão
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS) -lm

# Compilação dos arquivos objeto
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(INCLUDES)

nave_jogador.o: nave_jogador.c
	$(CC) $(CFLAGS) -c nave_jogador.c $(INCLUDES)

projeteis.o: projeteis.c
	$(CC) $(CFLAGS) -c projeteis.c $(INCLUDES)

inimigos.o: inimigos.c
	$(CC) $(CFLAGS) -c inimigos.c $(INCLUDES)

chefes.o: chefes.c
	$(CC) $(CFLAGS) -c chefes.c $(INCLUDES)

hud.o: hud.c
	$(CC) $(CFLAGS) -c hud.c $(INCLUDES)

colisoes.o: colisoes.c
	$(CC) $(CFLAGS) -c colisoes.c $(INCLUDES)

itens.o: itens.c
	$(CC) $(CFLAGS) -c itens.c $(INCLUDES)

Joystick.o: Joystick.c
	$(CC) $(CFLAGS) -c Joystick.c $(INCLUDES)

inimigos_fase2.o: inimigos_fase2.c inimigos_fase2.h
	$(CC) $(CFLAGS) -c inimigos_fase2.c $(INCLUDES)


# Limpeza dos arquivos objeto e do executável
clean:
	rm -f $(OBJECTS) $(TARGET)
