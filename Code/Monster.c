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

    monstro -> isHit = 0;
    
    int random = rand()%180;    // X é definido aleatóriamente (lado ou não lado?)
    random = random % 2;
    if(random == 1){
        monstro -> X = -200;
        monstro -> fromLeft = 1;
    }
    else{
        monstro -> X = globalLargura + 200;
        monstro -> fromLeft = 0;
    }
    
    
    if(monsterId == 0 || monsterId == 3 || monsterId == 4 || monsterId == 8 || monsterId == 9){ // Meele Monster
        monstro -> Y = (globalAltura/4) * (float)2.5;
    }
    else{
        monstro -> Y = rand()% ((globalAltura/4) * 3);
        monstro -> Y -= 150;
    }
    
    
    monstro -> image = NULL;
    getImageMonster(monsterId, &monstro -> image);      // Aloca internamente a imagem do monstro.

    if(!monstro -> image)
        printf("NOPE!\n");
    
    monstro -> HP = getLife(monsterId);             //Devolve a vida do monstro
    monstro -> cooldown = getCooldown(monsterId);   //Devolve o Cooldown do monstro
    getAttack(monsterId, monstro -> ataque); // Manda pada o Void o ataque e função preenche vetor.
    monstro -> ready = 0;
    monstro -> currentCooldown = 0;
    sprintf (monstro -> name, "\n");
    if(monstro -> Y < al_get_bitmap_height(monstro -> image)){
        monstro -> Y = al_get_bitmap_height(monstro -> image);
    }
    
    monstro -> centerX = monstro -> X + (al_get_bitmap_width(monstro -> image) /2);
    monstro -> centerY = monstro -> Y + (al_get_bitmap_height(monstro -> image) /2);
    return monstro;
}

Monster* initWithBossNumber(int fase){
    
    int monsterId = fase;
    Monster *monstro = malloc(sizeof(Monster));

    monstro -> isHit = 0;
    
    monstro -> X = globalLargura/2;
    
    if(monsterId == 0 || monsterId == 3 || monsterId == 4 || monsterId == 8 || monsterId == 9){ // Meele Monster
        monstro -> Y = (globalAltura/4) * (float)2.5;
    }
    else{
        monstro -> Y = globalAltura + 400;
    }
    monstro -> fromLeft = 2;
    
    monstro -> image = NULL;
    getImageMonster(monsterId, &monstro -> image);      // Aloca internamente a imagem do monstro.
    
    if(!monstro -> image)
        printf("NOPE!\n");
    
    monstro -> HP = getLife(monsterId);             //Devolve a vida do monstro
    monstro -> cooldown = getCooldown(monsterId);   //Devolve o Cooldown do monstro
    getAttack(monsterId, monstro -> ataque); // Manda pada o Void o ataque e função preenche vetor.
    monstro -> ready = 0;
    monstro -> currentCooldown = 0;
    getName(monsterId, monstro -> name);
    
    monstro -> centerX = monstro -> X + (al_get_bitmap_width(monstro -> image) /2);
    monstro -> centerY = monstro -> Y + (al_get_bitmap_height(monstro -> image) /2);
    return monstro;
}




void startMove(Monster* monstro){
    if(monstro -> ready == 1)
        return;
    
    if(monstro -> fromLeft == 1)
        monstro -> X = monstro -> X + 20;
    else if(monstro -> fromLeft == 0)
        monstro -> X = monstro -> X - 20;
    else if(monstro -> fromLeft == 2)
        monstro -> Y = monstro -> Y - 30;
    
    
    monstro -> centerX = monstro -> X + (al_get_bitmap_width(monstro -> image) /2);
    monstro -> centerY = monstro -> Y + (al_get_bitmap_height(monstro -> image) /2);
    
    if(monstro -> centerX > (al_get_bitmap_width(monstro -> image) /2) && monstro -> centerX < (globalLargura - (al_get_bitmap_height(monstro -> image) /2)) && monstro -> fromLeft != 2){
        int randomMovementStop = rand() % 100;
        if(monstro -> fromLeft == 1)
            randomMovementStop += monstro -> centerX/4;
        else
            randomMovementStop += (globalLargura - monstro -> centerX) /4;
            
        if(randomMovementStop > 90 && monstro -> centerX > 0 && monstro -> centerX < globalLargura){
            monstro -> ready = 1;
            printf("MOVEMENT ENDEEEEEEEEEEEEEED %f %f\n", monstro -> X, monstro -> centerX);
        }

    }
    if(monstro -> centerY < globalAltura - 300 && monstro -> fromLeft == 2){
        monstro -> ready = 1;
    }
}


