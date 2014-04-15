#include <opencv/highgui.h>
#include "camera.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


typedef struct _Ataque{
    float X0;
    float Y0;
    float X;
    float Y;
    int damage;
    int currentDuration;
    int preAnimationTime;
    int duration;
    ALLEGRO_BITMAP *image;

}Ataque;

*Ataque initWithAttackNumber(int attackId, int senderX, int senderY){
    Ataque *ataque = malloc(sizeof(Ataque));
    
    ataque -> X0 = senderX;
    ataque -> Y0 = senderY;
    ataque -> preAnimationTime = 0;
    
    
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

    image = getImage(attackId, ataque -> X0, ataque -> Y0, ataque -> X, ataque -> Y);
    
    ataque -> duration = getDuration(attackId);
    ataque -> damage = getDamage(attackId);
    
    
    return ataque;
}


bool checkAttack(Ataque *attack){
    if (attack -> preAnimationTime < 0) // Em geral, o tempo antes da ativação do ataque. Pra meele e alguns casos especiais. Ele é um contador externo à animação.
        attack -> preAnimationTime++;
    else{
        if(attack -> currentDuration != attack -> duration)
            attack -> currentDuration++;
        else{
            
            //if(ponto em X,Y MATRIZ GLOBAL == BRANCA || ponto em X,Y MATRIZ GLOBAL != Shield)
            //ATTACK DAMAAAAGE
            //Hit, sounds, etc...
            
            
            free(attack);
            return TRUE;
        }
    }
    return FALSE;
}


ALLEGRO_BITMAP getImage(int number, X0, Y0, X, Y){        // Isto procura a imagem de um ataque dado seu id.
    ALLEGRO_BITMAP *Image;
    
    //Switch case for images
    
    return image;
}

int getDamage(int number){        //Este método devolve o dano de um ataque, dado seu id.
    int damage;
    
    //Switch case for damages
    
    return damage;
}

int getDuration(int num){      //Este metodo devolve qual o tempo de animação do ataque.
    int time;
    
    //Switch case for attacks
    
    return time;
}