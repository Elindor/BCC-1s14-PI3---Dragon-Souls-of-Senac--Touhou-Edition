#ifndef gameCamera
#define  gameCamera

#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "camera.h"

#include "fila.h"
#include "hsvMatriz.h"
#include "jogo.h"

void drawAtk(fila *f);
void rgbToHsv(int r, int g, int b, int *h, int *s, int *v);
void cameraLoop(unsigned char ***matriz, camera *cam, fila *f, int ***background, ALLEGRO_BITMAP *gameScreen, int *sx, int *sy);
void getBackground(camera *cam, int ***background);

#endif