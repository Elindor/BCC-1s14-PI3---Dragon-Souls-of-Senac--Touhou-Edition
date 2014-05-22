#ifndef MONSTER
#define MONSTER

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>



typedef enum monstro{
    Crab = 0, Fly = 1, Bug = 2, Fat = 3, Kobold = 4, Worm = 5, Leech = 6, Hornet = 7, UndeadFat = 8, Knight = 9, Shadow = 10, Spider = 11, Sentry = 12
}monstro;

typedef struct _Monster{
    int HP;
    int ataque[2];
    float cooldown;         // Somar o periodo dos ataques no uso, lembrar de deletar comentário
    ALLEGRO_BITMAP *image;
    float X;
    float Y;
    bool fromLeft;
    bool ready;
}Monster;

typedef struct _noMonster{
    struct _noMonster *prox;
    Monster *monster;
}noMonster;

Monster* initWithMonsterNumber(int fase);

int getId(int fase);
void startMove(Monster* monstro);
void getImageMonster(int number, ALLEGRO_BITMAP* image);
int getLife(int number);
void getAttack(int fase, int *num);
float getCooldown(int num);

#endif