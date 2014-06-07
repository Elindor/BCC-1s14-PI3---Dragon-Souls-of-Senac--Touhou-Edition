#ifndef MONSTER
#define MONSTER

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <opencv/highgui.h>

#include <time.h>
#include "globals.h"
#include "Monster.h"


typedef enum monstro{
    Crab = 0, Fly = 1, Bug = 2, Fat = 3, Kobold = 4, Worm = 5, Leech = 6, Hornet = 7, UndeadFat = 8, Knight = 9, Shadow = 10, Spider = 11, Sentry = 12, Marlingone = 21, Hueda = 22, Cirno = 23, Dragon = 24, Balrog = 25, Lavos = 26, Phantom2 = 32, Phantom3 = 33, Phantom4 = 34, Phantom5 = 35, Phantom6 = 36
}monstro;

typedef struct _Monster{
    int HP;
    int ataque[2];
    int currentCooldown;
    float cooldown;
    ALLEGRO_BITMAP *image;
    char name[32];
    float X;
    float Y;
    float centerX;
    float centerY;
    int fromLeft;
    int ready;
    int isHit;
}Monster;

typedef struct _noMonster{
    struct _noMonster *prox;
    Monster *monster;
}noMonster;

Monster* initWithMonsterNumber(int fase);
Monster* initWithBossNumber(int fase);

int getId(int fase);
void startMove(Monster* monstro);
void getImageMonster(int number, ALLEGRO_BITMAP** image);
int getLife(int number);
void getAttack(int fase, int *num);
float getCooldown(int num);
void monsterGotHit(ALLEGRO_BITMAP *display, Monster *m);
void getName(int num, char *temp);

#endif