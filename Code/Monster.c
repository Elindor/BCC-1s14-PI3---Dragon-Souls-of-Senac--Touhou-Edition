    #include <opencv/highgui.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

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
    int id;
    
    return id;
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