#ifndef _OJOGO
#define _OJOGO

#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "camera.h"
#include "gameCamera.h"

#import "Ataque.h"
#import "Monster.h"
#import "stage.h" 

#define FPS 60

typedef struct _multiList{
    noAtaque* primeiroAtaque;
    noMonster* primeiroMonstro;
}multiList;

void erro(char *mensagem);

#endif