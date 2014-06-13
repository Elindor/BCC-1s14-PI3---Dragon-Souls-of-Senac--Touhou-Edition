#ifndef ATAQUE
#define ATAQUE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>


typedef enum _strike{
    Pincer = 1, Spit = 2, Needle = 3, Cut = 4, SpearThrow = 5, MagicMissiles = 6, Spores = 7, NeedleB = 8, CutB = 9, Omnicut = 10, Curse = 11, Web = 12, Fireball = 13
}strike;

typedef struct _Ataque{
    float X0;
    float Y0;
    float X;
    float Y;
    float targetX;
    float targetY;
    int damage;
    int deathCountdown;
    int currentDuration;
    float preAnimationTime;
    float duration;
    ALLEGRO_BITMAP *image;
    float angle;
    int atkId;
    
}Ataque;

typedef struct _noAtaque{
    struct _noAtaque *prox;
    Ataque *attack;
}noAtaque;


Ataque *initWithAttackNumber(int attackId, int senderX, int senderY);
bool checkAttack(Ataque *attack);
void getImageAttack(int number, ALLEGRO_BITMAP **image);
int getDamage(int number);
float getDuration(int num);
void playAudio(int num);

#endif