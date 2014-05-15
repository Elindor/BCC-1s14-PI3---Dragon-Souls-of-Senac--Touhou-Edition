#include "Ataque.h"

Ataque *initWithAttackNumber(int attackId, int senderX, int senderY){
    Ataque *ataque = malloc(sizeof(Ataque));
    
    ataque -> X0 = senderX;
    ataque -> Y0 = senderY;
    ataque -> preAnimationTime = 0;
    ataque -> id = attackId;
    
    ///
    // Adicionar sistema para geração de (X,Y) finais.
    //
    // if(meele){
    // PreAnimationTime = -40;
    // ataque -> X = senderX;
    // ataque -> Y = senderY;
    //  }
    // else
    //  do{
    //
    //
    //
    //  }while(ponto em X,Y MATRIZ GLOBAL == BRANCA);
    ///

    ataque -> currentDuration = 0;

    getImage(attackId, ataque -> image);
    
    ataque -> duration = getDuration(attackId);
    ataque -> damage = getDamage(attackId);
    
    // Realiza a inclinação
    float tempAngle = atan2( (ataque->targetY - ataque->Y0), (ataque->targetX - ataque->X0) );
    ataque -> angle = tempAngle * 3.14 / 180.0;
    
    // Desenha no primeiro frame
    al_draw_rotated_bitmap(ataque->image, ataque -> X, ataque -> Y, ataque -> X, ataque -> Y, ataque ->angle, 0);
    
    return ataque;
}


bool checkAttack(Ataque *attack){
    if (attack -> preAnimationTime < 0) // Em geral, o tempo antes da ativação do ataque. Pra meele e alguns casos especiais. Ele é um contador externo à animação.
        attack -> preAnimationTime++;
    else{
        if(attack -> currentDuration != attack -> duration)
            attack -> currentDuration++;
        else{
            
            attack -> X = attack -> X0 + ( ( (attack -> targetX - attack -> X0) / attack -> duration) * attack -> currentDuration);
            attack -> Y = attack -> Y0 + ( ( (attack -> targetY - attack -> Y0) / attack -> duration) * attack -> currentDuration);
            
            
            
            al_draw_rotated_bitmap(attack -> image, attack -> X, attack -> Y, attack -> X, attack -> Y, attack ->angle, 0);
            /*al_draw_rotated_bitmap(ALLEGRO_BITMAP *bitmap, float cx, float cy, float dx, float dy, float angle, int flags);*/
            
            //if(ponto em X,Y MATRIZ GLOBAL == BRANCA || ponto em X,Y MATRIZ GLOBAL != Shield)
            //ATTACK DAMAAAAGE
            //Hit, sounds, etc...
                
            
            free(attack);
            return true;
        }
    }
    return false;
}


void getImage(int number, ALLEGRO_BITMAP *image){        // Isto procura a imagem de um ataque dado seu id.
    
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
        sprintf (temp, "Needle");
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
    image = al_create_bitmap(width, height);
    sprintf (nome, "Graphics/%s.png", temp);
    image = al_load_bitmap(nome);
}

int getDamage(int number){        //Este método devolve o dano de um ataque, dado seu id.
    
    switch(number){
        case Pincer:
            return 4;

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
            return 2;

        case Spit:
            return 4;

        case Needle:
            return 2;

        case Cut:
            return 2;

        case SpearThrow:
            return 1;

        case MagicMissiles:
            return 1;

        case Spores:
            return 2;

        case NeedleB:
            return 0.3;

        case CutB:
            return 2;

        case Omnicut:
            return 3;

        case Curse:
            return 2;

        case Web:
            return 1.5;

        case Fireball:
            return 2;
    }

    return 0;
}