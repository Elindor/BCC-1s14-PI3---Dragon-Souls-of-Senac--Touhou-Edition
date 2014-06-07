#ifndef _STAGE
#define _STAGE

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "jogo.h"

typedef struct _stage{
	ALLEGRO_BITMAP *stageBackground;
	ALLEGRO_AUDIO_STREAM *stageAudio;
	ALLEGRO_AUDIO_STREAM *bossAudio;
    int targetKills;
    int limitSpawn;
    int stageNum;
    int darkPhantom;    // Has a 0 if none, has his number if has
    int darkSpawn;
}stage;

stage *initStageWithNumber(int n);
void removeStage(stage *s);

#endif