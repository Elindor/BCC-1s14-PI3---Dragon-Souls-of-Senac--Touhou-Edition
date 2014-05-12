
TARGETS = teste

CC = gcc

FLAGS = -std=c99

LIBS = -lopencv_core -lopencv_highgui -lallegro -lallegro_main -lallegro_image -lallegro_primitives

all: $(TARGETS)

camera.o: camera.c camera.h
	$(CC) $(FLAGS) $< -c

fila.o: fila.c fila.h
	$(CC) $(FLAGS) $< -c

hsvMatriz.o: hsvMatriz.c hsvMatriz.h
	$(CC) $(FLAGS) $< -c

teste: hsvTrack.c camera.o fila.o hsvMatriz.o
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *~ *.o

destroy: clean
	rm -f $(TARGETS)
