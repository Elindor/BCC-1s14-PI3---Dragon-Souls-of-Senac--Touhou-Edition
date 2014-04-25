#include <opencv/highgui.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>


typedef enum monstro{
    Crab = 0, Fly = 1, Bug = 2, Fat = 3, Kobold = 4, Worm = 5, Leech = 6, Hornet = 7, UndeadFat = 8, Knight = 9, Shadow = 10, Spider = 11, Sentry = 12
};

typedef struct _Monster{
    int HP;
    int ataque[2];
    float cooldown;         // Somar o periodo dos ataques no uso, lembrar de deletar comentário
    ALLEGRO_BITMAP *image;
    float X;
    float Y;
}Monster;

typedef struct _noMonster{
    noMonster* prox;
    Monster* monster;
}oMonster;



Monster* initWithMonsterNumber(int fase){
    
    int monsterId = getId(fase);    //Recebe um ID de monstro gerado aleatóriamente baseado na fase
    
    Monster *monstro = malloc(sizeof(Monster));
    getImage(monsterId, monstro -> image);      // Aloca internamente a imagem do monstro.
    
    monstro -> HP = getLife(monsterId);             //Devolve a vida do monstro
    monstro -> cooldown = getCooldown(monsterId);   //Devolve o Cooldown do monstro
    getAttack(monsterId, monstro -> ataque); // Manda pada o Void o ataque e função preenche vetor.
    
    
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
                return 13;  // SENTRY
            return 41;      // SUCCUBUS
            
    }
}

ALLEGRO_BITMAP getImage(int number, ALLEGRO_BITMAP image){        // Isto procura a imagem de um monstro dado seu id
    ALLEGRO_BITMAP *Image;
    
    Switch(number){
    case Crab:
        image = al_load_bitmap("Graphics/Crab.png");
        return;
    case Fly:
        image = al_load_bitmap("Graphics/Fly.png");
        return;
    case Bug:
        image = al_load_bitmap("Graphics/Bug.png");
        return;
    case Fat:
        image = al_load_bitmap("Graphics/Fat.png");
        return;
    case Kobold:
        image = al_load_bitmap("Graphics/Kobold.png");
        return;
    case Worm:
        image = al_load_bitmap("Graphics/Worm.png");
        return;
    case Leech:
        image = al_load_bitmap("Graphics/Leech.png");
        return;
    case Hornet:
        image = al_load_bitmap("Graphics/Hornet.png");
        return;
    case UndeadFat:
        image = al_load_bitmap("Graphics/UndeadFat.png");
        return;
    case Knight:
        image = al_load_bitmap("Graphics/Knight.png");
        return;
    case Shadow:
        image = al_load_bitmap("Graphics/Shadow.png");
        return;
    case Spider:
        image = al_load_bitmap("Graphics/Spider.png");
        return;
    case Sentry:
        image = al_load_bitmap("Graphics/Worm.png");        // MUDAR!!!
        return;
    }
    
    return image;
}

int getLife(int number){        //Este método devolve a vida de um monstro, dado seu id
    
    Switch(number){
    case Crab:
        return 9;
    case Fly:
        return 6;
    case Bug:
        return 15;
    case Fat:
        return 20;
    case Kobold:
        return 16;
    case Worm:
        return 5;
    case Leech:
        return 25;
    case Hornet:
        return 30;
    case UndeadFat:
        return 60;
    case Knight:
        return 36;
    case Shadow:
        return 24;
    case Spider:
        return 30;
    case Sentry:
        return 42;
    }
}

void getAttack(int fase, int *num){      //Este metodo devolve quais ataques o monstro realiza, dado seu id
    
    Switch(fase){
    case Crab:
        num[0] = 1;
        num[1] = 1;
        return;
    case Fly:
        num[0] = 2;
        num[1] = 2;
        return;
    case Bug:
        num[0] = 3;
        num[1] = 3;
        return;
    case Fat:
        num[0] = 4;
        num[1] = 4;
        return;
    case Kobold:
        num[0] = 5;
        num[1] = 4;
        return;
    case Worm:
        num[0] = 6;
        num[1] = 6;
        return;
    case Leech:
        num[0] = 7;
        num[1] = 7;
        return;
    case Hornet:
        num[0] = 8;
        num[1] = 4;
        return;
    case UndeadFat:
        num[0] = 9;
        num[1] = 4;
        return;
    case Knight:
        num[0] = 9;
        num[1] = 10;
        return;
    case Shadow:
        num[0] = 11;
        num[1] = 9;
        return;
    case Spider:
        num[0] = 12;
        num[1] = 9;
        return;
    case Sentry:
        num[0] = 13;
        num[1] = 9;
        return;
    }
}

int getCooldown(int num){
    Switch(num){
    case Crab:
        return 8;
    case Fly:
        return 4;
    case Bug:
        return 3;
    case Fat:
        return 3;
    case Kobold:
        return 4;
    case Worm:
        return 0.8;
    case Leech:
        return 3;
    case Hornet:
        return 3;
    case UndeadFat:
        return 6;
    case Knight:
        return 4;
    case Shadow:
        return 3;
    case Spider:
        return 4;
    case Sentry:
        return 1;
    }
}

