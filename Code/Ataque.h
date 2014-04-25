#include <opencv/highgui.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


typedef enum strike{
    Pincer = 1, Spit = 2, Needle = 3, Cut = 4, SpearThrow = 5, MagicMissiles = 6, Spores = 7, Needle = 8, Cut2 = 9, Omnicut = 10, Curse = 11, Web = 12, Fireball = 13
};

typedef struct _Ataque{
    float X0;
    float Y0;
    float X;
    float Y;
    int damage;
    int currentDuration;
    float preAnimationTime;
    float duration;
    ALLEGRO_BITMAP *image;
    int id;
    
}Ataque;

typedef struct _noAtaque{
    noAtaque* prox;
    Ataque* attack;
}noAtaque;


*Ataque initWithAttackNumber(int attackId, int senderX, int senderY);
bool checkAttack(Ataque *attack)
ALLEGRO_BITMAP getImage(int number, X0, Y0, X, Y);
int getDamage(int number);
int getDuration(int num);

