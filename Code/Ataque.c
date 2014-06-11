#include "Ataque.h"
#include "globals.h"

Ataque *initWithAttackNumber(int attackId, int senderX, int senderY){
    Ataque *ataque = malloc(sizeof(Ataque));
    
    ataque -> X0 = senderX;
    ataque -> Y0 = senderY;
    ataque -> preAnimationTime = 0;
    ataque -> atkId = attackId;
    ataque -> deathCountdown = 0;
    printf("bla\n");


    if(attackId == 1 || attackId == 4 || attackId == 9 || attackId == 10){
        ataque -> targetX = ataque -> X0;
        ataque -> targetY = ataque -> Y0;
        ataque -> angle = 0;
    }
    else{
    ataque -> targetX = rand()%(globalLargura - 80) + 40;
    ataque -> targetY = rand()%(globalAltura - 190) + 40;
    ataque -> angle = atan2( (ataque->targetY - ataque->Y0), (ataque->targetX - ataque->X0) );
    }
    

    ataque -> currentDuration = 0;
    ataque -> image = NULL;
    getImageAttack(attackId, &ataque -> image);
    
    ataque -> duration = getDuration(attackId);
    ataque -> damage = getDamage(attackId);

    // Realiza a inclinação
   
    if(!ataque -> image)
        printf("Imageless atk\n");
    // Desenha no primeiro frame
    printf("Angle: %f\n", ataque -> angle);
    al_draw_rotated_bitmap(ataque -> image, 0, 0, ataque -> X + al_get_bitmap_width(ataque -> image), ataque -> Y + al_get_bitmap_height(ataque -> image), ataque -> angle, 0);

    return ataque;
}


bool checkAttack(Ataque *attack){
    if (attack -> preAnimationTime > 0) // Em geral, o tempo antes da ativação do ataque. Pra meele e alguns casos especiais. Ele é um contador externo à animação.
        attack -> preAnimationTime--;
    else{

        
        if(attack -> currentDuration != attack -> duration)
            attack -> currentDuration ++;
        
        
        attack -> X = attack -> X0 + ( (attack -> targetX - attack -> X0) * (attack -> currentDuration / attack -> duration));
        attack -> Y = attack -> Y0 + ( (attack -> targetY - attack -> Y0) * (attack -> currentDuration / attack -> duration));
            
        al_draw_rotated_bitmap(attack -> image, 0, 0, attack -> X - (al_get_bitmap_width(attack -> image) /2), attack -> Y - (al_get_bitmap_height(attack -> image) / 2), attack -> angle, 0);
        

            /*al_draw_rotated_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags);*/
            
            //if(ponto em X,Y MATRIZ GLOBAL == BRANCA || ponto em X,Y MATRIZ GLOBAL != Shield)
            //ATTACK DAMAAAAGE
            //Hit, sounds, etc...
                
            
            //free(attack);
            return true;
    }
    return false;
}


void getImageAttack(int number, ALLEGRO_BITMAP **image){        // Isto procura a imagem de um ataque dado seu id.
    
    char nome[40], temp[20];
    int width, height;
    
    //Switch case for images
    switch(number){
    case Pincer:
        sprintf (temp, "Pincer");
        width = height = 75;
        break;
    case Spit:
        sprintf (temp, "Spit");
        width = height = 50;
        break;
    case Needle:
        sprintf (temp, "Needle");
        width = 60;
        height = 35;
        break;
    case Cut:
        sprintf (temp, "Cut");
        width = height = 75;
        break;
    case SpearThrow:
        sprintf (temp, "SpearThrow");
        width = 75;
        height = 10;
        break;
    case MagicMissiles:
        sprintf (temp, "MagicMissiles");
        width = height = 50;
        break;
    case Spores:
        sprintf (temp, "Spores");
        width = height = 50;
        break;
    case NeedleB:
        sprintf (temp, "Needle2");
        width = 60;
        height = 35;
        break;
    case CutB:
        sprintf (temp, "Cut2");
        width = height = 75;
        break;
    case Omnicut:
        sprintf (temp, "Omnicut");
        width = height = 75;
        break;
    case Curse:
        sprintf (temp, "Curse");
        width = height = 50;
        break;
    case Web:
        sprintf (temp, "Web");
        width = height = 50;
        break;
    case Fireball:
        sprintf (temp, "Fireball");
        width = height = 70;
        break;
    }
    *image = al_create_bitmap(width, height);
    sprintf (nome, "Graphics/%s.png", temp);
    *image = al_load_bitmap(nome);
}


int getDamage(int number){        //Este método devolve o dano de um ataque, dado seu id.
    
    switch(number){
        case Pincer:
            return 2;

        case Spit:
            return 7;

        case Needle:
            return 15;

        case Cut:
            return 6;

        case SpearThrow:
            return 8;

        case MagicMissiles:
            return 3;

        case Spores:
            return 2;

        case NeedleB:
            return 15;

        case CutB:
            return 11;

        case Omnicut:
            return 8;

        case Curse:
            return 5;

        case Web:
            return 0;

        case Fireball:
            return 10;
    }

    return 0;
}

float getDuration(int num){      //Este metodo devolve qual o tempo de animação do ataque.

    switch(num){
        case Pincer:
            return 16;

        case Spit:
            return 30;

        case Needle:
            return 20;

        case Cut:
            return 16;

        case SpearThrow:
            return 20;

        case MagicMissiles:
            return 20;

        case Spores:
            return 60;

        case NeedleB:
            return 0.3;

        case CutB:
            return 16;

        case Omnicut:
            return 16;

        case Curse:
            return 20;

        case Web:
            return 30;

        case Fireball:
            return 20;
    }

    return 0;
}