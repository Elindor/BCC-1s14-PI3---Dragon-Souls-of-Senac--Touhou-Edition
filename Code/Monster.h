#include <opencv/highgui.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


typedef enum monstro{
    Crab = 0, Fly = 1, Bug = 2, Fat = 3, Kobold = 4, Worm = 5, Leech = 6, Hornet = 7, UndeadFat = 8, Knight = 9, Shadow = 10, Spider = 11, Sentry = 12
};

typedef struct _Monster{
    int HP;
    int ataque[2];
    float cooldown;
    ALLEGRO_BITMAP *image;
    float X;
    float Y;
}Monster;

typedef struct _noMonster{
    noMonster* prox;
    Monster* attack;
}noMonster;


Monster initWithMonsterNumber(int fase);

int getId(int fase);
ALLEGRO_BITMAP getImage(int number, ALLEGRO_BITMAP image);
int getLife(int number);
void getAttack(int fase, int *num);
int getCooldown(int num);