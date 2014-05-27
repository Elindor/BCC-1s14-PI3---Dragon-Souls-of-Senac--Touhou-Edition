#include <opencv/highgui.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>
#include "globals.h"
#include "Monster.h"



Monster* initWithMonsterNumber(int fase){
    
    int monsterId = getId(fase);    //Recebe um ID de monstro gerado aleatóriamente baseado na fase
    Monster *monstro = malloc(sizeof(Monster));
    
    
    int random = rand()%180;    // X é definido aleatóriamente (lado ou não lado?)
    random = random % 2;
    if(random == 1){
        monstro -> X = -200;
        monstro -> fromLeft = true;
    }
    else{
        monstro -> X = +200;
        monstro -> fromLeft = false;
    }
    
    
    if(monsterId == 1 || monsterId == 4 || monsterId == 5 || monsterId == 9 || monsterId == 10){ // Meele Monster
        monstro -> Y = globalAltura/4;
    }
    else{
        monstro -> Y = rand()%globalAltura;
    }
    
    
    
    getImageMonster(monsterId, monstro -> image);      // Aloca internamente a imagem do monstro.
    
    
    monstro -> HP = getLife(monsterId);             //Devolve a vida do monstro
    monstro -> cooldown = getCooldown(monsterId);   //Devolve o Cooldown do monstro
    getAttack(monsterId, monstro -> ataque); // Manda pada o Void o ataque e função preenche vetor.
    monstro -> ready = false;
    
    return monstro;
}


void startMove(Monster* monstro){
    
    if (monstro -> fromLeft == true)
        monstro -> X++;
    else
        monstro -> X--;
        
    if(monstro -> X == 200 || monstro -> X == globalLargura - 200)
        monstro -> ready = true;
    
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
                return 6;   // WORM
            
            x = rand()%100; // Not worm >> Then spawn real monster
            
            if(x < 45)
                return 11;  // SHADOW
            if(x < 50)
                return 13;  // SENTRY
            return 41;      // SUCCUBUS           
    }

    return 0;
}

void getImageMonster(int number, ALLEGRO_BITMAP* image){        // Isto procura a imagem de um monstro dado seu id
    
    char nome[40], temp[20];
    int width, height;
    
    
    switch(number){
        case Crab:
            sprintf (temp, "Crab");
            width = 179;
            height = 100;
            break;

        case Fly:
            sprintf (temp, "Fly");
            width = 168;
            height = 180;
            break;

        case Bug:
            sprintf (temp, "Bug");
            width = 250;
            height = 179;
            break;

        case Fat:
            sprintf (temp, "Fat");
            width = 166;
            height = 270;
            break;

        case Kobold:
            sprintf (temp, "Kobold");
            width = 187;
            height = 195;
            break;

        case Worm:
            sprintf (temp, "Worm");
            width = 101;
            height = 100;
            break;

        case Leech:
            sprintf (temp, "Leech");
            width = 202;
            height = 220;
            break;

        case Hornet:
            sprintf (temp, "Hornet");
            width = 138;
            height = 190;
            break;

        case UndeadFat:
            sprintf (temp, "UndeadFat");
            width = 205;
            height = 260;
            break;

        case Knight:
            sprintf (temp, "Knight");
            width = 162;
            height = 190;
            break;

        case Shadow:
            sprintf (temp, "Shadow");
            width = 115;
            height = 192;
            break;

        case Spider:
            sprintf (temp, "Spider");
            width = 287;
            height = 200;
            break;

        case Sentry:
            sprintf (temp, "Sentry");
            width = 0;
            height = 0;
            break;
    }
    
    image = al_create_bitmap(width, height);
    sprintf (nome, "Graphics/%s.png", temp);
    image = al_load_bitmap(nome);
    if(image){
        printf("Image \"%s\" did not load", nome);
        image = al_load_bitmap("Graphics/Fly.png");

    }

    al_draw_bitmap(image, 0, 0, 0);

    printf("DrawImage\n");

    al_rest(5);

}

int getLife(int number){        //Este método devolve a vida de um monstro, dado seu id
    
    switch(number){
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

    return 0;
}

void getAttack(int fase, int *num){      //Este metodo devolve quais ataques o monstro realiza, dado seu id
    
    switch(fase){
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

float getCooldown(int num){
    switch(num){
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

    return 0;
}
