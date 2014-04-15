#include <opencv/highgui.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>

typedef enum ataque{
    Arrow, Fireball, bla, exemplo4,
}AttackId;


typedef struct _Monster{
    int HP;
    AttackId ataque;
    ALLEGRO_BITMAP *image;
    float X;
    float Y;
}Monster;

Monster initWithMonsterNumber(int fase){
    int number;
    // temp -- como teriamos um método adequado para geração aleatória dado uma fase
    number = fase;
    //
    
    // number = getId(fase);
    
    Monster *monstro = malloc(sizeof(Monster));
    image = getImage(number);
    
    HP = getLife(number);
    ataque = getAttack(number);
    
    
    return monstro;
}

int getId(int fase){       //Recebido uma fase, este método realiza o sorteio aleatório de monstros possiveis para spawn.
    srand( (unsigned) time (NULL) ) ;
    int x = rand()%100;
    
    
    switch(fase){
        case 1:
            if(x < 50)
                return 1;   // CRAB
            if(x < 90)
                return 2;   // FLY
            return 3;       // BUG
            
        case 2:
            if(x < 65)
                return 4;   // FAT
            if(x < 95)
                return 5;   // KOBOLD
            return 3;       // BUG
            
        case 3:
            if(x < 60)
                return 6;   // WORM
            if(x < 95)
                return 7;   // LEECH
            return 8;       // HORNET
            
        case 4:
            if(x < 35)
                return 9;   // UNDEAD FAT
            if(x < 85)
                return 10;  // KNIGHT
            return 11;      // SHADOW
            
        case 5:
            if(x < 40)
                return 11;  // SHADOW
            if(x < 30)
                return 9;   // UNDEAD FAT
            return 12;      // SPIDER
            
        case 6:
            if(x < 60)
                return 0;   // FALSE_WORM
                
            x = rand()%100; // Not false worm >> Then spawn real monster
                
            if(x < 45)
                return 11;  // SHADOW
            if(x < 50)
                return 12;  // SENTRY
            return 13;      // SUCCUBUS
            
    }
}

ALLEGRO_BITMAP getImage(int number){        // Isto procura a imagem de um monstro dado seu id
    ALLEGRO_BITMAP *Image;
    
    //Switch case for images
    
    return image;
}

int getLife(int number){        //Este método devolve a vida de um monstro, dado seu id
    int life;
    
    //Switch case for lifes
    
    return life;
}

int getAttack(int num){      //Este metodo devolve qual ataque o monstro realiza, dado seu id
    int attack;
    
    //Switch case for attacks
    
    return attack;
}