int getId(int fase){       //Recebido uma fase, este método realiza o sorteio aleatório de monstros possiveis para spawn.
    srand( (unsigned) time (NULL) ) ;
    int x = rand()%100;
    
    
    switch(fase){
        case 1:
            if(x < 50)
                return 0;   // CRAB
            if(x < 90)
                return 1;   // FLY
            return 2;       // BUG
            
        case 2:
            if(x < 65)
                return 3;   // FAT
            if(x < 95)
                return 4;   // KOBOLD
            return 2;       // BUG
            
        case 3:
            if(x < 60)
                return 5;   // WORM
            if(x < 95)
                return 6;   // LEECH
            return 7;       // HORNET
            
        case 4:
            if(x < 35)
                return 8;   // UNDEAD FAT
            if(x < 85)
                return 9;  // KNIGHT
            return 10;      // SHADOW
            
        case 5:
            if(x < 40)
                return 10;  // SHADOW
            if(x < 30)
                return 8;   // UNDEAD FAT
            return 11;      // SPIDER
            
        case 6:
            if(x < 60)
                return 5;   // WORM
            
            x = rand()%100; // Not worm >> Then spawn real monster
            
            if(x < 45)
                return 10;  // SHADOW
            if(x < 50)
                return 12;  // SENTRY
            return 41;      // SUCCUBUS           
    }

    return 0;
}

void getImageMonster(int number, ALLEGRO_BITMAP** image){        // Isto procura a imagem de um monstro dado seu id
    
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
            width = 87;
            height = 84;
            break;
            
        case Marlingone:
            sprintf (temp, "Marlingone");
            width = 144;
            height = 144;
            break;
        case Hueda:
            sprintf (temp, "Troll2");
            width = 410;
            height = 502;
            break;
        case Cirno:
            sprintf (temp, "Cirno");
            width = 108;
            height = 128;
            break;
        case Dragon:
            sprintf (temp, "Dragon");
            width = 500;
            height = 522;
            break;
        case Balrog:
            sprintf (temp, "Balrog");
            width = 306;
            height = 256;
            break;
        case Lavos:
            sprintf (temp, "Sentry");
            width = 0;
            height = 0;
            break;
        case Phantom2:
            sprintf (temp, "DarkPhantom");
            width = 162;
            height = 190;
            break;
        case Phantom3:
            sprintf (temp, "DarkPhantom");
            width = 162;
            height = 190;
            break;
        case Phantom4:
            sprintf (temp, "DarkPhantom");
            width = 162;
            height = 190;
            break;
        case Phantom5:
            sprintf (temp, "DarkPhantom");
            width = 162;
            height = 190;
            break;
        case Phantom6:
            sprintf (temp, "DarkPhantom");
            width = 162;
            height = 190;
            break;

    }
    
    *image = al_create_bitmap(width, height);
    sprintf (nome, "Graphics/%s.png", temp);
    printf("%s", nome);
    *image = al_load_bitmap(nome);
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
            
        case Marlingone:
            return 100;

        case Hueda:
            return 160;

        case Cirno:
            return 120;

        case Dragon:
            return 200;

        case Balrog:
            return 400;

        case Lavos:
            return 1000;

        case Phantom2:
            return 94;

        case Phantom3:
            return 132;

        case Phantom4:
            return 187;

        case Phantom5:
            return 246;

        case Phantom6:
            return 300;
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

        case Marlingone:
            num[0] = 13;
            num[1] = 11;
            return;

        case Hueda:
            num[0] = 4;
            num[1] = 5;
            return;

        case Cirno:
            num[0] = 6;
            num[1] = 11;
            return;

        case Dragon:
            num[0] = 13;
            num[1] = 10;
            return;

        case Balrog:
            num[0] = 10;
            num[1] = 13;
            return;

        case Lavos:
            num[0] = 11;
            num[1] = 13;
            return;

        case Phantom2:
            num[0] = 4;
            num[1] = 6;
            return;

        case Phantom3:
            num[0] = 9;
            num[1] = 5;
            return;

        case Phantom4:
            num[0] = 9;
            num[1] = 9;
            return;

        case Phantom5:
            num[0] = 11;
            num[1] = 9;
            return;

        case Phantom6:
            num[0] = 9;
            num[1] = 13;
            return;
    }
}

