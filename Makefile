CC=gcc
CFLAGS=-I. `sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer -lm
DEPS = Map/map.h Player/player.h Render/render.h Tscreen/tscreen.h constantes.h
OBJ = main.o Map/map.o Player/player.o Render/render.o Tscreen/tscreen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TheLabyrinth: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o *~ core *~ Map/*.o Player/*.o Render/*.o Tscreen/*.o
