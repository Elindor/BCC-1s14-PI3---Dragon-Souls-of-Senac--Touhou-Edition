CC=gcc -std=c99
CFLAGS= −W −Wall
EXEC=DSoS:TE
#SRC:= $(wildcard *.c)
SRC:= $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c)
#SRC:= $(wildcard **/*.c)
OBJ= $(SRC:.c=.o)
LIBS=-lopencv_core -lopencv_highgui -lallegro -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf -lallegro_primitives -lm

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(OBJ)