float getCooldown(int num){
    switch(num){
        case Crab:
            return 7;

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
            
        case Marlingone:
            return 3;

        case Hueda:
            return 5;

        case Cirno:
            return 1;

        case Dragon:
            return 2;

        case Balrog:
            return 2;

        case Lavos:
            return 3;

        case Phantom2:
            return 2;

        case Phantom3:
            return 1;

        case Phantom4:
            return 1;

        case Phantom5:
            return 0;

        case Phantom6:
            return -1;
    }

    return 0;
}

void getName(int num, char *temp){

    switch (num){
        case Marlingone:
            sprintf (temp, "Old Sorcerer Marlingone");
            break;

        case Hueda:
            sprintf (temp, "Troll Chieftain Hu3Hu3da");
            break;

        case Cirno:
            sprintf (temp, "Ice Fairy Cirno");
            break;

        case Dragon:
            sprintf (temp, "Guardian Dragon");
            break;

        case Balrog:
            sprintf (temp, "Great Demon Balrog");
            break;

        case Lavos:
            sprintf (temp, "Lavos");
            break;

        case Phantom2:
            sprintf (temp, "Dark Phantom GruntingPlague");
            break;

        case Phantom3:
            sprintf (temp, "Dark Phantom FrostQueen _ GGWP");
            break;

        case Phantom4:
            sprintf (temp, "Dark Phantom LegendaryRankDude");
            break;

        case Phantom5:
            sprintf (temp, "Dark Phantom RussiaDotAPlayer");
            break;

        case Phantom6:
            sprintf (temp, "Dark Phantom Fluttershy");
            break;
    }
}

void monsterGotHit(ALLEGRO_BITMAP *display, Monster *m){
    unsigned char rd, gd, bd, am;

    //tentar usar putpixels pra ver a hitbox...
    ALLEGRO_LOCKED_REGION *lockedDisplay = al_lock_bitmap(display, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_READWRITE);
    ALLEGRO_LOCKED_REGION *lockedMinion = al_lock_bitmap(m -> image, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_READWRITE);

    //tipo = abgr8888, pitch = variável, pixel_size = 4

    int hm = al_get_bitmap_height(m -> image);
    int wm = al_get_bitmap_width(m -> image);
    int hd = al_get_bitmap_height(display);
    int wd = al_get_bitmap_width(display);

    unsigned char *rowM = lockedMinion -> data;
    unsigned char *rowD = lockedDisplay -> data;

    rowD += ((int)m -> Y * lockedDisplay -> pitch);
    rowD += ((int)m -> X * lockedDisplay -> pixel_size);

    for(int y = 0; y < hm; y++){
        unsigned char *pixelM = rowM;
        unsigned char *pixelD = rowD;

        for(int x = 0; x < wm; x++){
            am = rd = bd = gd = 0;

            pixelM += 3;
            am = *pixelM;
            pixelM++;

            if(am != 0 && y + (int)m -> Y >= 0 && y + (int)m -> Y < hd && x + (int)m -> X >= 0 && x + (int)m -> X < wd){
                bd = *pixelD;
                pixelD++;

                gd = *pixelD;
                pixelD++;

                rd = *pixelD;
                pixelD += 2;

                if(rd == 255 && gd == 0 && bd == 0){
                    if(m -> isHit == 0){
                        m -> isHit = 1;
                        m -> HP -= playerAtk;                   // Monstro perde vida igual ao ataque;
                        playerHP += playerAtk * 0.13;           // O valor 13% de lifesteal foi gerado por um rand com seed (Leon)

                        printf("acertou hp atual:%d!\n", m -> HP);

                        if(playerHP > 100)
                            playerHP = 100;

                        al_unlock_bitmap(display);
                        al_unlock_bitmap(m -> image);
                        return;
                    }

                    else if(m -> isHit == 1){
                        al_unlock_bitmap(display);
                        al_unlock_bitmap(m -> image);
                        printf("Ja está sendo atacado!\n");
                        return;
                    }
                }
            }

            else
                pixelD += 4;
        }

        rowM += lockedMinion -> pitch;
        rowD += lockedDisplay -> pitch;
    }

    al_unlock_bitmap(display);
    al_unlock_bitmap(m -> image);

    if(m -> isHit == 1){
        printf("Espada saiu do minion\n");
        m -> isHit = 0;
    }
}