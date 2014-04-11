#include <opencv/highgui.h>


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
    int duration;
    ALLEGRO_BITMAP *image;

}Ataque;

*Ataque initWithAttackNumber(int attackId, int senderX, int senderY){
    Ataque *ataque = malloc(sizeof(Ataque));
    
    ataque -> X0 = senderX;
    ataque -> Y0 = senderY;
    
    ///
    // Adicionar sistema para geração de (X,Y) finais.
    ///

    ataque -> currentDuration = 0;

    image = getImage(attackId, ataque -> X0, ataque -> Y0, ataque -> X, ataque -> Y);
    
    ataque -> duration = getDuration(attackId);
    ataque -> damage = getDamage(attackId);
    
    
    return ataque;
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